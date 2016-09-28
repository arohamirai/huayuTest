#pragma once

#include "global.h"
#include "Camera.h"
#include "IoControler.h"
#include "process.h"
#include "iostream"
#include "windows.h"

class CProcessThread
{
public:
	CProcessThread(DWORD dwThreadid);
	~CProcessThread();

public:
	DWORD hExceptionThreadId;
private:
	CCamera m_camera;
	CIoControler m_ioControler;
	bool m_work;
public:
	int InitInstance();
	int createThread(PVOID Param, int initFlagm);
	DWORD  resumeThread();
	int run(void);

public:


public:
	unsigned int  m_ThreadId;
	HANDLE m_hThread;
	DWORD m_dwThreadid;


public:
	static unsigned  __stdcall ThreadstaticEntry(void * pThis)
	{
		CProcessThread * pProcessThread = (CProcessThread*)pThis;
		MSG m_msgCur;

		while (1)
		{
			Sleep(2000);
			PostThreadMessage(pProcessThread->m_dwThreadid,WM_CAMERA_LOSED,NULL,NULL);
			printf("thread\n");
		}
		{
			if (pProcessThread->m_work)   // 可以工作
			{
				///获取图像，处理图像等
			}
			else						//暂停工作
			{
				if (!::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))    //正常暂停
				{
					Sleep(1000);
				}
				else															//发来消息
				{
					if (!::GetMessage(&m_msgCur, NULL, NULL, NULL))				// WM_QUIT 消息
					{
						return 0;
					}
					else
					{
						::GetMessage(&m_msgCur, NULL, NULL, NULL);
						switch(m_msgCur.message)
						{
						case WM_CAMERA_LOSED:
							//相机丢失
							break;
						case WM_IOCARD_LOSED:
							// IO 板卡丢失
							break;
						}
					}
				}
			}


			if (pProcessThread->m_work && !::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))    //可以工作 且无消息
			{
				
			}
			else if (!pProcessThread->m_work && !::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE)) // 正常暂停
			{
				// do nothing
			}
			else

					return 0;
		}
		
		
		
	}
	
};

