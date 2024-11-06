#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include"resource.h"
CONST CHAR* g_VALUES[] = { "This","is","My","First""Combo","Box" };
BOOL CALLBACK DlgProc(HWND hwndd, UINT uMsg, WPARAM wParam, LPARAM lParam);
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
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		for (int  i = 0; i < sizeof(g_VALUES)/sizeof(g_VALUES[0]); i++)
		{
			SendMessage (hCombo, CB_ADDSTRING, 0, (LPARAM)g_VALUES[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{

			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			SendMessage(hCombo, CB_GETLBTEXT, i,(LPARAM)sz_buffer);

			CHAR sz_message[SIZE]{};
			sprintf(sz_message, "�� ������� ����� �%i �� ���������\"%s\".", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return false;
}