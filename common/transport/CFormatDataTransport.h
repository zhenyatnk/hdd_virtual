#ifndef _CLASS_FORMAT_TRANSPORT_H_
#define _CLASS_FORMAT_TRANSPORT_H_

#include <string>
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