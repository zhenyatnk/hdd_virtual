#ifndef _C_SERVER_OBJECT_FACTORY_H_
#define _C_SERVER_OBJECT_FACTORY_H_

#include "./../../common/transport/IObjectFactory.h"

IObjectFactory::Ptr CreateServerFactory(std::string aFileNameVM, std::string aFileVirtualDisk);

#endif