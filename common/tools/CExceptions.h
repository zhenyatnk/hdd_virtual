#ifndef _I_EXCEPTIONS_H_
#define _I_EXCEPTIONS_H_

#include <stdexcept>
#include <string>

class socket_exception_w
   :public std::runtime_error
{
public:
   explicit socket_exception_w(const std::wstring& aWhat)
   :mError(aWhat), runtime_error("socket_exception_w")
   { 
      mError = aWhat;
   }
   std::wstring get_message() const
   {
      return mError;
   }
private:
   std::wstring mError;
};
std::wstring GetMessageWithSocketError(std::wstring aError);

class vm_exception
   :public std::runtime_error
{
public:
   explicit vm_exception(const std::string& aWhat)
   :mError(aWhat), runtime_error("vm_exception")
   { 
      mError = aWhat;
   }
   std::string get_message() const
   {
      return mError;
   }
private:
   std::string mError;
};

class server_exception
   :public std::runtime_error
{
public:
   explicit server_exception(const std::string& aWhat)
   :mError(aWhat), runtime_error("server_exception")
   { 
      mError = aWhat;
   }
   std::string get_message() const
   {
      return mError;
   }
private:
   std::string mError;
};



#endif