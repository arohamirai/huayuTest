#include "ProcessThread.h"


CProcessThread::CProcessThread()
{

}


CProcessThread::~CProcessThread(void)
{
}


int CProcessThread::InitInstance()
{
	//******************** 数据库连接 *********************//

	m_db.connectDB();
	//iocard连接

	//预置点信息生成

	//相机参数设置

	return TRUE;
}


int CProcessThread::run(void)
{
	for (;;)
	{
		if (m_work)
		{
			/// move camera
			//
			/////////////////////
		}
	}

	return 0;
}


int CProcessThread::createThread(PVOID Param, unsigned int initFlag)
{
	CProcessThread *pProcessThread = (CProcessThread*)Param;
	pProcessThread->m_hThread = (HANDLE)_beginthreadex(NULL,0,CProcessThread::ThreadstaticEntry,Param,CREATE_SUSPENDED,&pProcessThread->m_ThreadId);
	return 0;
}

DWORD CProcessThread::resumeThread()
{
	return ResumeThread(this->m_hThread);
}

