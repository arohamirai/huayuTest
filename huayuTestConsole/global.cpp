#include "global.h"
#include"vector"
//INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
//{
//	UNREFERENCED_PARAMETER(lParam); // 避免編译时的警告
//	switch (uMsg) {
//	case WM_INITDIALOG:
//		return (TRUE); // TRUE 表示我已处理过这个消息
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK
//			|| LOWORD(wParam) == IDCANCEL) {
//				EndDialog(hWnd, TRUE);
//				return (TRUE); // TRUE 表示我已处理过这个消息
//		}
//		break;
//	}
//	return (FALSE); // FALSE 表示我没有处理这个消息
//}

extern HANDLE *g_pEventHandle;
extern BOOL *g_work;


unsigned int  WINAPI MainThreadProc(PVOID pParam)	//机台主线程函数
{
	int machineID = (int)pParam;				//机台标识





	return 0;
}



unsigned int  WINAPI threadProc(PVOID pParam)	//线程函数
{
	int machineID = (int)pParam;				//机台标识





	return 0;
}


