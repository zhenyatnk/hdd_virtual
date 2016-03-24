#ifndef _TEMPLATE_BUFFER_H_
#define _TEMPLATE_BUFFER_H_

#include <string>
#include "DSmartPtr.h"

//-------------------------------------------------------------
template <int aBufferSize>
class TBuffer
{
public:
   typedef typename SmartPtr<TBuffer>::Ptr Ptr;

private:
   TBuffer(const TBuffer&);
   TBuffer& operator = (const TBuffer&);

public:
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