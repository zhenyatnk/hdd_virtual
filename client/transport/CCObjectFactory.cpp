#include "CCObjectFactory.h"
#include "./../../common/tools/ISocket.h"
#include "./../../common/tools/CExceptions.h"
#include "./../../common/transport/CFormatDataTransport.h"

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
   typename TObject::Ptr GetObjectPtr()
   {
      TBuffer<DEFAULT_BUFLEN> lBuffer;
      TObject::Ptr lObject;
      this->GetSocket()->Send(CFormatDataTransport::command_get_object<TObject>());
      if (this->GetSocket()->Receive(lBuffer.GetData(), lBuffer.GetSize()))
      {
         printf("%s\n", lBuffer.GetData());
         if (lBuffer.ToString() != CFormatDataTransport::command_error())
         {
            ;
         }
      }
      return lObject;
   }

private:
	ISocket::Ptr mClientSocket;
	TConectionParms mParmConnection;
};

CClientFactory::CClientFactory(TConectionParms aParmConnection)
:mParmConnection(aParmConnection)
{}

CClientFactory::~CClientFactory()
{
	if (!!mClientSocket)
		mClientSocket->Send(CFormatDataTransport::command_close());
}

CPartitionMeta::Ptr CClientFactory::CreatePartitionMeta(UINT8 aIndex)
{
   return this->GetObjectPtr<CPartitionMeta>();
}

std::vector<CPartitionMeta::Ptr> CClientFactory::CreatePartitionsMeta()
{
	return std::vector<CPartitionMeta::Ptr>();
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