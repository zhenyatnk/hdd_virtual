#include <windows.h>
#include <iostream>
#include "vix_objects.h"
#include "../../../common/tools/CExceptions.h"

int main(int argc, char* argv[])
{
   std::locale current_locale("");
   std::locale::global(current_locale);

   std::string lNameVM = "E:\\tmp\\vm\\Windows 8 x64.vmx";
   //std::string lNameVM = "E:\\VirtualM\\Ubuntu 64-bit\\Ubuntu 64-bit (2).vmx";
   try{
	   CVixHost lHost;
	   CVixVirtualMachine::Ptr lVM = lHost.GetVM(lNameVM.c_str());
	   bool lVMRun = lVM->IsPowerOn();
	   if (lVMRun)
		   lVM->AddSnapshot("VM_SNAP_INFO", "");
	   if (lVMRun)
		   lVM->RemoveSnapshot("VM_SNAP_INFO");
   }
   catch (vm_exception_w &err)
   {
      std::wcout << err.get_message();
   }
   return 0;
}