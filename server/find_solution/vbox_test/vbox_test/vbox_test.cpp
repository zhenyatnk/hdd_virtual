// vbox_test.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include "VirtualBox_h.h"

#define SAFE_RELEASE(x) \
if (x) {\
   x->Release(); \
   x = NULL; \
}

int listVMs(IVirtualBox *virtualBox)
{
   HRESULT rc;

   /*
   * First we have to get a list of all registered VMs
   */
   SAFEARRAY *machinesArray = NULL;

   rc = virtualBox->get_Machines(&machinesArray);
   if (SUCCEEDED(rc))
   {
      IMachine **machines;
      rc = SafeArrayAccessData(machinesArray, (void **)&machines);
      if (SUCCEEDED(rc))
      {
         for (ULONG i = 0; i < machinesArray->rgsabound[0].cElements; ++i)
         {
            BSTR str;
            rc = machines[i]->get_Name(&str);
            if (SUCCEEDED(rc))
            {
               printf("Name: %S\n", str);
               SysFreeString(str);
            }


            SAFEARRAY *storagesArray = NULL;
            machines[i]->get_StorageControllers(&storagesArray);
            IStorageController** lStorageControllers;
            rc = SafeArrayAccessData(storagesArray, (void **)&lStorageControllers);
         }

         SafeArrayUnaccessData(machinesArray);
      }

      SafeArrayDestroy(machinesArray);
   }

   return 0;
}




int testErrorInfo(IVirtualBox *virtualBox)
{
   HRESULT rc;

   /* Try to find a machine that doesn't exist */
   IMachine *machine = NULL;
   BSTR machineName = SysAllocString(L"Foobar");

   rc = virtualBox->FindMachine(machineName, &machine);

   if (FAILED(rc))
   {
      IErrorInfo *errorInfo;

      rc = GetErrorInfo(0, &errorInfo);

      if (FAILED(rc))
         printf("Error getting error info! rc = 0x%x\n", rc);
      else
      {
         BSTR errorDescription = NULL;

         rc = errorInfo->GetDescription(&errorDescription);

         if (FAILED(rc) || !errorDescription)
            printf("Error getting error description! rc = 0x%x\n", rc);
         else
         {
            printf("Successfully retrieved error description: %S\n", errorDescription);

            SysFreeString(errorDescription);
         }

         errorInfo->Release();
      }
   }

   SAFE_RELEASE(machine);
   SysFreeString(machineName);

   return 0;
}


int testStartVM(IVirtualBox *virtualBox)
{
   HRESULT rc;

   /* Try to start a VM called "WinXP SP2". */
   IMachine *machine = NULL;
   BSTR machineName = SysAllocString(L"WinXP SP2");

   rc = virtualBox->FindMachine(machineName, &machine);

   if (FAILED(rc))
   {
      IErrorInfo *errorInfo;

      rc = GetErrorInfo(0, &errorInfo);

      if (FAILED(rc))
         printf("Error getting error info! rc = 0x%x\n", rc);
      else
      {
         BSTR errorDescription = NULL;

         rc = errorInfo->GetDescription(&errorDescription);

         if (FAILED(rc) || !errorDescription)
            printf("Error getting error description! rc = 0x%x\n", rc);
         else
         {
            printf("Successfully retrieved error description: %S\n", errorDescription);

            SysFreeString(errorDescription);
         }

         SAFE_RELEASE(errorInfo);
      }
   }
   else
   {
      ISession *session = NULL;
      IConsole *console = NULL;
      IProgress *progress = NULL;
      BSTR sessiontype = SysAllocString(L"gui");
      BSTR guid;

      do
      {
         rc = machine->get_Id(&guid); /* Get the GUID of the machine. */
         if (!SUCCEEDED(rc))
         {
            printf("Error retrieving machine ID! rc = 0x%x\n", rc);
            break;
         }

         /* Create the session object. */
         rc = CoCreateInstance(CLSID_Session,        /* the VirtualBox base object */
            NULL,                 /* no aggregation */
            CLSCTX_INPROC_SERVER, /* the object lives in a server process on this machine */
            IID_ISession,         /* IID of the interface */
            (void**)&session);
         if (!SUCCEEDED(rc))
         {
            printf("Error creating Session instance! rc = 0x%x\n", rc);
            break;
         }

         /* Start a VM session using the delivered VBox GUI. */
         rc = machine->LaunchVMProcess(session, sessiontype,
            NULL, &progress);
         if (!SUCCEEDED(rc))
         {
            printf("Could not open remote session! rc = 0x%x\n", rc);
            break;
         }

         /* Wait until VM is running. */
         printf("Starting VM, please wait ...\n");
         rc = progress->WaitForCompletion(-1);

         /* Get console object. */
         session->get_Console(&console);

         /* Bring console window to front. */
         machine->ShowConsoleWindow(0);

         printf("Press enter to power off VM and close the session...\n");
         getchar();

         /* Power down the machine. */
         rc = console->PowerDown(&progress);

         /* Wait until VM is powered down. */
         printf("Powering off VM, please wait ...\n");
         rc = progress->WaitForCompletion(-1);

         /* Close the session. */
         rc = session->UnlockMachine();

      } while (0);

      SAFE_RELEASE(console);
      SAFE_RELEASE(progress);
      SAFE_RELEASE(session);
      SysFreeString(guid);
      SysFreeString(sessiontype);
      SAFE_RELEASE(machine);
   }

   SysFreeString(machineName);

   return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
   HRESULT rc;
   IVirtualBox *virtualBox;

   do
   {
      /* Initialize the COM subsystem. */
      CoInitialize(NULL);

      /* Instantiate the VirtualBox root object. */
      rc = CoCreateInstance(CLSID_VirtualBox,       /* the VirtualBox base object */
         NULL,                   /* no aggregation */
         CLSCTX_LOCAL_SERVER,    /* the object lives in a server process on this machine */
         IID_IVirtualBox,        /* IID of the interface */
         (void**)&virtualBox);

      if (!SUCCEEDED(rc))
      {
         printf("Error creating VirtualBox instance! rc = 0x%x\n", rc);
         break;
      }

      listVMs(virtualBox);

      testErrorInfo(virtualBox);

      /* Enable the following line to get a VM started. */
      //testStartVM(virtualBox);

      /* Release the VirtualBox object. */
      virtualBox->Release();

   } while (0);

   CoUninitialize();
   return 0;
}


