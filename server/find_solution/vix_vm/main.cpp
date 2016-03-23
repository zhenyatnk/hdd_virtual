#include <windows.h>
#include "vix_objects.h"

int main(int argc, char* argv[])
{
   std::string lNameVM = "E:\\tmp\\vm\\Windows 8 x64.vmx";
   bool lVMRun = false;
   CVixHost lHost;
   std::vector<std::string> lNamesRunMaches = lHost.GetNamesVMachines();
   for (std::vector<std::string>::iterator lIterator = lNamesRunMaches.begin(); lIterator != lNamesRunMaches.end() && !lVMRun; ++lIterator)
      if (!_stricmp(lIterator->c_str(), lNameVM.c_str()))
         lVMRun = true;

   CVixVirtualMachine::Ptr lVM = lHost.GetVM(lNameVM.c_str());
   if (lVMRun)
      lVM->AddSnapshot("VM_SNAP_INFO", "");
   if(lVMRun)
      lVM->RemoveSnapshot("VM_SNAP_INFO");
   return 0;
}