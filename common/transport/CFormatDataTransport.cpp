#include "CFormatDataTransport.h"

std::string ConverterToStr::Convert(CPartitionMeta::Ptr aObject)
{
   std::stringstream lStream;
   lStream << CPartitionMeta::GetNameObject() << ConverterToStr::Separator;
   lStream << "SizeInSector" << " " << std::to_string(aObject->GetSizeInSector()) << ConverterToStr::Separator;
   lStream << "TypePart" << " " << std::to_string(aObject->GetTypePart()) << ConverterToStr::Separator;
   lStream << "Boot" << " " << aObject->IsBoot();
   return lStream.str();
}

std::string ConverterToStr::Convert(std::vector<CPartitionMeta::Ptr> aContainerObjects)
{
   std::stringstream lStream;
   for (std::vector<CPartitionMeta::Ptr>::iterator lIterator = aContainerObjects.begin(); lIterator != aContainerObjects.end(); ++lIterator)
   {
      if (lIterator != aContainerObjects.begin())
         lStream << ConverterToStr::Separator;
      lStream << ConverterToStr::Convert((*lIterator));
   }
   return lStream.str();
}