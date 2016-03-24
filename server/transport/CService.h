#ifndef _C_SERVICE_H_
#define _C_SERVICE_H_

#include "./../../common/tools/ISocket.h"
#include "./../../common/tools/IThread.h"
#include "./../../common/tools/TBuffer.h"

//------------------------------------------------------------------------
class CClientStream
{
public:
   CClientStream(ISocket::Ptr aSocketClient);
   ~CClientStream();

   bool Send(std::string aBuff);

private:
   bool SendToWait(std::string aBuff);

private:
   ISocket::Ptr mSocketClient;
   std::string mCurrentChunc;
   bool mIsFirstSend;
   TBuffer<DEFAULT_BUFLEN> mBuffer;
};

//------------------------------------------------------------------------
class CChanelClient
   :public IThread
{
public:
   CChanelClient(ISocket::Ptr aSocketClient);

   virtual void Run();

private:
   ISocket::Ptr mSocketClient;
};

//------------------------------------------------------------------------
class CService
   :public IThread
{
public:
   CService(const TConectionParms &aParmServer);

   virtual void Run();

private:
   ISocket::Ptr GetSocket();

private:

   TConectionParms mParmServer;
   ISocket::Ptr mSocket;
};
//------------------------------------------------------------------------

#endif