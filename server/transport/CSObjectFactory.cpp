#include "CSObjectFactory.h"
#include "./../../common/tools/ISocket.h"

class CServerFactory
   :public IObjectFactory
{
   public:
   CServerFactory();

   virtual std::vector<CPartitionMeta::Ptr> CreatePartitionsMeta();
   
};

CServerFactory::CServerFactory()
{}

std::vector<CPartitionMeta::Ptr> CServerFactory::CreatePartitionsMeta()
{
   return std::vector<CPartitionMeta::Ptr>();
}

//----------------------------------------------------------------------------
IObjectFactory::Ptr CreateServerFactory()
{
	return IObjectFactory::Ptr(new CServerFactory());
}