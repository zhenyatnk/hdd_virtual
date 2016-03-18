#ifndef _CONFIG_FILE_H_
#define _CONFIG_FILE_H_

#include <string>
#include "..\..\common\tools\TypeDef.h"

class CConfigForms
{
private:
   CConfigForms();

public:
   static CConfigForms& GetInstance();

   ~CConfigForms();

   std::string GetDefaultIP();
   UINT32 GetDefaultPort();

   void SetDefaultIP(std::string);
   void SetDefaultPort(UINT32);

private:
   void ParseLine(std::string aLine);

   void LoadConfig();
   void LoadToDefaultValue();
   void SaveConfig();

private:
   std::string mFileNameConfig = "config.ini";

   std::string mDefaultIP;
   UINT32 mDefaultPort;
};

#endif