#include "CSObjectFactory.h"
#include "./../../common/tools/ISocket.h"

class CServerFactory
   :public IObjectFactory
{
   public:
   CServerFactory();

   virtual IPartitionMeta::Ptr CreatePartitionMeta(UINT8 aIndex);
   virtual std::vector<IPartitionMeta::Ptr> CreatePartitionsMeta();
   
};

CServerFactory::CServerFactory()
{}

IPartitionMeta::Ptr CServerFactory::CreatePartitionMeta(UINT8 aIndex)
{
   IPartitionMeta::Ptr lPartMeta;
   return lPartMeta;
}

std::vector<IPartitionMeta::Ptr> CServerFactory::CreatePartitionsMeta()
{
   return std::vector<IPartitionMeta::Ptr>();
}

//----------------------------------------------------------------------------
IObjectFactory::Ptr CreateServerFactory()
{
	return IObjectFactory::Ptr(new CServerFactory());
}