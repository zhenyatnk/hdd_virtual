#include <windows.h>
#include <tchar.h>
#include <process.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include "vixDiskLib.h"

std::map<UINT16, std::wstring> CreateFileSysMap()
{
   std::map<UINT16, std::wstring> file_sys_types;
   file_sys_types[0x00] = L"Empty";
   file_sys_types[0x01] = L"FAT12";
   file_sys_types[0x04] = L"FAT16 <32M";
   file_sys_types[0x05] = L"Extended";
   file_sys_types[0x06] = L"FAT16";
   file_sys_types[0x0b] = L"FAT32";
   file_sys_types[0x0c] = L"FAT32 (LBA)";
   file_sys_types[0x0e] = L"FAT16 (LBA)";
   file_sys_types[0x0f] = L"Win Ext'd (LBA)";
   file_sys_types[0x82] = L"Linux swap";
   file_sys_types[0x83] = L"Linux";
   file_sys_types[0x85] = L"Linux extended";
   file_sys_types[0x07] = L"HPFS/NTFS";
   return file_sys_types;
}

std::map<UINT16, std::wstring>& GetFileSysMap()
{
   static std::map<UINT16, std::wstring> file_sys_types = CreateFileSysMap();
   return file_sys_types;
}

class VixDiskLibErrWrapper
{
public:
   explicit VixDiskLibErrWrapper(VixError errCode, const char* file, int line)
      :
      _errCode(errCode),
      _file(file),
      _line(line)
   {
      char* msg = VixDiskLib_GetErrorText(errCode, NULL);
      _desc = msg;
      VixDiskLib_FreeErrorText(msg);
   }

   VixDiskLibErrWrapper(const char* description, const char* file, int line)
      :
      _errCode(VIX_E_FAIL),
      _desc(description),
      _file(file),
      _line(line)
   {
   }

   std::string Description() const { return _desc; }
   VixError ErrorCode() const { return _errCode; }
   std::string File() const { return _file; }
   int Line() const { return _line; }

private:
   VixError _errCode;
   std::string _desc;
   std::string _file;
   int _line;
};

#define THROW_ERROR(vixError) \
   throw VixDiskLibErrWrapper((vixError), __FILE__, __LINE__)

#define CHECK_AND_THROW(vixError)                                    \
do {\
if (VIX_FAILED((vixError))) {   \
   throw VixDiskLibErrWrapper((vixError), __FILE__, __LINE__); \
}                                                              \
} while (0)

class CGlobals
{
private:
   struct TGlobals
   {
      int command;
      VixDiskLibAdapterType adapterType;
      char *transportModes;
      char *diskPath;
      char *parentPath;
      char *metaKey;
      char *metaVal;
      int filler;
      unsigned mbSize;
      VixDiskLibSectorType numSectors;
      VixDiskLibSectorType startSector;
      VixDiskLibSectorType bufSize;
      uint32 openFlags;
      unsigned numThreads;
      Bool success;
      Bool isRemote;
      char *host;
      char *userName;
      char *password;
      char *thumbPrint;
      int port;
      char *srcPath;
      VixDiskLibConnection connection;
      char *vmxSpec;
      bool useInitEx;
      char *cfgFile;
      char *libdir;
      char *ssMoRef;
      int repair;
   };

public:
   CGlobals()
   {
      memset(&mGlobals, 0, sizeof(TGlobals));
      mGlobals.command = 0;
      mGlobals.adapterType = VIXDISKLIB_ADAPTER_SCSI_BUSLOGIC;
      mGlobals.startSector = 0;
      mGlobals.numSectors = 1;
      mGlobals.mbSize = 100;
      mGlobals.filler = 0xff;
      mGlobals.openFlags = VIXDISKLIB_FLAG_OPEN_READ_ONLY;
      mGlobals.numThreads = 1;
      mGlobals.success = TRUE;
      mGlobals.isRemote = FALSE;
   }
   TGlobals& GetGlobals()
   {
      return mGlobals;
   }

private:
   TGlobals mGlobals;
};


VixDiskLibConnectParams CreateConnectParms(CGlobals aGlob)
{
   VixDiskLibConnectParams cnxParams = { 0 };
   if (aGlob.GetGlobals().isRemote)
   {
      cnxParams.vmxSpec = aGlob.GetGlobals().vmxSpec;
      cnxParams.serverName = aGlob.GetGlobals().host;
      cnxParams.credType = VIXDISKLIB_CRED_UID;
      cnxParams.creds.uid.userName = aGlob.GetGlobals().userName;
      cnxParams.creds.uid.password = aGlob.GetGlobals().password;
      cnxParams.thumbPrint = aGlob.GetGlobals().thumbPrint;
      cnxParams.port = aGlob.GetGlobals().port;
   }
   return cnxParams;
}

class VixDisk
{
public:

   VixDiskLibHandle Handle() { return _handle; }
   VixDisk(VixDiskLibConnection connection, const char *path, uint32 flags)
   {
      _handle = NULL;
      VixError vixError = VixDiskLib_Open(connection, path, flags, &_handle);
      CHECK_AND_THROW(vixError);
   }

   ~VixDisk()
   {
      if (_handle) {
         VixDiskLib_Close(_handle);
      }
      _handle = NULL;
   }

private:
   VixDiskLibHandle _handle;
};

