#include "CCObjectFactory.h"
#include "./../../../common/tools/ISocket.h"
#include "./../../../common/tools/CExceptions.h"
#include "./../../../common/tools/TBuffer.h"
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
      while (this->GetSocket()->Receive(lBuffer.GetData(), lBuffer.GetSize()) && 
             lBuffer.ToString() != CFormatDataTransport::command_error() && 
             lBuffer.ToString() != CFormatDataTransport::command_close() )
      {
         if (lBuffer.ToString().substr(0, CFormatDataTransport::command_error().size()) == CFormatDataTransport::command_error())
            throw server_exception(lBuffer.ToString());

         std::vector<typename TObject::Ptr> lPartObjects = ConverterFromStr::ConvertToList<TObject>(lBuffer.ToString());
         for (std::vector<CPartitionMeta::Ptr>::iterator lIterator = lPartObjects.begin(); lIterator != lPartObjects.end(); ++lIterator)
            lContainerObjects.push_back(*lIterator);
         this->GetSocket()->Send(CFormatDataTransport::command_wait());
         lBuffer.Clear();
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

