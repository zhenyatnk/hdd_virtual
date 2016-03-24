#ifndef _HDD_INFO_TOOLS_H_
#define _HDD_INFO_TOOLS_H_

#include <windows.h>
#include <vector>

#include "../../common/transport/CPartitionMeta.h"
//------------------------------------------------------------------------------
std::vector<CPartitionMeta::Ptr> GetContainerPartitionMeta(char* aSector0);
//------------------------------------------------------------------------------
std::vector<CPartitionMeta::Ptr> GetContainerPartitionMeta(std::string aFileNameVM, std::string aFileVirtualDisk);
//------------------------------------------------------------------------------
#endif