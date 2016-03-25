#ifndef _C_FILE_NAME_UTILS_H_
#define _C_FILE_NAME_UTILS_H_

#include <string>

//----------------------------------------
class CFileName
{
public:
   CFileName(std::string Path, std::string FileName);
   CFileName(std::string FullFileName);
   CFileName(const CFileName& rght);
   std::string GetFileName() const;
   std::string GetFileNameWithoutExtension() const;
   std::string GetExtension() const;
   std::string GetPath() const;
   std::string GetFullFileName() const;

   bool operator!() const;

private:
   std::string mPathToFile;
   std::string mFileNameWithoutExtension;
   std::string mExtension;
};
#endif
