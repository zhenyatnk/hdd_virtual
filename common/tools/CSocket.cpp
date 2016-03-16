#include "windows.h"
#include "winsock.h"
#include "ISocket.h"

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
   if (aConParms.mHostName.empty())
      mAddr.sin_addr.s_addr = inet_addr(aConParms.mIP.c_str());
   else
   {
      hostent *lHost = gethostbyname(aConParms.mHostName.c_str());
      if (!lHost)
         throw("Нельзя распознать адрес");
      mAddr.sin_addr.s_addr = *(u_long *)(lHost->h_addr_list[0]);
   }
   mAddr.sin_port = htons(aConParms.mPort);
   mAddr.sin_family = aConParms.mFamily;
   return mAddr;
}
//---------------------------------------------
class CSocket
   :public ISocket
{
public:
   explicit CSocket(const SOCKET &aSocket);
   explicit CSocket(const TConectionParms &aConParms);
   virtual ~CSocket();
   
   virtual void Connect();
   virtual void Send(std::string aMessage);
   virtual bool Receive(char* aBuff, int aSize);

   virtual void Bind();
   virtual void Listen(int aMaxConnection);
   virtual ISocket::Ptr Accept();

private:
    SOCKET mSocket;
    SOCKADDR_IN mConParms;
};

CSocket::CSocket(const SOCKET &aSocket)
  :mSocket(aSocket)
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

void CSocket::Connect()
{
   connect(mSocket, (sockaddr *)&mConParms, sizeof(mConParms));
}

void CSocket::Send(std::string aMessage)
{
   send(mSocket, aMessage.c_str(), strlen(aMessage.c_str()), 0);
}

bool CSocket::Receive(char* aBuff, int aSize)
{
   int size_recieved;
   if ((size_recieved = recv(mSocket, aBuff, aSize, 0)))
      aBuff[size_recieved] = 0;
   return !!size_recieved;
}

void CSocket::Bind()
{
   bind(mSocket, (sockaddr *)&mConParms, sizeof(mConParms));
}

void CSocket::Listen(int aMaxConnection)
{
   listen(mSocket, aMaxConnection);
}

ISocket::Ptr CSocket::Accept()
{
   SOCKET lRetSocket = accept(mSocket, 0, 0);
   if (INVALID_SOCKET == lRetSocket)
      return ISocket::Ptr(NULL);
   else
      return ISocket::Ptr(new CSocket(lRetSocket));
}

ISocket::Ptr CreateWinSocket(const TConectionParms &aConParms)
{
   return ISocket::Ptr(new CSocket(aConParms));
}