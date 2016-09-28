
#include "MyServer.h"
#include "iostream"
#include "IoControler.h"
#include "Camera.h"
#include "ProcessThread.h"
#include "Dbase.h"
#include "tchar.h"
#include "AnsicUnicode.h"
#include "Machine.h"

#include "FlyCapture2.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace FlyCapture2;


#define	TOTAL_MACHINE				10
#define LINEMODULES_PER_MACHINE		2
#define	CAMERAS_PER_LINEARMODULE	2


HANDLE *g_pEventHandle = new HANDLE[TOTAL_MACHINE * LINEMODULES_PER_MACHINE];	//事件句柄，用于直线模组上相机的同步
BOOL *g_work = new BOOL[TOTAL_MACHINE * LINEMODULES_PER_MACHINE];				//模组工作标志位

unsigned int  WINAPI threadProc(PVOID pParam);	//线程函数

//*********************** 安装钩子函数，用于获取键盘消息 ***********************//
HHOOK g_kb_hook;
LRESULT CALLBACK kb_proc (int code, WPARAM wParam, LPARAM lParam)
{
	//printf((w==WM_KEYDOWN)?"按下%c\n":"抬起%c\n",((PKBDLLHOOKSTRUCT)lParam)->vkCode);
	if(wParam == WM_KEYUP)		
	{
		TCHAR c = ((PKBDLLHOOKSTRUCT)lParam)->vkCode;
		PostThreadMessage(GetCurrentThreadId(),WM_CHAR,NULL,(LPARAM)c);
	}
	return CallNextHookEx (g_kb_hook, code, wParam, lParam);
}

void _tmain(int argc, _TCHAR* argv[])
{
	//BusManager busM;

	///*bool pOk;
	//
	//unsigned int pSize;
	//FlyCapture2::CameraSelectionDlg dlg;
	//dlg.ShowModal(&pOk,&pGuid,&pSize);*/

	//FlyCapture2::PGRGuid pGuid;
	//unsigned int pNumCameras = 0;
	//busM.GetNumOfCameras (&pNumCameras);

	//busM.GetCameraFromIndex(0,&pGuid);


	//FlyCapture2::Camera cam;

	//
	//FlyCapture2::Error err = cam.Connect(&pGuid);

	//CString str;
	////str.Format(_T("%s"),err.GetDescription())

	//cam.StartCapture();

	//FlyCapture2::Image m_rawImage, m_processedImage;

	//cv::namedWindow("image",1);
	//for(;;)
	//{
	//	cam.RetrieveBuffer(&m_rawImage);

	//	unsigned int rows,cols,stride;
	//	PixelFormat format;
	//	m_rawImage.GetDimensions( &rows, &cols, &stride, &format );

	//	m_rawImage.Convert( PIXEL_FORMAT_RGB8, &m_processedImage );

	//	cv::Mat img(rows,cols,CV_8UC3,m_processedImage.GetData());
	//	cv::imshow("image",img);
	//	//cv::imwrite("image.jpg",img);
	//	cv::waitKey(30);
	//}
	g_kb_hook = SetWindowsHookEx (WH_KEYBOARD_LL,kb_proc,GetModuleHandle(NULL),0);

	if (g_kb_hook == NULL )
	{
		printf("安装钩子出错\n");
		return ;
	};
	//if (argc < 2)	return;
	//if(_tcscmp(argv[1], _T("huayuTest")) != 0)	return;

	//*********************** 参数定义 ***********************//
	int mechaineID[TOTAL_MACHINE] = {0};
	bool bOKmechine[TOTAL_MACHINE] = {false};


	//*********************** 初始化系统 ***********************//
	//						  相机连接确认						//

	{
		BusManager busManager;
		unsigned int numOfCameras;
		FlyCapture2::Error e;
		e = busManager.GetNumOfCameras(&numOfCameras);
		if (e != PGRERROR_OK)	return;

		if ( numOfCameras < TOTAL_MACHINE * LINEMODULES_PER_MACHINE * CAMERAS_PER_LINEARMODULE)
		{
			CString errorInfo(_T("系统检测到某些机台相机缺失，是否按现有设备启动其他正常机台？"));
			int nResponse = ::MessageBox(NULL,errorInfo,_T("提醒"),MB_OKCANCEL|MB_ICONQUESTION);

			if (nResponse == IDCANCEL)
			{
				return;
			}
		}

		// 建立可启动机台数组

	}




	//						  IO模块连接确认						//
	/*
	 //add code here
	*/
	
	//*********************** 建立通信服务 ***********************//

	CMyServer server;
	CMyServer *pServer = &server;

	// 开启服务
	if(pServer->Start())
	{
		printf(" 服务器开启成功... \n");
	}
	else
	{
		printf(" 服务器开启失败！\n");
		return;
	}

	//*********************** 创建工作者线程 ***********************//

	int totalThread = TOTAL_MACHINE * LINEMODULES_PER_MACHINE * CAMERAS_PER_LINEARMODULE ;
	int totalLinearModule = TOTAL_MACHINE * LINEMODULES_PER_MACHINE;

	HANDLE *pThreadHandle = new HANDLE[totalThread];		//工作者线程句柄
	
	for(int i = 0; i < TOTAL_MACHINE; ++i)
	{
		for(int j = 0; j < )
		pThreadHandle[i] = (HANDLE)_beginthreadex(NULL,0,threadProc,NULL,CREATE_SUSPENDED,NULL);
	}

	//*********************** 消息循环 ***********************//
	BOOL bQuit = FALSE;
	MSG msg;
	while(!bQuit && ::GetMessage(&msg,NULL,0,0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
		switch (msg.message)
		{
			case WM_CHAR :			//键盘消息
				{
					wprintf(_T("%c\n"),(TCHAR)msg.lParam);
					TCHAR c = (TCHAR)msg.lParam;

					switch(c)
					{
					case 'Q':
						bQuit = TRUE;
						break;
					default:
						break;
					}	
					
				}
			break;
		default:
			break;
		}

	}
	

	

	//						  程序退出						//
	/*
	 //add code here
	*/

	// 释放钩子
	UnhookWindowsHookEx(g_kb_hook);


	//关闭服务器
	pServer->Shutdown();
	pServer = NULL;
	printf(" 服务器关闭 \n ");


	// 释放线程句柄及事件句柄
	for (int i = 0; i < totalThread; ++i)
	{
		CloseHandle(pThreadHandle[i]);
	}
	for (int i = 0; i < totalLinearModule; ++i)
	{
		CloseHandle(pEventHandle[i]);
	}

}