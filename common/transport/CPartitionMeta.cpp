#include ".\CPartitionMeta.h"

CPartitionMeta::CPartitionMeta(bool aIsBoot, UINT8 aType, UINT32 aSize)
:mIsBoot(aIsBoot), mType(aType), mSize(aSize)
{}

bool CPartitionMeta::IsBoot()
{
   return mIsBoot;
}

UINT8 CPartitionMeta::GetTypePart()
{
   return mType;
}
UINT32 CPartitionMeta::GetSizeInSector()
{
   return mSize;
}