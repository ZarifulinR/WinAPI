#include<Windows.h>
//#define MASS_BOX
INT WINAPI WinMain(HINSTANCE hInmtance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{

#ifdef MASS_BOX
	MessageBox
	(
		NULL,
		"Hello WinAPI",
		"Заголовок окна",
		MB_OK | MB_YESNOCANCEL
		| MB_HELP | MB_SYSTEMMODAL

	);


#endif // MASS_BOX

	return 0;
}