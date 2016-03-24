#include "vix_objects.h"
#include "../../../common/tools/CExceptions.h"

//------------------------------------------------------------------------------
#define  CONNTYPE    VIX_SERVICEPROVIDER_VMWARE_WORKSTATION
#define  HOSTNAME ""
#define  HOSTPORT 0
#define  USERNAME ""
#define  PASSWORD ""
//------------------------------------------------------------------------------
std::vector <std::string> gContainerNames;
//------------------------------------------------------------------------------
void VixAgregatorNamesProc(VixHandle jobHandle, VixEventType eventType, VixHandle moreEventInfo, void *clientData)
{
   VixError err = VIX_OK;
   char *url = NULL;

   if (VIX_EVENTTYPE_FIND_ITEM != eventType)
      return;

   // Found a virtual machine.
   err = Vix_GetProperties(moreEventInfo,
      VIX_PROPERTY_FOUND_ITEM_LOCATION,
      &url,
      VIX_PROPERTY_NONE);
   if (VIX_FAILED(err))
   {
      Vix_FreeBuffer(url);
      throw vm_exception_w(L"Ошибка установки паузы для виртуальной машины");
   }
   gContainerNames.push_back(std::string(url));
   Vix_FreeBuffer(url);
}

//------------------------------------------------------------------------------
CVixSnapshot::CVixSnapshot(VixHandle aHandleVM, VixHandle aHandleShapshot)
:mHandleVM(aHandleVM), mHandleShapshot(aHandleShapshot)
{
   if (mHandleVM == VIX_INVALID_HANDLE ||
      mHandleShapshot == VIX_INVALID_HANDLE)
      throw vm_exception_w(L"Ошибка получения метки состояния");
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
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка получения имени состояния");
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
      throw vm_exception_w(L"Ошибка создания объекта виртуальной машины");
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
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка получения состояния виртуальной машины");
   return VIX_POWERSTATE_POWERED_ON & lPowerState;
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
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка установки паузы для виртуальной машины");
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
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка снятия паузы для виртуальной машины");
}

int CVixVirtualMachine::GetNumSnapshots()
{
   VixError err;
   int numSnapshots;
   err = VixVM_GetNumRootSnapshots(mHandleVM, &numSnapshots);
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка выполнения операции получения количества сохраненных состояний");
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
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка создания метки состояния");
}

CVixSnapshot::Ptr CVixVirtualMachine::GetSnapshot(int aIndex)
{
   VixError err;
   VixHandle snapshotHandle = VIX_INVALID_HANDLE;

   err = VixVM_GetRootSnapshot(mHandleVM, aIndex, &snapshotHandle);
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка создания метки состояния");
   return  CVixSnapshot::Ptr(new CVixSnapshot(mHandleVM, snapshotHandle));
}

CVixSnapshot::Ptr CVixVirtualMachine::GetSnapshot(std::string aNameSnapshot)
{
   VixError err;
   VixHandle snapshotHandle = VIX_INVALID_HANDLE;
   err = VixVM_GetNamedSnapshot(mHandleVM, aNameSnapshot.c_str(), &snapshotHandle);
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка создания метки состояния");
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
      throw vm_exception_w(L"Ошибка получения состояния по имени");
   }

   jobHandle = VixVM_RemoveSnapshot(mHandleVM,
      snapshotHandle,
      0, // options
      NULL, // callbackProc
      NULL); // clientData
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   Vix_ReleaseHandle(jobHandle);
   Vix_ReleaseHandle(snapshotHandle);
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка удаления метки состояния");
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
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка соединения с хостом");
}

CVixHost::~CVixHost()
{
   VixHost_Disconnect(mHadleHost);
}

std::vector<std::string> CVixHost::GetNamesVMachines()
{
   gContainerNames = std::vector<std::string>();
   VixError err;
   VixHandle vmHandle = VIX_INVALID_HANDLE;
   VixHandle jobHandle = VIX_INVALID_HANDLE;
   jobHandle = VixHost_FindItems(mHadleHost,
      VIX_FIND_RUNNING_VMS,
      VIX_INVALID_HANDLE, // searchCriteria
      -1, // timeout
      VixAgregatorNamesProc,
      NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   Vix_ReleaseHandle(jobHandle);
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка выполения операции поиска зарегистрированных машин");
   return gContainerNames;
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
   if (VIX_FAILED(err))
      throw vm_exception_w(L"Ошибка открытия виртуальной машины");
   return CVixVirtualMachine::Ptr(new CVixVirtualMachine(vmHandle));
}