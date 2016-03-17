#include "winsock.h"
#include <string>

#include "CExceptions.h"

std::wstring GetMessageWithSocketError(std::wstring aError)
{
   return aError + L" Код ошибки: " + std::to_wstring(WSAGetLastError());
}