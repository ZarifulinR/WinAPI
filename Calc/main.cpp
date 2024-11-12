#include<Windows.h>
#define IDC_STATIC 1000
#define IDC_EDIT   1001
#define IDC_BUTTON 1002
CONST CHAR g_sz_MY_Window_Class[] = "Calc";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInmtance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.style = NULL;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInmtance;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszClassName = g_sz_MY_Window_Class;
	wc.lpszMenuName = NULL;
	if (!RegisterClassEx(&wc) > 0)
	{
		MessageBox(NULL, " Class registrationfaled", "Error", MB_OK | MB_ICONERROR);
	}

	HWND hwnd = CreateWindowEx
	(NULL,
		g_sz_MY_Window_Class,
		g_sz_MY_Window_Class,
		WS_OVERLAPPEDWINDOW ,
		CW_USEDEFAULT, CW_USEDEFAULT ,
		500, 600,
		NULL,
		NULL,
		hInmtance,
		NULL
	);
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		//TranslateMessage(&msg);
		//DispatchMessage(&msg);
		IsDialogMessage(hwnd, &msg);
	}
	return msg.message;

	return 0;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		CreateWindowEx
		(NULL,
			"Static",
			"Это функция создана при помощи функции CreateWindowEx",
			WS_CHILDWINDOW | WS_VISIBLE ,
			10,
			10,
			500, 25,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),
			NULL

		);
		CreateWindowEx
		(NULL,
			"Edit",
			"",
			WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER ,
			10,
			48,
			450,
			23,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			310, 88,
			150, 32,
			hwnd,
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL

		);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hStatic = GetDlgItem(hwnd, IDC_STATIC);
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hStatic,WM_SETTEXT,0,(LPARAM)sz_buffer);
			SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)sz_buffer);
			SendMessage(GetDlgItem(hwnd,IDC_BUTTON),WM_SETTEXT,0,(LPARAM)sz_buffer);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
	return FALSE;
}