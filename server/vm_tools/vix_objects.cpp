#include "vix_objects.h"
#include "../../../common/tools/CExceptions.h"

//------------------------------------------------------------------------------
#define  CONNTYPE    VIX_SERVICEPROVIDER_VMWARE_WORKSTATION
#define  HOSTNAME ""
#define  HOSTPORT 0
#define  USERNAME ""
#define  PASSWORD ""
//------------------------------------------------------------------------------
std::string GetVIXErrorMessage(VixError aErrorCode)
{
   const char* lMessage = Vix_GetErrorText(aErrorCode, NULL);
   std::string str = lMessage;
   return str;
}
//------------------------------------------------------------------------------
#define THROW_ERROR(vixError) \
   throw vm_exception(GetVIXErrorMessage(vixError));

#define CHECK_AND_THROW(vixError)\
if (VIX_FAILED((vixError))) \
{ \
   throw vm_exception(GetVIXErrorMessage(vixError)); \
}
//------------------------------------------------------------------------------
CVix_Snapshot::CVix_Snapshot(VixHandle aHandleVM, VixHandle aHandleShapshot)
:mHandleVM(aHandleVM), mHandleShapshot(aHandleShapshot)
{
   if (mHandleVM == VIX_INVALID_HANDLE ||
      mHandleShapshot == VIX_INVALID_HANDLE)
      throw vm_exception("Cannot get snapshot.");
}

CVix_Snapshot::~CVix_Snapshot()
{
   Vix_ReleaseHandle(mHandleShapshot);
}

std::string CVix_Snapshot::GetNameSnapshot()
{
   VixError err;
   char *lNameSnapshot = NULL;
   err = Vix_GetProperties(mHandleShapshot,
      VIX_PROPERTY_SNAPSHOT_DISPLAYNAME,
      &lNameSnapshot,
      VIX_PROPERTY_NONE);
   CHECK_AND_THROW(err);
   return lNameSnapshot;
}

VixHandle CVix_Snapshot::GetHandle()
{
   return mHandleShapshot;
}

//------------------------------------------------------------------------------
CVix_VirtualMachine::CVix_VirtualMachine(VixHandle aHandleVM)
:mHandleVM(aHandleVM)
{
   if (mHandleVM == VIX_INVALID_HANDLE)
      throw vm_exception("Cannot get virtal machine.");
}

CVix_VirtualMachine::~CVix_VirtualMachine()
{
   Vix_ReleaseHandle(mHandleVM);
}

bool CVix_VirtualMachine::IsPowerOn()
{
   VixError err;
   VixToolsState lPowerState = 0;
   err = Vix_GetProperties(mHandleVM,
      VIX_PROPERTY_VM_POWER_STATE,
      &lPowerState,
      VIX_PROPERTY_NONE);
   CHECK_AND_THROW(err);
   return (VIX_POWERSTATE_POWERED_ON & lPowerState) == VIX_POWERSTATE_POWERED_ON;
}

void CVix_VirtualMachine::Pause()
{
   VixError err;
   VixHandle jobHandle = VIX_INVALID_HANDLE;
   jobHandle = VixVM_Pause(mHandleVM,
      0, // options
      VIX_INVALID_HANDLE, // propertyListHandle
      NULL, // callbackProc
      NULL); // clientData
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   Vix_ReleaseHandle(jobHandle);
   CHECK_AND_THROW(err);
}

void CVix_VirtualMachine::UnPause()
{
   VixError err;
   VixHandle jobHandle = VIX_INVALID_HANDLE;
   jobHandle = VixVM_Unpause(mHandleVM,
      0, // options
      VIX_INVALID_HANDLE, // propertyListHandle
      NULL, // callbackProc
      NULL); // clientData
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   Vix_ReleaseHandle(jobHandle);
   CHECK_AND_THROW(err);
}

int CVix_VirtualMachine::GetNumSnapshots()
{
   VixError err;
   int numSnapshots;
   err = VixVM_GetNumRootSnapshots(mHandleVM, &numSnapshots);
   CHECK_AND_THROW(err);
   return numSnapshots;
}

