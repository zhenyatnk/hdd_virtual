#ifndef _I_OBJECT_FACTORY_H_
#define _I_OBJECT_FACTORY_H_

#include "IPartitionMeta.h"
#include <vector>

class IObjectFactory
{
public:
   typedef SmartPtr<IObjectFactory>::Ptr Ptr;
public:
	virtual ~IObjectFactory(){}

   virtual IPartitionMeta::Ptr CreatePartitionMeta(UINT8 aIndex) = 0;
   virtual std::vector<IPartitionMeta::Ptr> CreatePartitionsMeta() = 0;
};

#endif