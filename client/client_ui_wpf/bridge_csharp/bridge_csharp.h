#pragma once

#include "../../tools/transport/CCObjectFactory.h"

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
		~CREFFactoryObject();

		CREFPartitionMeta^ CreatePartitionMeta(UInt16 aIndex);

		void CloseChannel();

	private:
		IObjectFactory* GetFactory();

	private:
		IObjectFactory* mObjectFactory;
		CREFConectionParms^ mParms;
	};

	public ref class CREFConfigFile
	{
	public:
		System::String^ GetDefaultIP();
		Int32 GetDefaultPort();

		void SetDefaultIP(System::String^ aIP);
		void SetDefaultPort(Int32 aPort);
	};
}
