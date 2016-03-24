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
CVixSnapshot::CVixSnapshot(VixHandle aHandleVM, VixHandle aHandleShapshot)
:mHandleVM(aHandleVM), mHandleShapshot(aHandleShapshot)
{
   if (mHandleVM == VIX_INVALID_HANDLE ||
      mHandleShapshot == VIX_INVALID_HANDLE)
      throw vm_exception("Cannot get snapshot.");
}

CVixSnapshot::~CVixSnapshot()
{
   Vix_ReleaseHandle(mHandleShapshot);
}

std::string CVixSnapshot::GetNameSnapshot()
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

VixHandle CVixSnapshot::GetHandle()
{
   return mHandleShapshot;
}

//------------------------------------------------------------------------------
CVixVirtualMachine::CVixVirtualMachine(VixHandle aHandleVM)
:mHandleVM(aHandleVM)
{
   if (mHandleVM == VIX_INVALID_HANDLE)
      throw vm_exception("Cannot get virtal machine.");
}

CVixVirtualMachine::~CVixVirtualMachine()
{
   Vix_ReleaseHandle(mHandleVM);
}

bool CVixVirtualMachine::IsPowerOn()
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

void CVixVirtualMachine::Pause()
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

void CVixVirtualMachine::UnPause()
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

int CVixVirtualMachine::GetNumSnapshots()
{
   VixError err;
   int numSnapshots;
   err = VixVM_GetNumRootSnapshots(mHandleVM, &numSnapshots);
   CHECK_AND_THROW(err);
   return numSnapshots;
}

void CVixVirtualMachine::AddSnapshot(std::string aNameSnapshot, std::string aDescription)
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

CVixSnapshot::Ptr CVixVirtualMachine::GetSnapshot(int aIndex)
{
   VixError err;
   VixHandle snapshotHandle = VIX_INVALID_HANDLE;

   err = VixVM_GetRootSnapshot(mHandleVM, aIndex, &snapshotHandle);
   CHECK_AND_THROW(err);
   return  CVixSnapshot::Ptr(new CVixSnapshot(mHandleVM, snapshotHandle));
}

CVixSnapshot::Ptr CVixVirtualMachine::GetSnapshot(std::string aNameSnapshot)
{
   VixError err;
   VixHandle snapshotHandle = VIX_INVALID_HANDLE;
   err = VixVM_GetNamedSnapshot(mHandleVM, aNameSnapshot.c_str(), &snapshotHandle);
   CHECK_AND_THROW(err);
   return  CVixSnapshot::Ptr(new CVixSnapshot(mHandleVM, snapshotHandle));
}

void CVixVirtualMachine::RemoveSnapshot(std::string aNameSnapshot)
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
CVixHost::CVixHost()
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

CVixHost::~CVixHost()
{
   VixHost_Disconnect(mHadleHost);
}

CVixVirtualMachine::Ptr CVixHost::GetVM(std::string aFileNameVM)
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
   return CVixVirtualMachine::Ptr(new CVixVirtualMachine(vmHandle));
}