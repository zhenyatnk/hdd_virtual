#ifndef _C_PARTITION_H_
#define _C_PARTITION_H_

#include "..\tools\DSmartPtr.h"
#include "..\tools\TypeDef.h"
#include <string>

class CPartitionMeta
{
public:
	typedef SmartPtr<CPartitionMeta>::Ptr Ptr;

public:
   CPartitionMeta(bool aIsBoot, bool aIsExtend, V_UINT8 aType, V_UINT32 aSize);

	bool IsBoot();
   bool IsExtend();
   V_UINT8 GetTypePart();
   V_UINT32 GetSizeInSector();

	NAME_CLASS(CPartitionMeta)

private:
   bool mIsExtend;
   bool mIsBoot;
   V_UINT8 mType;
   V_UINT32 mSize;
};

std::string ConvertTypeSystem(V_UINT8 aTypeSystem);

#endif