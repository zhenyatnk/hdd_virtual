#ifndef _HDD_INFO_TOOLS_H_
#define _HDD_INFO_TOOLS_H_

#include <windows.h>
#include <vector>

#include "../../common/transport/CPartitionMeta.h"
#include "../vm_tools/vddk_vm_tools.h"
//------------------------------------------------------------------------------
std::vector<CPartitionMeta::Ptr> GetContainerPartitionMeta(CVix_VirtualDisk::Ptr lDisk);

//------------------------------------------------------------------------------
#endif