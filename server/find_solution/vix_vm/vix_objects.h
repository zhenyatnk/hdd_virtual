#ifndef _VIX_OBJECTS_H_
#define _VIX_OBJECTS_H_

#include <memory>
#include <string>
#include <vector>

#include "vix.h"
//------------------------------------------------------------------------------
class CVixSnapshot
{
public:
   typedef std::shared_ptr<CVixSnapshot> Ptr;
   friend class CVixVirtualMachine;

private:
   CVixSnapshot(VixHandle aHandleVM, VixHandle aHandleShapshot);

public:
   ~CVixSnapshot();

   std::string GetNameSnapshot();

private:
   VixHandle GetHandle();

private:
   VixHandle mHandleShapshot;
   VixHandle mHandleVM;
};
//------------------------------------------------------------------------------
class CVixVirtualMachine
{
public:
   typedef std::shared_ptr<CVixVirtualMachine> Ptr;
   friend class CVixHost;

private:
   CVixVirtualMachine(VixHandle aHandle);

public:
   ~CVixVirtualMachine();

   bool IsPowerOn();
   void Pause();
   void UnPause();
   int GetNumSnapshots();
   void AddSnapshot(std::string aNameSnapshot, std::string aDescription);
   void RemoveSnapshot(std::string aNameSnapshot);
   CVixSnapshot::Ptr GetSnapshot(int aIndex);
   CVixSnapshot::Ptr GetSnapshot(std::string aNameSnapshot);

private:
   VixHandle mHandleVM;
};
//------------------------------------------------------------------------------
class CVixHost
{
public:
   CVixHost();
   ~CVixHost();

   std::vector<std::string> GetNamesVMachines();
   CVixVirtualMachine::Ptr GetVM(std::string aFileNameVM);

private:
   VixHandle mHadleHost;
};
//------------------------------------------------------------------------------
#endif