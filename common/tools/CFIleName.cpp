#include "CFIleName.h"
//-----------------------------------------------------------------------------
std::string GetExtension(std::string FileName)
{
   std::string lExtension = "";
   size_t lLastDot = FileName.find_last_of(".");
   if (lLastDot != std::string::npos)
      lExtension = FileName.substr(lLastDot + 1);
   return lExtension;
}
//-----------------------------------------------------------------------------
std::string GetFileNameWithoutExtension(std::string FileName)
{
   std::string lFileNameWitoutExtension = "";
   size_t lLastDot = FileName.find_last_of(".");
   if (lLastDot != std::string::npos)
      lFileNameWitoutExtension = FileName.substr(0, lLastDot);
   else
      lFileNameWitoutExtension = FileName;
   return lFileNameWitoutExtension;
}
//-----------------------------------------------------------------------------
CFileName::CFileName(std::string PathToFile, std::string FileName)
:mPathToFile(PathToFile), mFileNameWithoutExtension(::GetFileNameWithoutExtension(FileName)), mExtension(::GetExtension(FileName))
{
}

CFileName::CFileName(std::string FullFileName)
{
   std::string::size_type offset_name = FullFileName.find_last_of("\\");
   if (offset_name != std::string::npos)
   {
      mPathToFile = FullFileName.substr(0, offset_name);
      mFileNameWithoutExtension = ::GetFileNameWithoutExtension(FullFileName.substr(offset_name + 1));
      mExtension = ::GetExtension(FullFileName.substr(offset_name + 1));
   }
   else
   {
      mFileNameWithoutExtension = ::GetFileNameWithoutExtension(FullFileName);
      mExtension = ::GetExtension(FullFileName);
   }
}

CFileName::CFileName(const CFileName& rght)
:mPathToFile(rght.GetPath()), mFileNameWithoutExtension(rght.GetFileNameWithoutExtension()), mExtension(rght.GetExtension())
{
}

std::string CFileName::GetFileName() const
{
   if (GetExtension().empty())
      return GetFileNameWithoutExtension();
   else
      return GetFileNameWithoutExtension() + "." + GetExtension();
}

std::string CFileName::GetFileNameWithoutExtension() const
{
   return mFileNameWithoutExtension;
}

std::string CFileName::GetExtension() const
{
   return mExtension;
}

std::string CFileName::GetPath() const
{
   return mPathToFile;
}

std::string CFileName::GetFullFileName() const
{
   return GetPath() + "\\" + GetFileName();
}

bool CFileName::operator!() const
{
   return GetFileName() == "";
}

//-----------------------------------------------------------------------------