#include "vddk_vm_tools.h"
#include "../../../common/tools/CExceptions.h"

//------------------------------------------------------------------------------
#define VIXDISKLIB_VERSION_MAJOR 6
#define VIXDISKLIB_VERSION_MINOR 0
//------------------------------------------------------------------------------
std::string GetVDDKErrorMessage(VixError aErrorCode)
{
   char* lMessage = VixDiskLib_GetErrorText(aErrorCode, NULL);
   std::string str = lMessage;
   VixDiskLib_FreeErrorText(lMessage);
   return str;
}
//------------------------------------------------------------------------------
#define THROW_ERROR(vixError) \
   throw vm_exception(GetVDDKErrorMessage(vixError));

#define CHECK_AND_THROW(vixError)\
if (VIX_FAILED((vixError))) \
{ \
   throw vm_exception(GetVDDKErrorMessage(vixError)); \
}

//------------------------------------------------------------------------------
CVix_VirtualDisk::CVix_VirtualDisk(VixDiskLibConnection aConnectionParms, const char *aPathVirtualDisk, uint32 aFlagsOpen)
:mHandleVirtualDisk(NULL)
{
   VixError vixError = VixDiskLib_Open(aConnectionParms, aPathVirtualDisk, aFlagsOpen, &mHandleVirtualDisk);
   CHECK_AND_THROW(vixError);
}

CVix_VirtualDisk::~CVix_VirtualDisk()
{
   if (mHandleVirtualDisk)
      VixDiskLib_Close(mHandleVirtualDisk);
   mHandleVirtualDisk = NULL;
}

TBuffer<VIXDISKLIB_SECTOR_SIZE>::Ptr CVix_VirtualDisk::ReadSector(uint32 aNumberSector)
{
   TBuffer<VIXDISKLIB_SECTOR_SIZE>::Ptr lBuffer(new TBuffer<VIXDISKLIB_SECTOR_SIZE>());
   VixError vixError = VixDiskLib_Read(mHandleVirtualDisk, aNumberSector, 1, (uint8*)lBuffer->GetData());
   CHECK_AND_THROW(vixError);
   return lBuffer;
}

//------------------------------------------------------------------------------
CVix_DiskLibrary::CVix_DiskLibrary()
:mConnection(NULL)
{
   VixError vixError;
   vixError = VixDiskLib_Init(VIXDISKLIB_VERSION_MAJOR,
      VIXDISKLIB_VERSION_MINOR,
      NULL, NULL, NULL, NULL);
};

CVix_DiskLibrary::~CVix_DiskLibrary()
{
   Disconnect();
   VixDiskLib_Exit();
}

bool CVix_DiskLibrary::Connect(std::string aNameVM)
{
   VixDiskLibConnectParams cnxParams = { 0 };
   if (!aNameVM.empty())
   {
      cnxParams.vmxSpec = new char(aNameVM.size() + 1);
      memset(cnxParams.vmxSpec, 0, aNameVM.size() + 1);
      strcpy(cnxParams.vmxSpec, aNameVM.c_str());
   }
   return Connect(cnxParams);
}
bool CVix_DiskLibrary::Connect(VixDiskLibConnectParams aParms)
{
   Disconnect();
   VixError vixError;
   vixError = VixDiskLib_Connect(&aParms,
      &mConnection);
   return VIX_SUCCEEDED(vixError);
}

CVix_VirtualDisk::Ptr CVix_DiskLibrary::GetVirtualDisk(std::string aDiskPath)
{
   CVix_VirtualDisk::Ptr lVirtualDisk;
   if (!!mConnection || Connect())
      lVirtualDisk = CVix_VirtualDisk::Ptr(new CVix_VirtualDisk(mConnection, aDiskPath.c_str(), VIXDISKLIB_FLAG_OPEN_READ_ONLY));
   return lVirtualDisk;
}

void CVix_DiskLibrary::Disconnect()
{
   if (mConnection != NULL)
      VixDiskLib_Disconnect(mConnection);
}
//------------------------------------------------------------------------------