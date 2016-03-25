#include "CSObjectFactory.h"
#include "./../../common/tools/ISocket.h"
#include "../vm_tools/vix_objects.h"
#include "../hdd_info/hdd_info_tools.h"

class CServerFactory
   :public IObjectFactory
{
public:
   CServerFactory(std::string aFileNameVM, std::string aFileVirtualDisk);

   virtual std::vector<CPartitionMeta::Ptr> CreatePartitionsMeta();

private:
   std::string mFileNameVM;
   std::string mFileVirtualDisk;
};

CServerFactory::CServerFactory(std::string aFileNameVM, std::string aFileVirtualDisk)
:mFileNameVM(aFileNameVM), mFileVirtualDisk(aFileVirtualDisk)
{}

std::vector<CPartitionMeta::Ptr> CServerFactory::CreatePartitionsMeta()
{
   std::vector<CPartitionMeta::Ptr> lContainerPartition;
   std::string lSnapshotName = "VM_SNAP_HDD_INFO";
   CVix_Host lHost;
   CVix_VirtualMachine::Ptr lVM = lHost.GetVM(mFileNameVM);
   bool lVMRun = lVM->IsPowerOn();
   if (lVMRun) lVM->AddSnapshot(lSnapshotName, lSnapshotName);
   CVix_DiskLibrary lDiskLib;
   if (lDiskLib.Connect())
   {
      CVix_VirtualDisk::Ptr lDisk = lDiskLib.GetVirtualDisk(mFileVirtualDisk);
      lContainerPartition = GetContainerPartitionMeta(lDisk);
   }
   if (lVMRun) lVM->RemoveSnapshot(lSnapshotName);
   return lContainerPartition;
   return std::vector<CPartitionMeta::Ptr>();
}

//----------------------------------------------------------------------------
IObjectFactory::Ptr CreateServerFactory(std::string aFileNameVM, std::string aFileVirtualDisk)
{
   return IObjectFactory::Ptr(new CServerFactory(aFileNameVM, aFileVirtualDisk));
}