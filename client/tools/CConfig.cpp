#include <fstream>
#include "Windows.h"
#include "..\..\common\tools\ISocket.h"
#include "CConfig.h"

//-------------------------------------------------------------------------------
class CConfigKeywords
{
public:
   static std::string config_ip();
   static std::string config_port();
   static std::string config_separator();
};

std::string CConfigKeywords::config_ip()
{
   return "IP";
}

std::string CConfigKeywords::config_port()
{
   return "PORT";
}

std::string CConfigKeywords::config_separator()
{
   return " ";
}
//-------------------------------------------------------------------------------
std::string GetModulePath()
{
   CHAR lModuleFileName_chr[MAX_PATH];
   GetModuleFileNameA(NULL, lModuleFileName_chr, MAX_PATH);
   std::string lModuleFileName_str(lModuleFileName_chr);
   std::string::size_type offset_name = lModuleFileName_str.find_last_of('\\');
   if (offset_name != std::wstring::npos)
      return lModuleFileName_str.substr(0, offset_name);
   else
      return ".";
}
//-------------------------------------------------------------------------------
CConfigForms& CConfigForms::GetInstance()
{
   static CConfigForms lConfig;
   return lConfig;
}

CConfigForms::CConfigForms()
:mDefaultPort(0)
{
   LoadConfig();
}

CConfigForms::~CConfigForms()
{
   SaveConfig();
}

std::string CConfigForms::GetDefaultIP()
{
   return mDefaultIP;
}

UINT32 CConfigForms::GetDefaultPort()
{
   return mDefaultPort;
}

void CConfigForms::SetDefaultIP(std::string aDefaultIP)
{
   mDefaultIP = aDefaultIP;
}
void CConfigForms::SetDefaultPort(UINT32 aDefaultPort)
{
   mDefaultPort = aDefaultPort;
}

void CConfigForms::ParseLine(std::string aLine)
{
   size_t lPos = aLine.find(CConfigKeywords::config_separator());
   if (lPos != std::string::npos)
   {
      std::string lKey = aLine.substr(0, lPos);
      std::string lValue = aLine.substr(lPos + 1, aLine.size() - lPos);
      if (CConfigKeywords::config_ip() == lKey)         this->SetDefaultIP(lValue);
      else if (CConfigKeywords::config_port() == lKey)  this->SetDefaultPort(std::stol(lValue));
   }
}

void CConfigForms::LoadConfig()
{
   LoadToDefaultValue();
   std::ifstream lStream;
   lStream.open(GetModulePath() + "\\" + mFileNameConfig);
   std::string lLine;
   if (lStream.is_open())
      while (getline(lStream, lLine))
         ParseLine(lLine);
}
void CConfigForms::LoadToDefaultValue()
{
   mDefaultIP = "127.0.0.1";
   mDefaultPort = NUMBER_PORT;
}

void CConfigForms::SaveConfig()
{
   std::ofstream lStream(GetModulePath() + "\\" + mFileNameConfig);
   if (lStream.is_open())
   {
      lStream << CConfigKeywords::config_ip() << CConfigKeywords::config_separator() << this->GetDefaultIP() << std::endl;
      lStream << CConfigKeywords::config_port() << CConfigKeywords::config_separator() << std::to_string(this->GetDefaultPort()) << std::endl;
      lStream.close();
   }
}
//-------------------------------------------------------------------------------
