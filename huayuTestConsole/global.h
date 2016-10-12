#pragma once

#include "windows.h"

#define WM_NET			WM_USER+104
#define WM_CAMERA_LOSED WM_USER+108
#define WM_IOCARD_LOSED WM_USER+112



typedef struct _tagHYSTARTINFO
{
	int MachineID;		//��̨��ʶ
	int moduleID;		//ģ���ʶ
	int index;			//�߳�������ʶ

} HYSTARTINFO,*pHYSTARTINFO;




unsigned int  WINAPI mainThreadProc(PVOID pParam);	//��̨���̺߳���

unsigned int  WINAPI threadProc(PVOID pParam);	//��̨���̺߳���