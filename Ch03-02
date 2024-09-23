#include <windows.h>
#include <stdio.h>
#include <string.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE _hInstance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Hello";

	if (!RegisterClass(&WndClass)) return NULL;
	_hInstance = hInstance;

	hWnd = CreateWindow(
		"Hello",
		"Hello",
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		600,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	static HWND hBtn;
	static HWND hBtn2;


	switch (mesg)
	{
	case WM_CREATE:
		hBtn = CreateWindow(
			"button",
			"클릭",
			WS_VISIBLE | WS_CHILD,
			0,
			0,
			200,
			200,
			hWnd,
			(HMENU)888,
			_hInstance,
			NULL
		);
		hBtn2 = CreateWindow(
			"button",
			"클릭2",
			WS_VISIBLE | WS_CHILD,
			200,
			0,
			200,
			200,
			hWnd,
			(HMENU)999,
			_hInstance,
			NULL
		);
		break;
	case WM_COMMAND:	
		int id;
		id = LOWORD(wParam);
		if (id == 888) {
			MessageBox(hWnd, "첫째", "1", MB_OK);
		}
		else if (id == 999) {
			MessageBox(hWnd, "둘째", "2", MB_OK);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}
