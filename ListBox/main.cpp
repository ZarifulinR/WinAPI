#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include <cstdio>
CONST CHAR* g_VALUES[] = { "My","First","List","Box" };
BOOL CALLBACK DlgProc(HWND hwndd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAddItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);

	return false;

}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{

		HICON hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hicon);
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_VALUES) / sizeof(g_VALUES[0]); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)g_VALUES[i]);

		}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_ADD:
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, (DLGPROC)DlgProcAddItem, 0);
			break;

		case IDOK:
		{

			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);

			CHAR sz_message[SIZE]{};
			sprintf(sz_message, "�� ������� ����� �%i �� ���������� \"%s\".", i, sz_buffer);
			MessageBox(hwnd, sz_message, "info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}

	return false;
}
BOOL CALLBACK DlgProcAddItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD));

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{

			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND heditAdd = GetDlgItem(hwnd, IDC_EDIT_ADD);
			SendMessage(heditAdd, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			HWND hList = GetDlgItem(GetParent(hwnd), IDC_LIST1);
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
		}
		
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;

	}
	return false;
}