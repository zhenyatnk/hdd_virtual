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
   CVixSnapshot(const CVixSnapshot&);
   CVixSnapshot& operator = (const CVixSnapshot&);

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
   explicit CVixVirtualMachine(VixHandle aHandle);
   CVixVirtualMachine(const CVixVirtualMachine&);
   CVixVirtualMachine& operator = (const CVixVirtualMachine&);

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

private:
   CVixHost(const CVixHost&);
   CVixHost& operator = (const CVixHost&);

public:
   ~CVixHost();

   CVixVirtualMachine::Ptr GetVM(std::string aFileNameVM);

private:
   VixHandle mHadleHost;
};
//------------------------------------------------------------------------------
#endif