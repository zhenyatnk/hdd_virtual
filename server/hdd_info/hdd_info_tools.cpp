#include <iostream>
#include "../../common/tools/CExceptions.h"
#include "../vm_tools/vix_objects.h"
#include "../vm_tools/vddk_vm_tools.h"
#include "hdd_info_tools.h"

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
unsigned int GetCountPartition(char* aSector0)
{
   unsigned int lCountPart = 0;
   TPartitionMeta* aParitionMeta = (TPartitionMeta*)aSector0;
   while (!!(aParitionMeta++)->type_part && lCountPart <= 4)
   {
      ++lCountPart;
   }
   return lCountPart;
}
//------------------------------------------------------------------------------
std::vector<CPartitionMeta::Ptr> GetContainerPartitionMeta(char* aSector0)
{
   std::vector<CPartitionMeta::Ptr> lContainerPartition;
   std::vector<TPartitionMeta> lPartMeta(GetCountPartition(aSector0));
   memset((void *)&lPartMeta[0], 0, (sizeof(TPartitionMeta)* lPartMeta.size()));
   memcpy((void *)&lPartMeta[0], aSector0 + 0x1BE, (sizeof(TPartitionMeta)* lPartMeta.size()));

   return lContainerPartition;
}

std::vector<CPartitionMeta::Ptr> GetContainerPartitionMeta(std::string aFileNameVM, std::string aFileVirtualDisk)
{
   std::vector<CPartitionMeta::Ptr> lContainerPartition;
   std::string lSnapshotName = "VM_SNAP_HDD_INFO";
   CVixHost lHost;
   CVixVirtualMachine::Ptr lVM = lHost.GetVM(aFileNameVM);
   bool lVMRun = lVM->IsPowerOn();
   if (lVMRun) lVM->AddSnapshot(lSnapshotName, lSnapshotName);
   CVix_DiskLibrary lDiskLib;
   if (lDiskLib.Connect(aFileNameVM))
   {
      CVix_VirtualDisk::Ptr lDisk = lDiskLib.GetVirtualDisk(aFileVirtualDisk);
      GetContainerPartitionMeta(lDisk->ReadSector(0)->GetData());
   }
   if (lVMRun) lVM->RemoveSnapshot(lSnapshotName);
   return lContainerPartition;
}
//------------------------------------------------------------------------------