#include "global.h"

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