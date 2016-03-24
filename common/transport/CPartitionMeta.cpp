#include ".\CPartitionMeta.h"

CPartitionMeta::CPartitionMeta(bool aIsBoot, V_UINT8 aType, V_UINT32 aSize)
   :mIsBoot(aIsBoot), mType(aType), mSize(aSize)
{}

bool CPartitionMeta::IsBoot()
{
   return mIsBoot;
}

V_UINT8 CPartitionMeta::GetTypePart()
{
   return mType;
}
V_UINT32 CPartitionMeta::GetSizeInSector()
{
   return mSize;
}