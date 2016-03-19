#include "stdafx.h"

#include <msclr\marshal_cppstd.h>
#include <string>
#include "bridge_csharp.h"

namespace bridge_csharp
{
	namespace Converters
	{
		TConectionParms ConvertTo(CREFConectionParms^ aParm)
		{
			System::String^ lStringHost = aParm->mHostName;
			System::String^ lStringIP = aParm->mIP;

			TConectionParms lParm;
			lParm.mFamily = aParm->mFamily;
			lParm.mHostName = msclr::interop::marshal_as<std::string>(lStringHost);
			lParm.mIP = msclr::interop::marshal_as<std::string>(lStringIP);
			lParm.mPort = aParm->mPort;
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
		:mParms(aParms), mObjectFactory(NULL)
	{}

	CREFFactoryObject::~CREFFactoryObject()
	{
		if (!!mObjectFactory)
			delete mObjectFactory;
	}

	CREFPartitionMeta^ CREFFactoryObject::CreatePartitionMeta(UInt16 aIndex)
	{
		return Converters::ConvertTo(GetFactory()->CreatePartitionMeta(aIndex));
	}

	void CREFFactoryObject::CloseChannel()
	{
		if (!!mObjectFactory)
		{
			delete mObjectFactory;
			mObjectFactory = NULL;
		}
	}

	IObjectFactory* CREFFactoryObject::GetFactory()
	{
		if (!mObjectFactory)
			mObjectFactory = CreateClientFactoryNptr(Converters::ConvertTo(mParms));
		return mObjectFactory;
	}
};