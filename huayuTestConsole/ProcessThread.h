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
			if (pProcessThread->m_work)   // ���Թ���
			{
				///��ȡͼ�񣬴���ͼ���
			}
			else						//��ͣ����
			{
				if (!::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))    //������ͣ
				{
					Sleep(1000);
				}
				else															//������Ϣ
				{
					if (!::GetMessage(&m_msgCur, NULL, NULL, NULL))				// WM_QUIT ��Ϣ
					{
						return 0;
					}
					else
					{
						::GetMessage(&m_msgCur, NULL, NULL, NULL);
						switch(m_msgCur.message)
						{
						case WM_CAMERA_LOSED:
							//�����ʧ
							break;
						case WM_IOCARD_LOSED:
							// IO �忨��ʧ
							break;
						}
					}
				}
			}


			if (pProcessThread->m_work && !::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))    //���Թ��� ������Ϣ
			{
				
			}
			else if (!pProcessThread->m_work && !::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE)) // ������ͣ
			{
				// do nothing
			}
			else

					return 0;
		}
		
		
		
	}
	
};

