#include "global.h"

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