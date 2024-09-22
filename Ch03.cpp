#include <windows.h>
#include <stdio.h>
#include <string.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

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

    // _hWnd2
    WndClass.lpfnWndProc = WndProc2;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WndClass.lpszClassName = "WND2";
    if (!RegisterClass(&WndClass)) return NULL;

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

// 자식 윈도우 먼저 죽이고 부모가 죽는다
LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
    static HWND hWnd2; // static 지역변수로 자식 선언, static 안하면 계속 초기화된다
    switch (mesg)
    {
    case WM_CREATE:
        hWnd2 = CreateWindow(
            "WND2",
            "World",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,   // ShowWindow 없이 생성 VISIBLE
            0,
            0,
            600,
            400,
            hWnd,   // WS_CHILD 적용하려면 반드시 부모 윈도우 있어야함
            NULL,
            _hInstance,
            NULL
        );
        break;
    case WM_LBUTTONDOWN:
        SetWindowText(hWnd2, "Black");
        break;
    case WM_DESTROY:
        MessageBox(hWnd, "나죽네", "", MB_OK);
        PostQuitMessage(0); // WM_QUIT
        return FALSE;
    }
    return DefWindowProc(hWnd, mesg, wParam, lParam);
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
    switch (mesg)
    {
    case WM_DESTROY:
        MessageBox(hWnd, "나죽어?", "", MB_OK);
        //PostQuitMessage(0);
        return FALSE;
    }
    return DefWindowProc(hWnd, mesg, wParam, lParam);
}