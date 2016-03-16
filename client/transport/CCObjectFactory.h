#ifndef _C_CLIENT_OBJECT_FACTORY_H_
#define _C_CLIENT_OBJECT_FACTORY_H_

#include "./../../common/transport/IObjectFactory.h"
#include "./../../common/tools/ISocket.h"

IObjectFactory::Ptr CreateClientFactory(TConectionParms aParmConnection);

#endif