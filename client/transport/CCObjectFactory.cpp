#include "CCObjectFactory.h"
#include "./../../common/tools/ISocket.h"

class CClientFactory
	:public IObjectFactory
{
public:
	CClientFactory(TConectionParms aParmConnection);
	~CClientFactory();
	virtual IPartitionMeta::Ptr CreatePartitionMeta(UINT8 aIndex);
	virtual std::vector<IPartitionMeta::Ptr> CreatePartitionsMeta();

private:
	ISocket::Ptr GetSocket();

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
		mClientSocket->Send("CLOSE");
}

IPartitionMeta::Ptr CClientFactory::CreatePartitionMeta(UINT8 aIndex)
{
	/*   this->GetSocket()->Send(std::string("GET ") + IPartitionMeta::GetNameObject());
	   char recvbuf[DEFAULT_BUFLEN];
	   int recvbuflen = DEFAULT_BUFLEN;
	   if(this->GetSocket()->Receive(recvbuf, recvbuflen))
	   lPartMeta = IPartitionMeta::LoadFromBuffer((UINT8*)recvbuf, recvbuflen);*/
	this->GetSocket()->Send(std::string("TEST SEND TO SERVER\n"));
	char recvbuf[DEFAULT_BUFLEN];
	memset(recvbuf, 0, DEFAULT_BUFLEN);
	int recvbuflen = DEFAULT_BUFLEN;
	if (this->GetSocket()->Receive(recvbuf, recvbuflen))
		printf(recvbuf);
	IPartitionMeta::Ptr lPartMeta;
	return lPartMeta;
}

std::vector<IPartitionMeta::Ptr> CClientFactory::CreatePartitionsMeta()
{
	return std::vector<IPartitionMeta::Ptr>();
}

ISocket::Ptr CClientFactory::GetSocket()
{
	if (!mClientSocket)
	{
		mClientSocket = CreateWinSocket(mParmConnection);
		mClientSocket->Connect();//TODO ошибка невозможно соединиться с сервером
	}
	return mClientSocket;
}

//----------------------------------------------------------------------------
IObjectFactory::Ptr CreateClientFactory(TConectionParms aParmConnection)
{
	return IObjectFactory::Ptr(new CClientFactory(aParmConnection));
}