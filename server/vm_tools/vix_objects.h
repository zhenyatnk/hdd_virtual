#ifndef _VIX_OBJECTS_H_
#define _VIX_OBJECTS_H_

#include <memory>
#include <string>
#include <vector>
#include "../../common/tools/DSmartPtr.h"
#include "../External/VMWare/h/vix.h"
//------------------------------------------------------------------------------
class CVix_Snapshot
{
public:
   typedef SmartPtr<CVix_Snapshot>::Ptr Ptr;
   friend class CVix_VirtualMachine;

private:
   CVix_Snapshot(VixHandle aHandleVM, VixHandle aHandleShapshot);
   CVix_Snapshot(const CVix_Snapshot&);
   CVix_Snapshot& operator = (const CVix_Snapshot&);

public:
   ~CVix_Snapshot();

   std::string GetNameSnapshot();

private:
   VixHandle GetHandle();

private:
   VixHandle mHandleShapshot;
   VixHandle mHandleVM;
};
//------------------------------------------------------------------------------
class CVix_VirtualMachine
{
public:
   typedef SmartPtr<CVix_VirtualMachine>::Ptr Ptr;
   friend class CVix_Host;

private:
   explicit CVix_VirtualMachine(VixHandle aHandle);
   CVix_VirtualMachine(const CVix_VirtualMachine&);
   CVix_VirtualMachine& operator = (const CVix_VirtualMachine&);

public:
   ~CVix_VirtualMachine();

   bool IsPowerOn();
   void Pause();
   void UnPause();
   int GetNumSnapshots();
   void AddSnapshot(std::string aNameSnapshot, std::string aDescription);
   void RemoveSnapshot(std::string aNameSnapshot);
   CVix_Snapshot::Ptr GetSnapshot(int aIndex);
   CVix_Snapshot::Ptr GetSnapshot(std::string aNameSnapshot);

private:
   VixHandle mHandleVM;
};
//------------------------------------------------------------------------------
class CVix_Host
{
public:
   CVix_Host();

private:
   CVix_Host(const CVix_Host&);
   CVix_Host& operator = (const CVix_Host&);

public:
   ~CVix_Host();

   CVix_VirtualMachine::Ptr GetVM(std::string aFileNameVM);

private:
   VixHandle mHadleHost;
};
//------------------------------------------------------------------------------
#endif