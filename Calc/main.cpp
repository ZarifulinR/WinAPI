#include<Windows.h>
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
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 600,
		NULL,
		NULL,
		hInmtance,
		NULL
	);
	HWND hwndButton = CreateWindow
	(
		NULL.,
		"+",
		 WS_CHILD | WS_VISIBLE,
		10,
		10,
		100,
		100,
		hwnd,
		NULL,
		DrvGetModuleHandle(NULL,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
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
	case WM_COMMAND:
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