#ifndef _VDDK_VM_TOOLS_H_
#define _VDDK_VM_TOOLS_H_

#include <windows.h>
#include <memory>
#include <string>
#include <vector>

#include "../../common/tools/TBuffer.h"
#include "../../common/tools/DSmartPtr.h"
#include "../External/VMWare/h/vixDiskLib.h"

//------------------------------------------------------------------------------
class CVix_VirtualDisk
{
public:
   typedef  SmartPtr<CVix_VirtualDisk>::Ptr Ptr;
   friend class CVix_DiskLibrary;

private:
   CVix_VirtualDisk(VixDiskLibConnection aConnectionParms, const char *aPathVirtualDisk, uint32 aFlagsOpen);
   CVix_VirtualDisk(const CVix_VirtualDisk&);
   
   CVix_VirtualDisk& operator = (const CVix_VirtualDisk&);

public:
   ~CVix_VirtualDisk();

   TBuffer<VIXDISKLIB_SECTOR_SIZE>::Ptr ReadSector(uint32 aNumberSector);

private:
   VixDiskLibHandle mHandleVirtualDisk;
};
//------------------------------------------------------------------------------
class CVix_DiskLibrary
{
public:
   CVix_DiskLibrary();
   ~CVix_DiskLibrary();

   bool Connect(std::string aSnapshotName="");
   bool Connect(VixDiskLibConnectParams aParms, std::string aSnapshotName="");

   CVix_VirtualDisk::Ptr GetVirtualDisk(std::string aDiskPath);

private:
   void Disconnect();

private:
   VixDiskLibConnection mConnection;
};
//------------------------------------------------------------------------------
#endif