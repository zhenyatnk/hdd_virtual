#include "CCObjectFactory.h"
#include "./../../../common/tools/ISocket.h"
#include "./../../../common/tools/CExceptions.h"
#include "./../../../common/transport/CFormatDataTransport.h"

class CClientFactory
   :public IObjectFactory
{
public:
   CClientFactory(TConectionParms aParmConnection);
   ~CClientFactory();
   virtual CPartitionMeta::Ptr CreatePartitionMeta(UINT8 aIndex);
   virtual std::vector<CPartitionMeta::Ptr> CreatePartitionsMeta();

private:
   ISocket::Ptr GetSocket();

   template <class TObject>
   typename TObject::Ptr GetObject()
   {
      TBuffer<DEFAULT_BUFLEN> lBuffer;
      TObject::Ptr lObject;
      this->GetSocket()->Send(CFormatDataTransport::command_get_object<TObject>());
      if (this->GetSocket()->Receive(lBuffer.GetData(), lBuffer.GetSize()))
      {
         printf("%s\n", lBuffer.GetData());
         if (lBuffer.ToString() != CFormatDataTransport::command_error())
            lObject = ConverterFromStr::Convert<TObject>(lBuffer.ToString());
      }
      return lObject;
   }
   template <class TObject>
   std::vector<typename TObject::Ptr> GetContainerObjects()
   {
      TBuffer<DEFAULT_BUFLEN> lBuffer;
      std::vector<typename TObject::Ptr> lContainerObjects;
      this->GetSocket()->Send(CFormatDataTransport::command_get_object_list<TObject>());
      if (this->GetSocket()->Receive(lBuffer.GetData(), lBuffer.GetSize()))
      {
         printf("%s\n", lBuffer.GetData());
         if (lBuffer.ToString() != CFormatDataTransport::command_error())
            lContainerObjects = ConverterFromStr::ConvertToList<TObject>(lBuffer.ToString());
      }
      return lContainerObjects;
   }


private:
   ISocket::Ptr mClientSocket;
   TConectionParms mParmConnection;
   ISocketInitializer::Ptr mInitSocket;
};

CClientFactory::CClientFactory(TConectionParms aParmConnection)
:mParmConnection(aParmConnection), mInitSocket(CreateWinSocketInitializer())
{}

CClientFactory::~CClientFactory()
{
   if (!!mClientSocket)
      mClientSocket->Send(CFormatDataTransport::command_close());
}

CPartitionMeta::Ptr CClientFactory::CreatePartitionMeta(UINT8 aIndex)
{
   return this->GetObject<CPartitionMeta>();
}

std::vector<CPartitionMeta::Ptr> CClientFactory::CreatePartitionsMeta()
{
   return this->GetContainerObjects<CPartitionMeta>();
}

ISocket::Ptr CClientFactory::GetSocket()
{
   if (!mClientSocket)
   {
      mClientSocket = CreateWinSocket(mParmConnection);
      if (!mClientSocket->Connect())
         throw socket_exception_w(GetMessageWithSocketError(L"Сервер не отвечает."));
   }
   return mClientSocket;
}

//----------------------------------------------------------------------------
IObjectFactory::Ptr CreateClientFactory(TConectionParms aParmConnection)
{
   return IObjectFactory::Ptr(new CClientFactory(aParmConnection));
}
IObjectFactory* CreateClientFactoryNptr(TConectionParms aParmConnection)
{
   return new CClientFactory(aParmConnection);
}

