#include "vddk_vm_tools.h"
#include "../../../common/tools/CExceptions.h"

//------------------------------------------------------------------------------
#define VIXDISKLIB_VERSION_MAJOR 6
#define VIXDISKLIB_VERSION_MINOR 0
//------------------------------------------------------------------------------
std::wstring GetVixErrorMessage(VixError aErrorCode)
{
   char* lMessage = VixDiskLib_GetErrorText(aErrorCode, NULL);
   std::string str = lMessage;
   std::wstring lMessageWString = std::wstring(str.begin(), str.end());
   VixDiskLib_FreeErrorText(lMessage);
   return lMessageWString;
}
//------------------------------------------------------------------------------
#define THROW_ERROR(vixError) \
   throw vm_exception_w(GetVixErrorMessage(vixError));

#define CHECK_AND_THROW(vixError)\
if (VIX_FAILED((vixError))) \
{ \
   throw vm_exception_w(GetVixErrorMessage(vixError)); \
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

std::vector<TPartitionMeta> CVix_VirtualDisk::GetMetaPartitions()
{
   std::vector<TPartitionMeta> lPartMeta(4);
   lPartMeta.reserve(4);
   uint8 Sector0[512];
   VixError vixError = VixDiskLib_Read(mHandleVirtualDisk, 0, 1, Sector0);
   if (vixError != VIX_OK && vixError != VIX_E_BUFFER_TOOSMALL)
      THROW_ERROR(vixError);
   memset((void *)&lPartMeta[0], 0, (sizeof(TPartitionMeta)* lPartMeta.size()));
   memcpy((void *)&lPartMeta[0], Sector0 + 0x1BE, (sizeof(TPartitionMeta)* lPartMeta.size()));
   return lPartMeta;
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

bool CVix_DiskLibrary::Connect()
{
   VixDiskLibConnectParams cnxParams = { 0 };
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