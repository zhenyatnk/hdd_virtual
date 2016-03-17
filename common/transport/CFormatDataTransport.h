#ifndef _CLASS_FORMAT_TRANSPORT_H_
#define _CLASS_FORMAT_TRANSPORT_H_

#include <string>
#include <sstream> 
#include "CPartitionMeta.h"

class CFormatDataTransport
{
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
        return "ERROR";
     }

     static std::string command_undefined()
     {
        return "UNDEFINED COMMAND";
     }

     template <class Type>
     static std::string command_get_object()
     {
        return CFormatDataTransport::command_get() + " " + Type::GetNameObject();
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

   static std::string Convert(bool aValue);
   static std::string Convert(UINT32 aValue);
   static std::string Convert(UINT8 aValue);
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
         UINT32 lSizeInSector;
         UINT32 lTypePart;
         bool lBoot;
         lStream >> lName; lStream >> lSizeInSector;
         lStream >> lName; lStream >> lTypePart;
         lStream >> lName; lStream >> lBoot;
         lObject = CPartitionMeta::Ptr(new CPartitionMeta(lBoot, (UINT8)lTypePart, lSizeInSector));
      }
      return lObject;
   }
};
//-------------------------------------------------------------
template <int aBufferSize>
struct TBuffer
{
   TBuffer()
   {
      Clear();
   }

   void Clear()
   {
      memset(mData, 0, aBufferSize);
   }

   std::string ToString()
   {
      return std::string((char*)mData);
   }

   char* GetData()
   {
      return (char*)mData;
   }

   UINT32 GetSize()
   {
      return aBufferSize;
   }

private:
   UINT8 mData[aBufferSize];
};


#endif