#include "iostream"
#include "MyServer.h"
#include "IoControler.h"
#include "Camera.h"
#include "ProcessThread.h"
#include "Dbase.h"
#include "tchar.h"
#include "AnsicUnicode.h"
#include "Machine.h"
#include "BusManager.h"

#include "FlyCapture2.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace FlyCapture2;


//#define	TOTAL_MACHINE				10

HANDLE *g_pEventHandle ;	//事件句柄，用于直线模组上相机的同步
BOOL *g_work;				//模组工作标志位

bool isCameraExist(unsigned int serialNumber, FlyCapture2::CameraInfo *pCamInfo,unsigned int arraySize);

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
	g_kb_hook = SetWindowsHookEx (WH_KEYBOARD_LL,kb_proc,GetModuleHandle(NULL),0);
	if (g_kb_hook == NULL )
	{
		printf("安装钩子出错\n");
		return ;
	};
	//if (argc < 2)	return;
	//if(_tcscmp(argv[1], _T("huayuTest")) != 0)	return;

	//*********************** 参数定义 ***********************//
	

	//*********************** 初始化系统 ***********************//
	//						  相机连接确认						//

	//						   常用变量							//
	
	int totalMachine = 0;
	unsigned int totalCam;
	std::vector<int> vecOKMachineID, vecNotOKMachineID;
	CDbase db;
	
	CString strSQL;

	db.connectDB();

	//获取机台总数
	{
		_RecordsetPtr pRecordset;
		strSQL = _T("select count(*) as totalMachine from machineInfoTable");
		pRecordset = db.readBySet(strSQL);
		if ( pRecordset->GetRecordCount() == -1)
			return;
		totalMachine = (int)pRecordset->GetCollect((_variant_t)(_T("totalMachine")));
		g_pEventHandle = new HANDLE[totalMachine * LINEMODULES_PER_MACHINE];
		g_work = new BOOL[totalMachine * LINEMODULES_PER_MACHINE];

		pRecordset->Close();
		pRecordset = NULL;
		
		//获取相机总数
		CBusManager bus;
		int e;
		e = bus.GetNumOfCameras(&totalCam);
		if (e != BUS_0K)	return;
	}

	//检测机台是否工作正常
	if ( totalCam < totalMachine  * LINEMODULES_PER_MACHINE * CAMERAS_PER_LINEARMODULE)
	{
		//某些机台出故障，检测出故障机台
		int *pMachaineID = NULL;
		bool *pbOKmachine = NULL;
		FlyCapture2::CameraInfo CamInfo ;
		unsigned int arrySize;
		pbOKmachine = new bool[totalMachine];
			
		//获取所有连接相机的信息
		CBusManager::DiscoverAllCameras(&CamInfo,&arrySize);

		//先获取所有机台编号
		_RecordsetPtr pRecordsetMachine;
		strSQL = _T("select machineID from machineInfoTable");
		pRecordsetMachine = db.readBySet(strSQL);
		//遍历机台
		if (!pRecordsetMachine->adoEOF)
		{
			int index = 0;
			pRecordsetMachine->MoveFirst();

			while(!pRecordsetMachine->adoEOF)
			{
				_RecordsetPtr pRecordsetCam;

				// 初始为true
				pbOKmachine[index] = true;

				//根据机台编号查找对应相机
				pMachaineID[index] = (int)pRecordsetMachine->GetCollect(_T("machineID"));
				strSQL.Format(_T("select cameraID from machineInfoTable where machineID =  %d"),pMachaineID[index]);
				pRecordsetCam = db.readBySet(strSQL);
				if (!pRecordsetCam->adoEOF)
				{
					pRecordsetCam->MoveFirst();
					while(!pRecordsetCam->adoEOF)
					{
						unsigned int serialNumber;
						bool exist;
							
						serialNumber= (unsigned int)pRecordsetCam->GetCollect(_T("cameraID"));
						exist = isCameraExist(serialNumber,&CamInfo,arrySize);
						pbOKmachine[index] = pbOKmachine[index] & exist;

						pRecordsetCam->MoveNext();
					}

					pRecordsetCam->Close();
					pRecordsetCam = NULL;
				}
				index++;
				pRecordsetMachine->MoveNext();
			}
		}


		pRecordsetMachine->Close();
		pRecordsetMachine = NULL;

		// 建立可启动机台编号数组，并输出相关信息
		for (int i = 0; i < totalMachine; ++i)
		{
			if (pbOKmachine[i] == true)
			{
				vecOKMachineID.push_back(pMachaineID[i]);
			}
			else
			{
				vecNotOKMachineID.push_back(pMachaineID[i]);
			}
			delete []pMachaineID;
			delete []pbOKmachine;

			CString strNotOK = _T("");
			for (std::vector<int>::iterator it = vecNotOKMachineID.begin(); it != vecNotOKMachineID.end(); it++)
			{
				CString strTemp;
				strTemp.Format(_T("%d,"),*it);
				strNotOK =strNotOK + strTemp;
			}
			strNotOK = _T("编号为：") + strNotOK + _T("的机台某些相机不能正常工作，是否启动其他正常机台？");
			INT_PTR nResponse = ::MessageBox(NULL,strNotOK,_T("请注意"),MB_OKCANCEL|MB_ICONQUESTION);
			if (nResponse == IDCANCEL)
				return;
		}
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

	int totalThread = vecOKMachineID.size();
	int totalLinearModule = 1;
	HANDLE *pThreadHandle = new HANDLE[totalThread];		//工作者线程句柄
	
	for(int i = 0; i < totalThread; ++i)
	{
		pThreadHandle[i] = (HANDLE)_beginthreadex(NULL,0,threadProc,&vecOKMachineID[i],CREATE_SUSPENDED,NULL);
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
		CloseHandle(g_pEventHandle[i]);
	}

	//释放内存


}


bool isCameraExist(unsigned int serialNumber, FlyCapture2::CameraInfo *pCamInfo,unsigned int arraySize)
{
	for (int i = 0; i < arraySize; ++i)
	{
		if (serialNumber == pCamInfo[i].serialNumber) return true;
	}

	return false;
}