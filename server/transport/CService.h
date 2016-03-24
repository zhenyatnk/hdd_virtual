#ifndef _C_SERVICE_H_
#define _C_SERVICE_H_

#include "./../../common/tools/ISocket.h"
#include "./../../common/transport/CPartitionMeta.h"
#include "./../../common/tools/IThread.h"
#include "./../../common/tools/TBuffer.h"
#include "./../../common/tools/CExceptions.h"
#include "./../../common/transport/CFormatDataTransport.h"
#include "./hdd_info/hdd_info_tools.h"
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
            CPartitionMeta::Ptr lMeta(new CPartitionMeta(false, 12, 151110));
            mSocketClient->Send(CFormatDataTransport::command_value_object<ConverterToStr>(lMeta));
         }
         else if (lString_buffer == CFormatDataTransport::command_get_object_list<CPartitionMeta>())
         {
            try
            {
               std::vector<CPartitionMeta::Ptr> lContainerObjects = GetContainerPartitionMeta("E:\\tmp\\vm\\Windows 8 x64.vmx", "E:\\tmp\\vm\\Windows 8 x64.vmdk");
               TBuffer<DEFAULT_BUFLEN> lBufferChannel;
               std::string lBufferRec = "";
               bool isFirst = true;
               for (std::vector<CPartitionMeta::Ptr>::iterator lIterator = lContainerObjects.begin(); lIterator != lContainerObjects.end(); ++lIterator)
               {
                  std::string lStringObj = CFormatDataTransport::command_value_object<ConverterToStr>(*lIterator);
                  if ((lBufferRec.size() + lStringObj.size()) >= DEFAULT_BUFLEN)
                  {
                     if (!isFirst && !(mSocketClient->Receive(lBufferChannel.GetData(), lBufferChannel.GetSize()) &&
                        lBufferChannel.ToString() == CFormatDataTransport::command_wait()))
                        break;
                     mSocketClient->Send(lBufferRec);
                     if (isFirst) isFirst = false;
                     lBufferRec = "";
                  }
                  if (!lBufferRec.empty())
                     lBufferRec += ConverterToStr::Separator;
                  lBufferRec += lStringObj;
               }
               if (!lBufferRec.empty())
               {
                  if (!isFirst && !(mSocketClient->Receive(lBufferChannel.GetData(), lBufferChannel.GetSize()) &&
                     lBufferChannel.ToString() == CFormatDataTransport::command_wait()))
                     break;
                  mSocketClient->Send(lBufferRec);
                  lBufferRec = "";
               }
               mSocketClient->Send(CFormatDataTransport::command_close());
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