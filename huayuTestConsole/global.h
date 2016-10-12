#pragma once

#include "windows.h"

#define WM_NET			WM_USER+104
#define WM_CAMERA_LOSED WM_USER+108
#define WM_IOCARD_LOSED WM_USER+112



typedef struct _tagHYSTARTINFO
{
	int MachineID;		//机台标识
	int moduleID;		//模组标识
	int index;			//线程索引标识

} HYSTARTINFO,*pHYSTARTINFO;




unsigned int  WINAPI mainThreadProc(PVOID pParam);	//机台主线程函数

unsigned int  WINAPI threadProc(PVOID pParam);	//机台次线程函数