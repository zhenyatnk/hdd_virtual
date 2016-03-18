#include "stdafx.h"

#include <string>
#include <sstream>
#include <msclr/marshal_cppstd.h>
#include "bridge_csharp.h"

namespace bridge_csharp
{
	namespace Converters
	{
		TConectionParms ConvertTo(CREFConectionParms^ aParm)
		{
			TConectionParms lParm;
			lParm.mFamily = aParm->mFamily;
/*			lParm.mHostName = msclr::interop::marshal_as<std::string>((aParm->mHostName);
			lParm.mIP = msclr::interop::marshal_as<std::string>(aParm->mIP);
*/			lParm.mPort = aParm->mPort;
			return lParm;
		}
		CREFPartitionMeta^ ConvertTo(CPartitionMeta::Ptr aObj)
		{
			return gcnew CREFPartitionMeta(aObj->IsBoot(), aObj->GetTypePart(), aObj->GetSizeInSector());
		}
	}
	//-------------------------------------------------------------------------------
	CREFConectionParms::CREFConectionParms()
		:mHostName(""), mIP(""), mPort(0), mFamily(0)
	{}
	//-------------------------------------------------------------------------------
	CREFPartitionMeta::CREFPartitionMeta(bool aIsBoot, UInt16 aType, UInt32 aSize)
		: mIsBoot(aIsBoot), mType(aType), mSize(aSize)
	{}

	bool CREFPartitionMeta::IsBoot()
	{
		return mIsBoot;
	}

	UInt16 CREFPartitionMeta::GetTypePart()
	{
		return mType;
	}

	UInt32 CREFPartitionMeta::GetSizeInSector()
	{
		return mSize;
	}
	//-------------------------------------------------------------------------------

	CREFFactoryObject::CREFFactoryObject(CREFConectionParms^ aParms)
	{
		mObjectFactory = CreateClientFactoryNptr(Converters::ConvertTo(aParms));
	}
	CREFPartitionMeta^ CREFFactoryObject::CreatePartitionMeta(UInt16 aIndex)
	{
		return Converters::ConvertTo(mObjectFactory->CreatePartitionMeta(aIndex));
	}
};