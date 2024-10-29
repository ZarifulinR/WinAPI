#include<Windows.h>
#include"resource.h"

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
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			//������� GetDlgItem() ���������� HWND ��������� �������� ���� �� ��� ResourceID.
			// HWND - Handler to window -��� ����� ��� ������ �������� ����� ��������� � ����. 
			CONST INT SIZE = 256;
			CHAR sz_buffr[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffr);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffr);

		}
		break;
		case IDOK: MessageBox(hwnd, "���� ������ ������ ��! ", "info", MB_OK | MB_ICONINFORMATION);break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return false;
}