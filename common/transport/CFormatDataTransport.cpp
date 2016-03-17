#include "CFormatDataTransport.h"

std::string ConverterToStr::Convert(CPartitionMeta::Ptr aObject)
{
   std::string lStr(CPartitionMeta::GetNameObject());
   lStr += ConverterToStr::Separator;
   lStr += std::string("SizeInSector: "); lStr += ConverterToStr::Convert(aObject->GetSizeInSector());
   lStr += ConverterToStr::Separator;
   lStr += std::string("TypePart: ");  lStr += ConverterToStr::Convert(aObject->GetTypePart());
   lStr += ConverterToStr::Separator;
   lStr += std::string("Boot: "); lStr += ConverterToStr::Convert(aObject->IsBoot());
   return lStr;
}

std::string ConverterToStr::Convert(bool aValue)
{
   std::string lStr;
   if (aValue)   lStr += "true";
   else          lStr += "false";
   return lStr;
}
std::string ConverterToStr::Convert(UINT32 aValue)
{
   return std::to_string(aValue);
}
std::string ConverterToStr::Convert(UINT8 aValue)
{
   return std::to_string(aValue);
}