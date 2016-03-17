#ifndef _I_SOCKET_H_
#define _I_SOCKET_H_

#include <string>
#include "DSmartPtr.h"

#define DEFAULT_BUFLEN 512
#define NUMBER_PORT 25000
//---------------------------------------------
class ISocketInitializer
{
public:
   typedef SmartPtr<ISocketInitializer>::Ptr Ptr;

public:
   virtual ~ISocketInitializer()
   {}
};

//---------------------------------------------
struct TConectionParms
{
public:
   TConectionParms()
      :mHostName(""), mIP(""), mPort(0), mFamily(0)
   {}
   std::string mHostName;
   std::string mIP;
   int mPort;
   unsigned int mFamily;
};
//---------------------------------------------
class ISocket
{
public:
   typedef SmartPtr<ISocket>::Ptr Ptr;

public:
   virtual ~ISocket()
   {}

   virtual bool Connect() = 0;
   virtual void Send(std::string aMessage) = 0;
   virtual bool Receive(char* aBuff, int aSize) = 0;

   virtual bool Bind() = 0;
   virtual void Listen(int aMaxConnection) = 0;
   virtual ISocket::Ptr Accept() = 0;
   virtual TConectionParms GetParmsConnection() = 0;
};

ISocket::Ptr CreateWinSocket(const TConectionParms &aConParms);
ISocketInitializer::Ptr CreateWinSocketInitializer();

#endif