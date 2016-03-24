#ifndef _TEMPLATE_BUFFER_H_
#define _TEMPLATE_BUFFER_H_

#include <string>
#include "DSmartPtr.h"
#include "TypeDef.h"

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
      mData = new V_UINT8[aBufferSize + 1];
      Clear();
   }

   ~TBuffer()
   {
      delete [] mData;
   }

   void Clear()
   {
      memset(mData, 0, aBufferSize + 1);
   }

   std::string ToString()
   {
      return std::string((char*)mData);
   }

   char* GetData()
   {
      return (char*)mData;
   }

   V_UINT32 GetSize()
   {
      return aBufferSize;
   }

private:
   V_UINT8 *mData;
};


#endif