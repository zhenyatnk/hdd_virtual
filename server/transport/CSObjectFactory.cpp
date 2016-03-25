#include "CSObjectFactory.h"
#include "./../../common/tools/ISocket.h"
#include "../vm_tools/vix_objects.h"
#include "../hdd_info/hdd_info_tools.h"

class CServerFactory
   :public IObjectFactory
{
public:
   CServerFactory(std::string aFileNameVM);

   virtual std::vector<CPartitionMeta::Ptr> CreatePartitionsMeta();

private:
   std::string mFileNameVM;
};

CServerFactory::CServerFactory(std::string aFileNameVM)
:mFileNameVM(aFileNameVM)
{}

std::vector<CPartitionMeta::Ptr> CServerFactory::CreatePartitionsMeta()
{
   std::vector<CPartitionMeta::Ptr> lContainerPartition;
   std::string lSnapshotName = "VM_SNAP_HDD_INFO";
   std::string lLoadSnap = "";
   CVix_Host lHost;
   CVix_VirtualMachine::Ptr lVM = lHost.GetVM(mFileNameVM);
   std::vector<std::string> lContainerFileVMDK = GetNameFilesVMDK(mFileNameVM);
   bool lVMRun = lVM->IsPowerOn();
   if (lVMRun) 
   {
      lVM->AddSnapshot(lSnapshotName, lSnapshotName);
      lLoadSnap = lSnapshotName;
   }
    CVix_DiskLibrary lDiskLib;
    if (lDiskLib.Connect(lLoadSnap))
   {
      for (std::vector<std::string>::iterator lFileVMDk = lContainerFileVMDK.begin(); lFileVMDk != lContainerFileVMDK.end(); ++lFileVMDk)
      {
         CVix_VirtualDisk::Ptr lDisk = lDiskLib.GetVirtualDisk(*lFileVMDk);
         std::vector<CPartitionMeta::Ptr> lContainerPartitionVMDK = GetContainerPartitionMeta(lDisk);

         for (std::vector<CPartitionMeta::Ptr>::iterator lIterator = lContainerPartitionVMDK.begin(); lIterator != lContainerPartitionVMDK.end(); ++lIterator)
            lContainerPartition.push_back(*lIterator);
      }
   }
   if (lVMRun) lVM->RemoveSnapshot(lSnapshotName);
   return lContainerPartition;
   return std::vector<CPartitionMeta::Ptr>();
}

//----------------------------------------------------------------------------
IObjectFactory::Ptr CreateServerFactory(std::string aFileNameVM)
{
   return IObjectFactory::Ptr(new CServerFactory(aFileNameVM));
}