#ifndef _C_SERVICE_H_
#define _C_SERVICE_H_

#include "./../../common/tools/ISocket.h"
#include "./../../common/transport/CPartitionMeta.h"
#include "./../../common/tools/IThread.h"
#include "./../../common/tools/CExceptions.h"
#include "./../../common/transport/CFormatDataTransport.h"
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
      printf("IP(%s:%d):\tConnect\n", mSocketClient->GetParmsConnection().mIP.c_str(), mSocketClient->GetParmsConnection().mPort);
      TBuffer<DEFAULT_BUFLEN> lBuffer;
      while (mSocketClient->Receive(lBuffer.GetData(), lBuffer.GetSize()))
		{
         printf("IP(%s:%d):\tECHO %s\n", mSocketClient->GetParmsConnection().mIP.c_str(), mSocketClient->GetParmsConnection().mPort, lBuffer.GetData());
         std::string lString_buffer = lBuffer.ToString();
         if (lString_buffer == CFormatDataTransport::command_close())
				break;
         else if (lString_buffer == CFormatDataTransport::command_get_object<CPartitionMeta>())
         {
            CPartitionMeta::Ptr lMeta(new CPartitionMeta(true, 1, 150));
            mSocketClient->Send(CFormatDataTransport::command_value_object<ConverterToStr>(lMeta));
         }
         else
            mSocketClient->Send(CFormatDataTransport::command_undefined());
         lBuffer.Clear();
      }
      printf("IP(%s:%d):\tDisconnect\n", mSocketClient->GetParmsConnection().mIP.c_str(), mSocketClient->GetParmsConnection().mPort);
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
         if (!mSocket->Bind())
            throw socket_exception_w(GetMessageWithSocketError(L"Адрес недоступен."));
		}
		return mSocket;
	}

private:

	TConectionParms mParmServer;
	ISocket::Ptr mSocket;
};
//------------------------------------------------------------------------

#endif