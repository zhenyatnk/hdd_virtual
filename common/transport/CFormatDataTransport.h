#ifndef _CLASS_FORMAT_TRANSPORT_H_
#define _CLASS_FORMAT_TRANSPORT_H_

#include <string>
#include <vector>
#include <sstream> 
#include "CPartitionMeta.h"

class CFormatDataTransport
{
public:
   static const char Separator = '\n';

public:
   static std::string command_close()
   {
      return "CLOSE";
   }
   static std::string command_get()
   {
      return "GET";
   }

   static std::string command_error()
   {
      return CFormatDataTransport::command_error("");
   }

   static std::string command_error(std::string aError)
   {
      return "ERROR: " + aError;
   }

   static std::string command_wait()
   {
      return "WAIT";
   }

   static std::string command_undefined()
   {
      return "UNDEFINED COMMAND";
   }

   static std::string command_file_name_vm()
   {
      return CFormatDataTransport::command_file_name_vm("");
   }

   static std::string command_file_name_vm(std::string aFileNameVM)
   {
      return "FILENAME_VM: " + aFileNameVM;
   }

   template <class Type>
   static std::string command_get_object()
   {
      return CFormatDataTransport::command_get() + " " + Type::GetNameObject();
   }

   template <class Type>
   static std::string command_get_object_list()
   {
      return CFormatDataTransport::command_get() + " LIST " + Type::GetNameObject();
   }

   template <class TConverterData, class Type>
   static std::string command_value_object(Type aObject)
   {
      return TConverterData::Convert(aObject);
   }
};
//-------------------------------------------------------------
class ConverterToStr
{
public:
   static const char Separator = '\n';

public:
   static std::string Convert(CPartitionMeta::Ptr aObject);
   static std::string Convert(std::vector<CPartitionMeta::Ptr> aContainerObjects);
};
//-------------------------------------------------------------
class ConverterFromStr
{
public:
   static const char Separator = '\n';

public:
   template<class TObject>
   static typename TObject::Ptr Convert(std::string aStr)
   {
      "Для метода требуется определить специализацию";
   }

   template<class TObject>
   static std::vector<typename TObject::Ptr> ConvertToList(std::string aStr)
   {
      "Для метода требуется определить специализацию";
   }

   template<>
   static CPartitionMeta::Ptr Convert<CPartitionMeta>(std::string aStr)
   {
      CPartitionMeta::Ptr lObject;
      std::stringstream lStream;
      lStream.str(aStr);
      std::string lName;
      lStream >> lName;
      if (lName == CPartitionMeta::GetNameObject())
      {
         V_UINT32 lSizeInSector;
         V_UINT32 lTypePart;
         bool lBoot;
         bool lExtend;
         lStream >> lName; lStream >> lSizeInSector;
         lStream >> lName; lStream >> lTypePart;
         lStream >> lName; lStream >> lBoot;
         lStream >> lName; lStream >> lExtend;
         lObject = CPartitionMeta::Ptr(new CPartitionMeta(lBoot, lExtend, (V_UINT8)lTypePart, lSizeInSector));
      }
      return lObject;
   }

   template<>
   static  std::vector<CPartitionMeta::Ptr> ConvertToList<CPartitionMeta>(std::string aStr)
   {
      std::vector<CPartitionMeta::Ptr> lContainerObjects;
      std::stringstream lStream;
      lStream.str(aStr);
      while (!lStream.eof())
      {
         std::string lName;
         lStream >> lName;
         if (lName == CPartitionMeta::GetNameObject())
         {
            V_UINT32 lSizeInSector;
            V_UINT32 lTypePart;
            bool lBoot;
            bool lExtend;
            lStream >> lName; lStream >> lSizeInSector;
            lStream >> lName; lStream >> lTypePart;
            lStream >> lName; lStream >> lBoot;
            lStream >> lName; lStream >> lExtend;
            lContainerObjects.push_back(CPartitionMeta::Ptr(new CPartitionMeta(lBoot, lExtend, (V_UINT8)lTypePart, lSizeInSector)));
         }
      }
      return lContainerObjects;
   }
};

#endif