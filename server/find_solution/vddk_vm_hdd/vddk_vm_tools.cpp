#include "vddk_vm_tools.h"

//------------------------------------------------------------------------------
#define VIXDISKLIB_VERSION_MAJOR 6
#define VIXDISKLIB_VERSION_MINOR 0
//------------------------------------------------------------------------------
VixDiskLibErrWrapper::VixDiskLibErrWrapper(VixError aErrorCode, const char* aFile, int aLine)
: mErrorCode(aErrorCode), mFile(aFile), mLine(aLine)
{
   char* lMessage = VixDiskLib_GetErrorText(mErrorCode, NULL);
   mDescription = lMessage;
   VixDiskLib_FreeErrorText(lMessage);
}

VixDiskLibErrWrapper::VixDiskLibErrWrapper(const char* aDescription, const char* aFile, int aLine)
:mErrorCode(VIX_E_FAIL), mDescription(aDescription), mFile(aFile), mLine(aLine)
{ }

std::string VixDiskLibErrWrapper::Description() const
{
   return mDescription;
}

VixError VixDiskLibErrWrapper::ErrorCode() const
{
   return mErrorCode;
}

std::string VixDiskLibErrWrapper::File() const
{
   return mFile;
}

int VixDiskLibErrWrapper::Line() const
{
   return mLine;
}
//------------------------------------------------------------------------------
#define THROW_ERROR(vixError) \
   throw VixDiskLibErrWrapper((vixError), __FILE__, __LINE__)

#define CHECK_AND_THROW(vixError)\
do\
{\
if (VIX_FAILED((vixError))) \
{ \
   throw VixDiskLibErrWrapper((vixError), __FILE__, __LINE__); \
}                                                              \
} while (0)

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
   {
      THROW_ERROR(vixError);
   }
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