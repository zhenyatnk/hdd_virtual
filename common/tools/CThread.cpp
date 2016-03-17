#include "windows.h"
#include <process.h>
#include "IThread.h"

//-------------------------------------------------------------------------
class CWinRunnerThread
   :public IRunnerThread
{
public:
   CWinRunnerThread();

   virtual bool Start(IThread* aObj);
   virtual bool Wait();
   virtual void Close();

private:
    static unsigned int _stdcall func_runner(void* aParm);

private:
   HANDLE mHandleThread;
};

unsigned int _stdcall CWinRunnerThread::func_runner(void* aParm)
{
   IThread::thread_func(aParm);
   return 0;
}

//-------------------------------------------------------------------------
CWinRunnerThread::CWinRunnerThread()
:mHandleThread(NULL)
{}

bool CWinRunnerThread::Start(IThread* aObj)
{
   mHandleThread = (HANDLE)_beginthreadex(NULL, 0, (CWinRunnerThread::func_runner), (void*)aObj, 0, NULL);
   return mHandleThread != 0;
}

bool CWinRunnerThread::Wait()
{
   if (!!mHandleThread)
      return WaitForSingleObject(mHandleThread, INFINITE) == WAIT_OBJECT_0;
   else
      return false;
}

void CWinRunnerThread::Close()
{
   if (!!mHandleThread)
      CloseHandle(mHandleThread);
}
//-------------------------------------------------------------------------
IRunnerThread::Ptr IRunnerThread::Create()
{
   return IRunnerThread::Ptr(new CWinRunnerThread());
}