#pragma pack(push,1)
struct TPartitionMeta {
   UINT8 bootable;
   UINT8 start_part[3];
   UINT8 type_part;
   UINT8 end_part[3];
   UINT32 sect_before;
   UINT32 sect_total;
};
#pragma pack(pop)

#define VIXDISKLIB_VERSION_MAJOR 6
#define VIXDISKLIB_VERSION_MINOR 0

class CVixDiskLib
{
public:
   CVixDiskLib(CGlobals aGlob)
      :mGlobals(aGlob)
   {
      VixError vixError;
      if (mGlobals.GetGlobals().useInitEx)
      {
         vixError = VixDiskLib_InitEx(VIXDISKLIB_VERSION_MAJOR,
            VIXDISKLIB_VERSION_MINOR,
            NULL, NULL, NULL,
            mGlobals.GetGlobals().libdir,
            mGlobals.GetGlobals().cfgFile);
      }
      else
      {
         vixError = VixDiskLib_Init(VIXDISKLIB_VERSION_MAJOR,
            VIXDISKLIB_VERSION_MINOR,
            NULL, NULL, NULL, // Log, warn, panic
            mGlobals.GetGlobals().libdir);
      }
   };

   ~CVixDiskLib()
   {
      VixError vixError;
      if (mGlobals.GetGlobals().vmxSpec != NULL)
         vixError = VixDiskLib_EndAccess(&CreateConnectParms(mGlobals), "Sample");
      if (mGlobals.GetGlobals().connection != NULL)
         VixDiskLib_Disconnect(mGlobals.GetGlobals().connection);
      VixDiskLib_Exit();
   }

   bool Connect()
   {
      return Connect(CreateConnectParms(mGlobals));
   }
   bool Connect(VixDiskLibConnectParams aParms)
   {
      VixError vixError;
      if (mGlobals.GetGlobals().vmxSpec != NULL)
      {
         vixError = VixDiskLib_PrepareForAccess(&aParms, "Sample");
         CHECK_AND_THROW(vixError);
      }
      if (mGlobals.GetGlobals().ssMoRef == NULL && mGlobals.GetGlobals().transportModes == NULL)
      {
         vixError = VixDiskLib_Connect(&aParms,
            &mConnection);
      }
      else
      {
         Bool ro = (mGlobals.GetGlobals().openFlags & VIXDISKLIB_FLAG_OPEN_READ_ONLY);
         vixError = VixDiskLib_ConnectEx(&aParms, ro, mGlobals.GetGlobals().ssMoRef,
            mGlobals.GetGlobals().transportModes,
            &mConnection);
      }
      return VIX_SUCCEEDED(vixError);
   }


public:
   std::vector<TPartitionMeta> GetMetaPartitions(std::string aDiskPath)
   {
      std::vector<TPartitionMeta> lPartMeta(4);
      lPartMeta.reserve(4);
      VixDisk disk(mConnection, aDiskPath.c_str(), mGlobals.GetGlobals().openFlags);
      uint8 Sector0[512];
      VixError vixError = VixDiskLib_Read(disk.Handle(), 0, 1, Sector0);
      if (vixError != VIX_OK && vixError != VIX_E_BUFFER_TOOSMALL)
      {
         THROW_ERROR(vixError);
      }
      memset((void *)&lPartMeta[0], 0, (sizeof(TPartitionMeta)* lPartMeta.size()));
      memcpy((void *)&lPartMeta[0], Sector0 + 0x1BE, (sizeof(TPartitionMeta)* lPartMeta.size()));
      return lPartMeta;
   }

private:
   void InitLib();

private:
   VixDiskLibConnection mConnection;
   CGlobals mGlobals;
};

void PrintPartitionMetainf(std::vector<TPartitionMeta> aPartsMeta)
{

   printf("\nBootable\tStart\tTotal\t\tTotalGB\t\tId\tType\n");
   for (std::vector<TPartitionMeta>::iterator lIteratorInf = aPartsMeta.begin(); lIteratorInf != aPartsMeta.end(); ++lIteratorInf)
   {
      if (!lIteratorInf->type_part)
         continue;

      if (lIteratorInf->bootable == 0x80) printf("*\t");
      else printf("\t");

      printf("%12u\t", lIteratorInf->sect_before);
      printf("%8u\t\t", lIteratorInf->sect_total);
      printf("%4u\t", (UINT32)round(double(lIteratorInf->sect_total) / (2048 * 1024)));
      printf("0x%.2X\t", lIteratorInf->type_part);
      wprintf(L"%s\n", GetFileSysMap()[lIteratorInf->type_part].c_str());
   }

}
int main(int argc, char* argv[])
{
   CVixDiskLib lDiskLib = CGlobals();
   if (lDiskLib.Connect())
   {
      PrintPartitionMetainf(lDiskLib.GetMetaPartitions("E:\\VirtualM\\Ubuntu 64-bit\\Ubuntu 64-bit (2).vmdk"));
//      PrintPartitionMetainf(lDiskLib.GetMetaPartitions("E:\\VM_ Machine\\Windows 10\\Windows 10 x64.vmdk"));
//      printf("\n");
//      PrintPartitionMetainf(lDiskLib.GetMetaPartitions("E:\\VM_ Machine\\Kubuntu\\Ubuntu 64-bit.vmdk"));

   }
   return 0;
}