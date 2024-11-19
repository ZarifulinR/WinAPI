#include<Windows.h>
#include"resource.h"
const CHAR g_sz_CLASS_NAME[] = "Calc PV_319";
CONST INT g_i_INTERVAL = 5;
CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_BUTTON_DOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;


CONST INT g_i_DISPLAY_WIDTH = g_i_BUTTON_SIZE*5  + g_i_INTERVAL*4 ;
CONST INT  g_i_DISPLAY_HEIGHT = 22;

CONST INT g_i_START_Y = 10;
CONST INT g_i_START_X = 10;
CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL;
CONST INT g_i_OPERATION_BUTTON_START_X = g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3;
CONST INT g_i_OPERATION_BUTTON_START_Y = g_i_BUTTON_START_Y;
CONST INT g_i_CONTROL_BUTTON_START_X = g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4;
CONST INT g_i_CONTROL_BUTTON_START_Y = g_i_BUTTON_START_Y;

CONST INT g_i_WINDOW_WIDTH = g_i_DISPLAY_WIDTH + g_i_START_X * 2+16;
CONST INT g_i_WINDOW_HEIGTH = g_i_DISPLAY_HEIGHT + g_i_START_Y * 2+(g_i_BUTTON_SIZE+g_i_INTERVAL)*4 +50;

CONST CHAR* g_OPERATIONS[] = { "+","-","*","/" };

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM Lparam);
INT WINAPI WinMain(HINSTANCE hInstanse, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// 1) Регистрация класса окна.
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(hInstanse, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hInstanse, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(hInstanse, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0, 255, 255));
	wc.hInstance = hInstanse;
	wc.lpszClassName = g_sz_CLASS_NAME;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszMenuName = NULL;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration faled", NULL, MB_OK | MB_ICONERROR);
	}
	// 2) Создание окна.
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,
		g_sz_CLASS_NAME,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME^WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGTH,
		NULL,
		NULL,
		hInstanse,
		NULL

	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//Запуск окнв.
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
	return 0;
}
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM Lparam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{

		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 10,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDI_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);
		CHAR sz_digit[2] = "0";
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = 49 + i + j;
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					g_i_BUTTON_START_X  + j * (g_i_BUTTON_SIZE + g_i_INTERVAL), 
					g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (2 - i / 3),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_0 + i + j,
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_BUTTON_START_X,
			g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_BUTTON_START_X  + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		for (int i = 0; i < 4; i++)
		{
			CreateWindowEx
			(
				NULL, "Button", g_OPERATIONS[i],
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				g_i_OPERATION_BUTTON_START_X ,
				g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)IDC_BUTTON_PLUS + i,
				GetModuleHandle(NULL),
				NULL
			);
		}
		CreateWindowEx
		(NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_CONTROL_BUTTON_START_X,
			g_i_CONTROL_BUTTON_START_Y,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL

			);
		CreateWindowEx
		(NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_CONTROL_BUTTON_START_X,
			g_i_CONTROL_BUTTON_START_Y+ g_i_BUTTON_SIZE+g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL),
			NULL

			);
		CreateWindowEx
		(NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_CONTROL_BUTTON_START_X,
			g_i_CONTROL_BUTTON_START_Y+ (g_i_BUTTON_SIZE+g_i_INTERVAL)*2,
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL

			);
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
	default: return DefWindowProc(hwnd, uMsg, wParam, Lparam);
	}
}
