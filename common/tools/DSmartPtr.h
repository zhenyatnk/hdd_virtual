#ifndef _DEF_SMART_PTR_H_
#define _DEF_SMART_PTR_H_

#include <memory>

#define NAME_CLASS(ItemName)\
static std::string GetNameObject()\
{\
   return #ItemName; \
}

template <typename Type>
class SmartPtr
{
public:
   typedef typename std::shared_ptr<Type> Ptr;
};

#endif