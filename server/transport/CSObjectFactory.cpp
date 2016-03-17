#include "CSObjectFactory.h"
#include "./../../common/tools/ISocket.h"

class CServerFactory
   :public IObjectFactory
{
   public:
   CServerFactory();

   virtual CPartitionMeta::Ptr CreatePartitionMeta(UINT8 aIndex);
   virtual std::vector<CPartitionMeta::Ptr> CreatePartitionsMeta();
   
};

CServerFactory::CServerFactory()
{}

CPartitionMeta::Ptr CServerFactory::CreatePartitionMeta(UINT8 aIndex)
{
   CPartitionMeta::Ptr lPartMeta;
   return lPartMeta;
}

std::vector<CPartitionMeta::Ptr> CServerFactory::CreatePartitionsMeta()
{
   return std::vector<CPartitionMeta::Ptr>();
}

//----------------------------------------------------------------------------
IObjectFactory::Ptr CreateServerFactory()
{
	return IObjectFactory::Ptr(new CServerFactory());
}