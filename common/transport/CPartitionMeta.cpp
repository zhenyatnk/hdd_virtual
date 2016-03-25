#include ".\CPartitionMeta.h"

//------------------------------------------------------------------------------
CPartitionMeta::CPartitionMeta(bool aIsBoot, bool aIsExtend, V_UINT8 aType, V_UINT32 aSize)
:mIsBoot(aIsBoot), mIsExtend(aIsExtend), mType(aType), mSize(aSize)
{}

bool CPartitionMeta::IsBoot()
{
   return mIsBoot;
}

bool CPartitionMeta::IsExtend()
{
   return mIsExtend;
}

V_UINT8 CPartitionMeta::GetTypePart()
{
   return mType;
}
V_UINT32 CPartitionMeta::GetSizeInSector()
{
   return mSize;
}
//------------------------------------------------------------------------------
std::string ConvertTypeSystem(V_UINT8 aTypeSystem)
{
   switch (aTypeSystem)
   {
   case 0x00: return "Empty";
   case 0x01: return "FAT12";
   case 0x04: return "FAT16 <32M";
   case 0x05: return "Extended";
   case 0x06: return "FAT16";
   case 0x0b: return "FAT32";
   case 0x0c: return "FAT32 (LBA)";
   case 0x0e: return "FAT16 (LBA)";
   case 0x0f: return "Win Ext'd (LBA)";
   case 0x82: return "Linux swap";
   case 0x83: return "Linux";
   case 0x85: return "Linux extended";
   case 0x07: return "HPFS/NTFS";
   default: return "unknow";
   }
}
