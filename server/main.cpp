#include <iostream>
#include "winsock.h"
#include ".\transport\CService.h"

int main(int argc, char* argv[])
{
   std::locale current_locale("");
   std::locale::global(current_locale);
   ISocketInitializer::Ptr lInit = CreateWinSocketInitializer();
   
   TConectionParms lParm;
   lParm.mFamily = AF_INET;
   lParm.mPort = NUMBER_PORT;

   try
   {
      CService lServer(lParm);
      lServer.Run();
   }
   catch (socket_exception_w &err)
   {
      std::wcout << err.get_message();
   }
   return 0;
}