void CVix_VirtualMachine::AddSnapshot(std::string aNameSnapshot, std::string aDescription)
{
   VixError err;
   VixHandle jobHandle = VIX_INVALID_HANDLE;
   VixHandle snapshotHandle = VIX_INVALID_HANDLE;
   jobHandle = VixVM_CreateSnapshot(mHandleVM,
      aNameSnapshot.c_str(),
      aDescription.c_str(),
      NULL,//VIX_SNAPSHOT_INCLUDE_MEMORY,
      VIX_INVALID_HANDLE,
      NULL, // *callbackProc,
      NULL); // *clientData);
   err = VixJob_Wait(jobHandle,
      VIX_PROPERTY_JOB_RESULT_HANDLE,
      &snapshotHandle,
      VIX_PROPERTY_NONE);
   Vix_ReleaseHandle(jobHandle);
   Vix_ReleaseHandle(snapshotHandle);
   CHECK_AND_THROW(err);
}

CVix_Snapshot::Ptr CVix_VirtualMachine::GetSnapshot(int aIndex)
{
   VixError err;
   VixHandle snapshotHandle = VIX_INVALID_HANDLE;

   err = VixVM_GetRootSnapshot(mHandleVM, aIndex, &snapshotHandle);
   CHECK_AND_THROW(err);
   return  CVix_Snapshot::Ptr(new CVix_Snapshot(mHandleVM, snapshotHandle));
}

CVix_Snapshot::Ptr CVix_VirtualMachine::GetSnapshot(std::string aNameSnapshot)
{
   VixError err;
   VixHandle snapshotHandle = VIX_INVALID_HANDLE;
   err = VixVM_GetNamedSnapshot(mHandleVM, aNameSnapshot.c_str(), &snapshotHandle);
   CHECK_AND_THROW(err);
   return  CVix_Snapshot::Ptr(new CVix_Snapshot(mHandleVM, snapshotHandle));
}

void CVix_VirtualMachine::RemoveSnapshot(std::string aNameSnapshot)
{
   VixError err;
   VixHandle jobHandle = VIX_INVALID_HANDLE;
   VixHandle snapshotHandle = VIX_INVALID_HANDLE;
   err = VixVM_GetNamedSnapshot(mHandleVM, aNameSnapshot.c_str(), &snapshotHandle);
   if (VIX_FAILED(err))
   {
      Vix_ReleaseHandle(snapshotHandle);
      THROW_ERROR(err);
   }

   jobHandle = VixVM_RemoveSnapshot(mHandleVM,
      snapshotHandle,
      0, // options
      NULL, // callbackProc
      NULL); // clientData
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   Vix_ReleaseHandle(jobHandle);
   Vix_ReleaseHandle(snapshotHandle);
   CHECK_AND_THROW(err);
}

//------------------------------------------------------------------------------
CVix_Host::CVix_Host()
:mHadleHost(VIX_INVALID_HANDLE)
{
   VixError err;
   VixHandle jobHandle = VIX_INVALID_HANDLE;
   jobHandle = VixHost_Connect(VIX_API_VERSION,
      CONNTYPE,
      HOSTNAME, // *hostName,
      HOSTPORT, // hostPort,
      USERNAME, // *userName,
      PASSWORD, // *password,
      0, // options,
      VIX_INVALID_HANDLE, // propertyListHandle,
      NULL, // *callbackProc,
      NULL); // *clientData);
   err = VixJob_Wait(jobHandle,
      VIX_PROPERTY_JOB_RESULT_HANDLE,
      &mHadleHost,
      VIX_PROPERTY_NONE);
   Vix_ReleaseHandle(jobHandle);
   CHECK_AND_THROW(err);
}

CVix_Host::~CVix_Host()
{
   VixHost_Disconnect(mHadleHost);
}

CVix_VirtualMachine::Ptr CVix_Host::GetVM(std::string aFileNameVM)
{
   VixError err;
   VixHandle vmHandle = VIX_INVALID_HANDLE;
   VixHandle jobHandle = VIX_INVALID_HANDLE;
   jobHandle = VixVM_Open(mHadleHost,
      aFileNameVM.c_str(),
      NULL, // VixEventProc *callbackProc,
      NULL); // void *clientData);
   err = VixJob_Wait(jobHandle,
      VIX_PROPERTY_JOB_RESULT_HANDLE,
      &vmHandle,
      VIX_PROPERTY_NONE);
   Vix_ReleaseHandle(jobHandle);
   CHECK_AND_THROW(err);
   return CVix_VirtualMachine::Ptr(new CVix_VirtualMachine(vmHandle));
}