#ifndef _I_PARTITION_H_
#define _I_PARTITION_H_

#include "..\tools\DSmartPtr.h"
#include ".\IMarshal.h"

class IPartitionMeta
	:public IMarshalObject
{
public:
	typedef SmartPtr<IPartitionMeta>::Ptr Ptr;

public:
	~IPartitionMeta(){}

	virtual bool IsBoot() = 0;
	virtual UINT8 GetTypePart() = 0;
	virtual UINT32 GetSizeInSector() = 0;

	static IPartitionMeta::Ptr LoadFromBuffer(UINT8* aBuffer, UINT32 aSize);
};
#endif