#include "stdafx.h"

#include <msclr\marshal_cppstd.h>
#include <string>
#include "bridge_csharp.h"
#include "../../tools/CConfig.h"
#include "../../../common/tools/CExceptions.h"

namespace bridge_csharp
{
   namespace Converters
   {
      CREFPartitionMeta^ ConvertTo(CPartitionMeta::Ptr aObj)
      {
         return gcnew CREFPartitionMeta(aObj->IsBoot(), aObj->IsExtend(), aObj->GetTypePart(), aObj->GetSizeInSector());
      }

      System::Collections::ArrayList^ ConvertTo(std::vector<CPartitionMeta::Ptr> aContainerObjs)
      {
         System::Collections::ArrayList^ lManagedContainerMeta = gcnew System::Collections::ArrayList;
         for (std::vector<CPartitionMeta::Ptr>::iterator lIterator = aContainerObjs.begin(); lIterator != aContainerObjs.end(); ++lIterator)
            lManagedContainerMeta->Add(Converters::ConvertTo(*lIterator));
         return lManagedContainerMeta;

      }

      System::String^ ConvertTo(std::string aStr)
      {
         return gcnew System::String(aStr.c_str());
      }

      std::string ConvertTo(System::String^ aStr)
      {
         return msclr::interop::marshal_as<std::string>(aStr);
      }

      TConectionParms ConvertTo(CREFConectionParms^ aParm)
      {
         System::String^ lStringHost = aParm->mHostName;
         System::String^ lStringIP = aParm->mIP;

         TConectionParms lParm;
         lParm.mFamily = aParm->mFamily;
         lParm.mHostName = ConvertTo(lStringHost);
         lParm.mIP = ConvertTo(lStringIP);
         lParm.mPort = aParm->mPort;
         return lParm;
      }
   }

   //-------------------------------------------------------------------------------
   CREFServerException::CREFServerException(System::String^ aMessage)
      :System::Exception("CREFServerException"), mMessage(aMessage)
   {}

   System::String^ CREFServerException::GetMessage()
   {
      return mMessage;
   }
   //-------------------------------------------------------------------------------
   CREFSocketException::CREFSocketException(System::String^ aMessage)
      :System::Exception("CREFSocketException"), mMessage(aMessage)
   {}

   System::String^ CREFSocketException::GetMessage()
   {
      return mMessage;
   }
   //-------------------------------------------------------------------------------
   CREFConectionParms::CREFConectionParms()
      :mHostName(""), mIP(""), mPort(0), mFamily(0)
   {}
   //-------------------------------------------------------------------------------
   CREFPartitionMeta::CREFPartitionMeta(bool aIsBoot, bool aIsExtend, UInt16 aType, UInt32 aSize)
      : mIsBoot(aIsBoot), mIsExtend(aIsExtend), mType(aType), mSize(aSize)
   {}

   bool CREFPartitionMeta::IsBoot()
   {
      return mIsBoot;
   }

   bool CREFPartitionMeta::IsExtend()
   {
      return mIsExtend;
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
   System::String^ REFConvertTypeSystem::Convert(UInt16 aType)
   {
      return gcnew System::String(ConvertTypeSystem(aType).c_str());
   }

   //-------------------------------------------------------------------------------

   CREFFactoryObject::CREFFactoryObject(CREFConectionParms^ aParms, System::String ^aFileNameVM)
      :mParms(aParms), mFileNameVM(aFileNameVM), mObjectFactory(NULL)
   {}

   CREFFactoryObject::~CREFFactoryObject()
   {
      if (!!mObjectFactory)
         delete mObjectFactory;
   }
   
   System::Collections::ArrayList^ CREFFactoryObject::CreatePartitionsMeta()
   {
      try
      {
         return Converters::ConvertTo(GetFactory()->CreatePartitionsMeta());
      }
      catch (server_exception &e)
      {
         throw gcnew CREFServerException(gcnew System::String(e.get_message().c_str()));
      }
      catch (socket_exception_w &e)
      {
         throw gcnew CREFSocketException(gcnew System::String(e.get_message().c_str()));
      }
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
         mObjectFactory = CreateClientFactoryNptr(Converters::ConvertTo(mParms), Converters::ConvertTo(mFileNameVM));
      return mObjectFactory;
   }

   System::String^ CREFConfigFile::GetDefaultIP()
   {
      return Converters::ConvertTo(CConfigForms::GetInstance().GetDefaultIP());
   }

   System::String^ CREFConfigFile::GetDefaultFileNameVM()
   {
      return Converters::ConvertTo(CConfigForms::GetInstance().GetDefaultFileNameVM());
   }

   Int32 CREFConfigFile::GetDefaultPort()
   {
      return CConfigForms::GetInstance().GetDefaultPort();
   }

   void CREFConfigFile::SetDefaultIP(System::String^ aIP)
   {
      CConfigForms::GetInstance().SetDefaultIP(Converters::ConvertTo(aIP));
   }

   void CREFConfigFile::SetDefaultFileNameVM(System::String^ aFileNameVM)
   {
      CConfigForms::GetInstance().SetDefaultFileNameVM(Converters::ConvertTo(aFileNameVM));
   }

   void CREFConfigFile::SetDefaultPort(Int32 aPort)
   {
      CConfigForms::GetInstance().SetDefaultPort(aPort);
   }
};