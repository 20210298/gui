#include <windows.h>
#include <stdio.h>
#include <string.h>

HWND _hWnd2;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASS WndClass;
    WndClass.style = NULL;
    WndClass.lpfnWndProc = WndProc;	// �� �Լ������� �̺�Ʈ ó��
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = "Hello";	// ClassName���� ������ ����

    if (!RegisterClass(&WndClass)) return NULL;

    hWnd = CreateWindow(
        "Hello",	// ����� Ŭ���� �̸�
        "Hello",	// ������ Ÿ��Ʋ
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

    // _hWnd2
    WndClass.lpfnWndProc = WndProc2;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WndClass.lpszClassName = "WND2";

    if (!RegisterClass(&WndClass)) return NULL;

    _hWnd2 = CreateWindow(
        "WND2",
        "World",
        WS_OVERLAPPEDWINDOW,
        600,
        0,
        600,
        400,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(_hWnd2, nCmdShow);
    UpdateWindow(_hWnd2);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
    switch (mesg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return FALSE;
    case WM_LBUTTONDOWN:
        HWND hNote;
        hNote = _hWnd2;/*FindWindow(NULL, "������� - �޸���");*/
        HDC hdc;     
        hdc = GetDC(hNote);
        TextOut(hdc, 0, 0, "Hello", 5);
        ReleaseDC(hNote, hdc);
        //SetWindowText(_hWnd2, "Black");
        //MessageBox(hWnd, "�ȳ��ϼ���", "�λ�", MB_OK);
        break;
        /*case WM_MOUSEMOVE:
            int x, y;
            char szPos[256];
            HDC hdc;
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            sprintf(szPos, "%04d %04d", x, y);
            hdc = GetDC(hWnd);
            TextOut(hdc, 0, 0, szPos, strlen(szPos));
            ReleaseDC(hWnd, hdc);
            break;*/
    }
    return DefWindowProc(hWnd, mesg, wParam, lParam);

}LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
    switch (mesg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return FALSE;
    case WM_LBUTTONDOWN:
        MessageBox(hWnd, "����������", "�λ�", MB_OK);
    }
    return DefWindowProc(hWnd, mesg, wParam, lParam);
}