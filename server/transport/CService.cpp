#include "CService.h"
#include "../hdd_info/hdd_info_tools.h"
#include "./../../common/transport/CPartitionMeta.h"
#include "./../../common/tools/CExceptions.h"
#include "./../../common/transport/CFormatDataTransport.h"
#include "./../../server/transport/CSObjectFactory.h"

//------------------------------------------------------------------------
CClientStream::CClientStream(ISocket::Ptr aSocketClient)
:mSocketClient(aSocketClient), mIsFirstSend(true)
{ }

CClientStream::~CClientStream()
{
   if (!mCurrentChunc.empty())
      this->SendToWait(mCurrentChunc);
   this->SendToWait(CFormatDataTransport::command_close());
}

bool CClientStream::Send(std::string aBuff)
{
   if ((mCurrentChunc.size() + aBuff.size()) >= DEFAULT_BUFLEN)
   {
      if (!this->SendToWait(mCurrentChunc))
         return false;
      mCurrentChunc = "";
      if (mIsFirstSend) mIsFirstSend = false;
   }
   if (!mCurrentChunc.empty())
      mCurrentChunc += ConverterToStr::Separator;
   mCurrentChunc += aBuff;
   return true;
}
bool CClientStream::SendToWait(std::string aBuff)
{
   mBuffer.Clear();
   if (!mIsFirstSend)
   if (!mSocketClient->Receive(mBuffer.GetData(), mBuffer.GetSize()) ||
      mBuffer.ToString() != CFormatDataTransport::command_wait())
      return false;
   mSocketClient->Send(aBuff);
   return true;
}
//------------------------------------------------------------------------
CChanelClient::CChanelClient(ISocket::Ptr aSocketClient)
:mSocketClient(aSocketClient)
{}

void CChanelClient::Run()
{
   printf("IP(%s:%d):\tConnect\n", mSocketClient->GetParmsConnection().mIP.c_str(), mSocketClient->GetParmsConnection().mPort);
   TBuffer<DEFAULT_BUFLEN> lBuffer;
   while (mSocketClient->Receive(lBuffer.GetData(), lBuffer.GetSize()))
   {
      printf("IP(%s:%d):\tECHO %s\n", mSocketClient->GetParmsConnection().mIP.c_str(), mSocketClient->GetParmsConnection().mPort, lBuffer.GetData());
      std::string lString_buffer = lBuffer.ToString();
      if (lString_buffer == CFormatDataTransport::command_close())
         break;
      else if (lString_buffer == CFormatDataTransport::command_get_object_list<CPartitionMeta>())
      {
         try
         {
            // HOME IObjectFactory::Ptr lFactoryObject = CreateServerFactory("E:\\VM_ Machine\\Windows 10\\Windows 10 x64.vmx", "E:\\VM_ Machine\\Windows 10\\Windows 10 x64.vmdk");
            IObjectFactory::Ptr lFactoryObject = CreateServerFactory("E:\\tmp\\vm\\Windows 8 x64.vmx", "E:\\tmp\\vm\\Windows 8 x64.vmdk");
            std::vector<CPartitionMeta::Ptr> lContainerObjects = lFactoryObject->CreatePartitionsMeta();

            CClientStream lStream(mSocketClient);
            for (std::vector<CPartitionMeta::Ptr>::iterator lIterator = lContainerObjects.begin(); lIterator != lContainerObjects.end(); ++lIterator)
            if (!lStream.Send(CFormatDataTransport::command_value_object<ConverterToStr>(*lIterator)))
               break;
         }
         catch (vm_exception &e)
         {
            mSocketClient->Send(CFormatDataTransport::command_error(e.get_message()));
         }
      }
      else
         mSocketClient->Send(CFormatDataTransport::command_undefined());
      lBuffer.Clear();
   }
   printf("IP(%s:%d):\tDisconnect\n", mSocketClient->GetParmsConnection().mIP.c_str(), mSocketClient->GetParmsConnection().mPort);
}

//------------------------------------------------------------------------
CService::CService(const TConectionParms &aParmServer)
:mParmServer(aParmServer)
{ }

void CService::Run()
{
   try
   {
      this->GetSocket()->Listen(0);
      ISocket::Ptr lClientSocket;
      while (!!(lClientSocket = this->GetSocket()->Accept()))
         (new CChanelClient(lClientSocket))->start();
   }
   catch (socket_exception_w &e)
   {
      wprintf(e.get_message().c_str());
   }
}

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