#include <iostream>
#include "winsock.h"
#include ".\transport\CCObjectFactory.h"

int main(int argc, char* argv[])
{
	ISocketInitializer::Ptr lInit = CreateWinSocketInitializer();

	TConectionParms lParm;
	lParm.mPort = NUMBER_PORT;
	lParm.mIP = "127.0.0.1";
	lParm.mFamily = AF_INET;
	IObjectFactory::Ptr lOper = CreateClientFactory(lParm);
	lOper->CreatePartitionMeta(1);
	lOper->CreatePartitionMeta(2);

	ISocket::Ptr lSocket = CreateWinSocket(lParm);
	lSocket->Connect();
	lSocket->Send("TEST1\n");
	lSocket->Send("TEST2\n");
	lSocket->Send("CLOSE");
	return 0;
}

