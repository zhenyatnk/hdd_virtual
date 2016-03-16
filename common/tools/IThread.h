#ifndef _I_THREAD_H_
#define _I_THREAD_H_

#include "DSmartPtr.h"

class IThread;
//-------------------------------------------------
class IRunnerThread
{
public:
   typedef SmartPtr<IRunnerThread>::Ptr Ptr;

public:
   virtual bool Start(IThread* aObj) = 0;
   virtual bool Wait() = 0;
   virtual void Close() = 0;

public:
   static IRunnerThread::Ptr Create();
};

//-------------------------------------------------
class IThread
{
public:
   static void* thread_func (void *aObject) 
   {
      IThread* lExecuteObj = (IThread*)aObject;
      lExecuteObj->Run();
	  delete lExecuteObj;
      return NULL;
   }

public:
   IThread()
      :mThreadRunner(IRunnerThread::Create())
   {}

   explicit IThread(IRunnerThread::Ptr aRunner)
      :mThreadRunner(aRunner)
   {}

   virtual ~IThread()
   {
      mThreadRunner->Close();
   }

   bool start ()
   {
      return mThreadRunner->Start(this);
   }
   bool wait()
   {
      return mThreadRunner->Wait();
   }

public:
   virtual void Run() = 0;

private:
   IRunnerThread::Ptr mThreadRunner;
}; 

#endif