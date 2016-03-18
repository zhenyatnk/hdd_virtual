#include "windows.h"
#include "winsock.h"
#include "ISocket.h"
#include "CExceptions.h"
#include "TypeDef.h"
#include <string>

const int WINSOCK_VERSION = 0x202;
//---------------------------------------------
class CSocketInitializer
   :public ISocketInitializer
{
public:
   CSocketInitializer();
   ~CSocketInitializer();

public:
     WSADATA wsaData;
};

CSocketInitializer::CSocketInitializer()
{
   if (WSAStartup(WINSOCK_VERSION, &wsaData)) 
	   WSACleanup();
}

CSocketInitializer::~CSocketInitializer()
{
   WSACleanup();
}

ISocketInitializer::Ptr CreateWinSocketInitializer()
{
   return ISocketInitializer::Ptr(new CSocketInitializer());
}

//---------------------------------------------
SOCKADDR_IN Convert(const TConectionParms &aConParms)
{
   SOCKADDR_IN mAddr;
   memset(&mAddr, 0, sizeof(mAddr));
   mAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   if (!aConParms.mIP.empty())
      mAddr.sin_addr.s_addr = inet_addr(aConParms.mIP.c_str());
   else if (!aConParms.mHostName.empty())
   {
      hostent *lHost = gethostbyname(aConParms.mHostName.c_str());
      if (!!lHost)
         throw socket_exception_w(L"Невозможно распознать адрес соединения");
      mAddr.sin_addr.s_addr = *(u_long *)(lHost->h_addr_list[0]);
   }
   mAddr.sin_port = htons(aConParms.mPort);
   mAddr.sin_family = aConParms.mFamily;
   return mAddr;
}
//---------------------------------------------
TConectionParms Convert(const SOCKADDR_IN &aConParms)
{
   TConectionParms lAddr;
   lAddr.mIP = inet_ntoa(aConParms.sin_addr);
   lAddr.mPort = ntohs(aConParms.sin_port);
   lAddr.mFamily = aConParms.sin_family;
   return lAddr;
}
//---------------------------------------------
class CSocket
   :public ISocket
{
public:
   explicit CSocket(const SOCKET &aSocket);
   CSocket(const SOCKET &aSocket, const SOCKADDR_IN& aAdrr);
   explicit CSocket(const TConectionParms &aConParms);
   virtual ~CSocket();
   
   virtual bool Connect();
   virtual void Send(std::string aMessage);
   virtual bool Receive(char* aBuff, int aSize);

   virtual bool Bind();
   virtual void Listen(int aMaxConnection);
   virtual ISocket::Ptr Accept();
   virtual TConectionParms GetParmsConnection();

private:
    SOCKET mSocket;
    SOCKADDR_IN mConParms;
};

CSocket::CSocket(const SOCKET &aSocket)
  :mSocket(aSocket)
{
   memset(&mConParms, 0, sizeof(mConParms));
}

CSocket::CSocket(const SOCKET &aSocket, const SOCKADDR_IN& aAdrr)
: mSocket(aSocket), mConParms(aAdrr)
{
}

CSocket::CSocket(const TConectionParms &aConParms)
   :mConParms(Convert(aConParms))
{
   mSocket = socket(AF_INET, SOCK_STREAM, 0);
}

CSocket::~CSocket()
{
   closesocket(mSocket);
}

bool CSocket::Connect()
{
   return !connect(mSocket, (sockaddr *)&mConParms, sizeof(mConParms));
}

void CSocket::Send(std::string aMessage)
{
   send(mSocket, aMessage.c_str(), (int)strlen(aMessage.c_str()), 0);
}

bool CSocket::Receive(char* aBuff, int aSize)
{
   int size_recieved;
   if ((size_recieved = recv(mSocket, aBuff, aSize, 0)))
      aBuff[size_recieved] = 0;
   return !!size_recieved;
}

bool CSocket::Bind()
{
   return !bind(mSocket, (sockaddr *)&mConParms, sizeof(mConParms));
}

void CSocket::Listen(int aMaxConnection)
{
   listen(mSocket, aMaxConnection);
}

ISocket::Ptr CSocket::Accept()
{
   SOCKADDR_IN accept_socket_addr;
   int addrLen = sizeof(SOCKADDR_IN);
   SOCKET lRetSocket = accept(mSocket, (SOCKADDR*)&accept_socket_addr, &addrLen);
   if (INVALID_SOCKET == lRetSocket)
      return ISocket::Ptr(NULL);
   else
      return ISocket::Ptr(new CSocket(lRetSocket, accept_socket_addr));
}

TConectionParms CSocket::GetParmsConnection()
{
   return Convert(mConParms);
}

ISocket::Ptr CreateWinSocket(const TConectionParms &aConParms)
{
   return ISocket::Ptr(new CSocket(aConParms));
}