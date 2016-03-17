#ifndef _I_MARSHAL_H_
#define _I_MARSHAL_H_

#include "..\tools\TypeDef.h"

class IMarshalObject
{
public:
	virtual ~IMarshalObject()	{}

	virtual UINT8* GetBuffer() = 0;
	virtual UINT32 GetSize() = 0;

	static char* GetNameObject();
};

#endif