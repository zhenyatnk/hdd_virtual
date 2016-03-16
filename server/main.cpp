#include <iostream>
#include "winsock.h"
#include "./transport/CService.h"

int main(int argc, char* argv[])
{
	ISocketInitializer::Ptr lInit = CreateWinSocketInitializer();
	TConectionParms lParm;
	lParm.mFamily = AF_INET;
	lParm.mIP = "127.0.0.1";
	lParm.mPort = NUMBER_PORT;
	CService lServer(lParm);
	lServer.Run();
	return 0;
}

