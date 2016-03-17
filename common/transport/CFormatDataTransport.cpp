#include "CFormatDataTransport.h"

std::string ConverterToStr::Convert(CPartitionMeta::Ptr aObject)
{
   std::stringstream lStream;
   lStream << CPartitionMeta::GetNameObject() << ConverterToStr::Separator;
   lStream << "SizeInSector" << " " << aObject->GetSizeInSector() << ConverterToStr::Separator;
   lStream << "TypePart" << " " << (UINT32)aObject->GetTypePart() << ConverterToStr::Separator;
   lStream << "Boot" << " " << aObject->IsBoot();
   return lStream.str();
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