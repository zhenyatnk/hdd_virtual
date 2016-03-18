#pragma once

#include "../tools/transport/CCObjectFactory.h"

using namespace System;

namespace bridge_csharp
{
	public ref class CREFConectionParms
	{
	public:
		CREFConectionParms();

		System::String^ mHostName;
		System::String^ mIP;
		Int32 mPort;
		UInt16 mFamily;
	};

	public ref class CREFPartitionMeta
	{
	public:
		CREFPartitionMeta(bool aIsBoot, UInt16 aType, UInt32 aSize);

		bool IsBoot();
		UInt16 GetTypePart();
		UInt32 GetSizeInSector();

	private:
		bool mIsBoot;
		UInt16 mType;
		UInt32 mSize;
	};

	public ref class CREFFactoryObject
	{
	public:
		CREFFactoryObject(CREFConectionParms^ aParms);
		CREFPartitionMeta^ CreatePartitionMeta(UInt16 aIndex);
	private:
		IObjectFactory* mObjectFactory;
	};
}
