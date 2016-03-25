#pragma once

#include "../../tools/transport/CCObjectFactory.h"

using namespace System;

namespace bridge_csharp
{
   public ref class CREFServerException
      :public System::Exception
   {
   public:
      CREFServerException(System::String^ aMessage);
      System::String^ GetMessage();

   private:
      System::String^ mMessage;
   };

   public ref class CREFSocketException
      :public System::Exception
   {
   public:
      CREFSocketException(System::String^ aMessage);
      System::String^ GetMessage();

   private:
      System::String^ mMessage;
   };

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
      CREFPartitionMeta(bool aIsBoot, bool aIsExtend, UInt16 aType, UInt32 aSize);

      bool IsBoot();
      bool IsExtend();
      UInt16 GetTypePart();
      UInt32 GetSizeInSector();

   private:
      bool mIsExtend;
      bool mIsBoot;
      UInt16 mType;
      UInt32 mSize;
   };

   public ref class REFConvertTypeSystem
   {
   public:
      static System::String^ Convert(UInt16 aType);
   };

   public ref class CREFFactoryObject
   {
   public:
      CREFFactoryObject(CREFConectionParms^ aParms, System::String ^aFileNameVM);
      ~CREFFactoryObject();

      System::Collections::ArrayList^ CreatePartitionsMeta();

      void CloseChannel();

   private:
      IObjectFactory* GetFactory();

   private:
      IObjectFactory* mObjectFactory;
      CREFConectionParms^ mParms;
      System::String ^mFileNameVM;
   };

   public ref class CREFConfigFile
   {
   public:
      System::String^ GetDefaultIP();
      System::String^ GetDefaultFileNameVM();
      Int32 GetDefaultPort();

      void SetDefaultIP(System::String^ aIP);
      void SetDefaultFileNameVM(System::String^ aFileNameVM);
      void SetDefaultPort(Int32 aPort);
   };
}
