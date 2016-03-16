#ifndef _C_SERVICE_H_
#define _C_SERVICE_H_

#include "./../../common/tools/ISocket.h"
#include "./../../common/tools/IThread.h"
//------------------------------------------------------------------------
class CChanelClient
	:public IThread
{
public:
	CChanelClient(ISocket::Ptr aSocketClient)
		:mSocketClient(aSocketClient)
	{}

	virtual void Run()
	{
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;
		while (mSocketClient->Receive(recvbuf, recvbuflen))
		{
			printf(recvbuf);
			memset(recvbuf, 0, DEFAULT_BUFLEN);
			if (std::string(recvbuf) == "CLOSE")
				break;
			mSocketClient->Send(std::string("TEST SEND TO CLIENT\n"));
		}
	}
private:
	ISocket::Ptr mSocketClient;
};

//------------------------------------------------------------------------
class CService
	:public IThread
{
public:
	CService(const TConectionParms &aParmServer)
		:mParmServer(aParmServer)
	{ }

	virtual void Run()
	{
		this->GetSocket()->Listen(0);
		ISocket::Ptr lClientSocket;
		while (!!(lClientSocket = this->GetSocket()->Accept()))
			(new CChanelClient(lClientSocket))->start();
	}

private:
	ISocket::Ptr CService::GetSocket()
	{
		if (!mSocket)
		{
			mSocket = CreateWinSocket(mParmServer);
			mSocket->Bind();
		}
		return mSocket;
	}

private:

	TConectionParms mParmServer;
	ISocket::Ptr mSocket;
};
//------------------------------------------------------------------------

#endif