#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
CONST CHAR g_sz_MY_Window_Class[] = "My Window";
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInmtance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{

	//  1) Регистрация класса окна.
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadIcon(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInmtance;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_MY_Window_Class;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	//  2) Создание окна.
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_heidth = GetSystemMetrics(SM_CYSCREEN);
	INT window_widht = screen_width * 3 / 4;
	INT window_height = screen_heidth * .75;
	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_heidth / 8;
	HWND hwnd = CreateWindowEx
		(
			NULL,
			g_sz_MY_Window_Class,
			g_sz_MY_Window_Class,
			WS_OVERLAPPEDWINDOW,
			window_start_x, window_start_y,
			window_widht, window_height,
			NULL,
			NULL,
			hInmtance,
			NULL

			);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//  3) Запуск цикла сообщений. 
	MSG msg;
	while (GetMessage(&msg,NULL,0,0)>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message;

	return 0;
}
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_MOVE:
	case WM_SIZE:
	{

		RECT rect;
		GetWindowRect(hwnd, &rect);
		INT window_width = rect.right - rect.left;
		INT windiw_height = rect.bottom - rect.top;

		CONST INT SIZE = 256;
		CHAR sz_titele[SIZE]{};
		sprintf(sz_titele, "%s - Position: %ix%i;\ tSize: %ix%i", g_sz_MY_Window_Class, rect.left,
			rect.top,window_width,windiw_height);
		SendMessage(hwnd,WM_SETTEXT, 0, (LPARAM)sz_titele);
	}
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}