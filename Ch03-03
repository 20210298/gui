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
	static HWND hEdt1;
	static HWND hEdt2;

	switch (mesg)
	{
	case WM_CREATE:
		hBtn = CreateWindow(
			"button",
			"클릭",
			WS_VISIBLE | WS_CHILD,
			0,
			0,
			100,
			100,
			hWnd,
			(HMENU)888,
			_hInstance,
			NULL
		);
		hEdt1 = CreateWindow("edit",
			"입력ㄱㄱ",
			WS_VISIBLE | WS_BORDER | WS_CHILD | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
			102,
			0,
			100,
			100,
			hWnd,
			(HMENU)999,
			_hInstance,
			NULL);
		hEdt2 = CreateWindow("edit",
			" ",
			WS_VISIBLE | WS_CHILD | ES_READONLY | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
			0,
			102,
			302,
			100,
			hWnd,
			(HMENU)1000,
			_hInstance,
			NULL);
		break;
	case WM_COMMAND:
		int id;
		id = LOWORD(wParam);
		if (id == 888) {
			MessageBox(hWnd, "첫째", "1", MB_OK);
		}
		else if (id == 999) {
			int code;
			code = HIWORD(wParam);
			if (code == EN_CHANGE) {
				char szMsg[1024];
				GetWindowText(hEdt1, szMsg, 1024);
				SetWindowText(hEdt2, szMsg);
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}
