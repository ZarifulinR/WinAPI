#include<Windows.h>
#include"resource.h"
CONST CHAR sz_LOGIN[] = "Ввудите имя пользователя";
BOOL WINAPI DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmd, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL WINAPI DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_LOGIN);

	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]  {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, sz_LOGIN) == 0)
				SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)"");
			if (HIWORD(wParam)== EN_KILLFOCUS&&strcmp(sz_buffer,"")==0)
				SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_LOGIN);
		}
		break;
		case IDC_BUTTON_COPY:

		{
			
			

			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			/*hEditLogin = GetFocus();
			if (GetFocus())
			{
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"Login");
			}*/
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			//Функция GetDlgItem() возвращает HWND дочернего элемента окна по его ResourceID.
			// HWND - Handler to window -Это число при помощи которого можно обратится к окну. 
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		
		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК! ", "info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return false;
}