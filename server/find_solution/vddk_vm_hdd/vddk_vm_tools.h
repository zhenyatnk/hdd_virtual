#ifndef _VDDK_VM_TOOLS_H_
#define _VDDK_VM_TOOLS_H_

#include <windows.h>
#include <memory>
#include <string>
#include <vector>

#include "vixDiskLib.h"

//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
class CVix_VirtualDisk
{
public:
   typedef std::shared_ptr<CVix_VirtualDisk> Ptr;
   friend class CVix_DiskLibrary;

private:
   CVix_VirtualDisk(VixDiskLibConnection aConnectionParms, const char *aPathVirtualDisk, uint32 aFlagsOpen);

public:
   ~CVix_VirtualDisk();

   std::vector<TPartitionMeta> GetMetaPartitions();

private:
   VixDiskLibHandle mHandleVirtualDisk;
};
//------------------------------------------------------------------------------
class CVix_DiskLibrary
{
public:
   CVix_DiskLibrary();
   ~CVix_DiskLibrary();

   bool Connect();
   bool Connect(VixDiskLibConnectParams aParms);

   CVix_VirtualDisk::Ptr GetVirtualDisk(std::string aDiskPath);

private:
   void Disconnect();

private:
   VixDiskLibConnection mConnection;
};
//------------------------------------------------------------------------------
#endif