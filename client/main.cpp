#include <iostream>
#include "winsock.h"
#include ".\transport\CCObjectFactory.h"
#include "./../common/tools/CExceptions.h"

int main(int argc, char* argv[])
{
   std::locale current_locale("");
   std::locale::global(current_locale);

   ISocketInitializer::Ptr lInit = CreateWinSocketInitializer();
   TConectionParms lParm;
   lParm.mPort = NUMBER_PORT;
   lParm.mIP = "127.0.0.1";
   lParm.mFamily = AF_INET;
   try
   {
      IObjectFactory::Ptr lFactory = CreateClientFactory(lParm);
      lFactory->CreatePartitionMeta(1);
   }
   catch (socket_exception_w &err)
   {
      std::wcout << err.get_message();
   }
   return 0;
}

