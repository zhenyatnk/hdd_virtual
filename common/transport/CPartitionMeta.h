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
	CPartitionMeta(bool aIsBoot, UINT8 aType, UINT32 aSize);

	bool IsBoot();
	UINT8 GetTypePart();
	UINT32 GetSizeInSector();

	NAME_CLASS(CPartitionMeta)

private:
	bool mIsBoot;
	UINT8 mType;
	UINT32 mSize;
};
#endif