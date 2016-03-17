﻿#ifndef _I_OBJECT_FACTORY_H_
#define _I_OBJECT_FACTORY_H_

#include "CPartitionMeta.h"
#include <vector>

class IObjectFactory
{
public:
   typedef SmartPtr<IObjectFactory>::Ptr Ptr;
public:
	virtual ~IObjectFactory(){}

   virtual CPartitionMeta::Ptr CreatePartitionMeta(UINT8 aIndex) = 0;
   virtual std::vector<CPartitionMeta::Ptr> CreatePartitionsMeta() = 0;
};

#endif