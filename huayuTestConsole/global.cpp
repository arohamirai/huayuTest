#include "global.h"
#include"vector"
//INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
//{
//	UNREFERENCED_PARAMETER(lParam); // ���⾎��ʱ�ľ���
//	switch (uMsg) {
//	case WM_INITDIALOG:
//		return (TRUE); // TRUE ��ʾ���Ѵ���������Ϣ
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK
//			|| LOWORD(wParam) == IDCANCEL) {
//				EndDialog(hWnd, TRUE);
//				return (TRUE); // TRUE ��ʾ���Ѵ���������Ϣ
//		}
//		break;
//	}
//	return (FALSE); // FALSE ��ʾ��û�д��������Ϣ
//}

extern HANDLE *g_pEventHandle;
extern BOOL *g_work;


unsigned int  WINAPI MainThreadProc(PVOID pParam)	//��̨���̺߳���
{
	int machineID = (int)pParam;				//��̨��ʶ





	return 0;
}



unsigned int  WINAPI threadProc(PVOID pParam)	//�̺߳���
{
	int machineID = (int)pParam;				//��̨��ʶ





	return 0;
}


