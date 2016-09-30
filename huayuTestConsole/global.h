#pragma once

#include "windows.h"

#define WM_NET			WM_USER+104
#define WM_CAMERA_LOSED WM_USER+108
#define WM_IOCARD_LOSED WM_USER+112



struct _tagSTARTINFO
{
	int Machine ID;

};




unsigned int  WINAPI threadProc(PVOID pParam);	//Ïß³Ìº¯Êý

