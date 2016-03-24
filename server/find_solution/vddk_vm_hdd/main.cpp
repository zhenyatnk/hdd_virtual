#include <map>
#include "vddk_vm_tools.h"

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
   CVix_DiskLibrary lDiskLib;
   if (lDiskLib.Connect())
   {
      //CVix_VirtualDisk::Ptr lDisk = lDiskLib.GetVirtualDisk("E:\\VirtualM\\Ubuntu 64-bit\\Ubuntu 64-bit (2).vmdk");
      CVix_VirtualDisk::Ptr lDisk = lDiskLib.GetVirtualDisk("E:\\tmp\\vm\\Windows 8 x64.vmdk");
      
//      PrintPartitionMetainf(lDiskLib.GetMetaPartitions("E:\\VM_ Machine\\Windows 10\\Windows 10 x64.vmdk"));
//      printf("\n");
//      PrintPartitionMetainf(lDiskLib.GetMetaPartitions("E:\\VM_ Machine\\Kubuntu\\Ubuntu 64-bit.vmdk"));
      PrintPartitionMetainf(lDisk->GetMetaPartitions());

   }
   return 0;
}