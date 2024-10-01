#include <windows.h>
#include <stdio.h>
#include <string.h>

LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

HINSTANCE _hInstance;
HWND _hWnd;
HWND _hEdit;
HWND _hStatic;

WNDPROC _fpBtnProc;
LRESULT CALLBACK BtnProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)
{
    HWND hWnd1;
    MSG msg;
    WNDCLASS WndClass;
    WndClass.style = NULL;
    WndClass.lpfnWndProc = WndProc1;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = "WND1";
    if (!RegisterClass(&WndClass)) return NULL;

    WndClass.lpfnWndProc = WndProc2;
    WndClass.lpszClassName = "WND2";
    if (!RegisterClass(&WndClass)) return NULL;

    hWnd1 = CreateWindow(
        "WND1",
        "부모윈도우 컴퓨터공학과 2학년 김주형 20210298",
        WS_OVERLAPPEDWINDOW,
        0, 0, 500, 300,
        NULL, NULL, hInstance, NULL
    );

    _hWnd = hWnd1;//
    _hInstance = hInstance;

    ShowWindow(hWnd1, nCmdShow);
    UpdateWindow(hWnd1);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc1(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdt1;
    static HWND hWnd2;
    static HWND hWnd3;

    RECT rt;
    int width, height;

    switch (mesg)
    {
    case WM_CREATE:
        hEdt1 = CreateWindow("edit",
            "",
            WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
            0, 0, 200, 200,
            hWnd, (HMENU)11, _hInstance, NULL);
        _hEdit = hEdt1;//
        hWnd2 = CreateWindow("static",
            "",
            WS_VISIBLE | WS_CHILD,
            0, 0, 200, 200, hWnd, NULL, _hInstance, NULL);
        _hStatic = hWnd2;//
        hWnd3 = CreateWindow("WND2", "자식윈도우",
            WS_OVERLAPPED | WS_VISIBLE,
            0, 300, 500, 200,
            hWnd, NULL, _hInstance, NULL);
        break;
    case WM_SIZE:
        GetClientRect(hWnd, &rt);
        width = rt.right - rt.left;
        height = rt.bottom - rt.top;

        MoveWindow(hEdt1, 0, 0, width / 2, height, true);

        MoveWindow(hWnd2, width / 2, 8, (width / 2) - 8, height - 16, true);

        MoveWindow(hWnd3, rt.left, rt.top + height, width, 150, true);

        break;
    case WM_MOVE:
        RECT rt;
        int width;
        int height;
        GetWindowRect(hWnd, &rt);
        width = rt.right - rt.left;
        height = rt.bottom - rt.top;
        MoveWindow(hWnd3, rt.left, rt.top + height, width, 150, true);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return FALSE;
    }
    return DefWindowProc(hWnd, mesg, wParam, lParam);
}

#define NO_BUTTON 4
#define IDC_BUTTON 100
#define MAX_CHARS 2048
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
    static HWND hBtn[NO_BUTTON];
    static HWND hEdt2;
    static char szTitle[NO_BUTTON][20] = { "이름은","학번은","지움","" };
    static char szMsg[NO_BUTTON][30] = { "김주형","20210298","" };

    int i;
    static int btn_width = 50;
    static int btn_height = 50;

    static char szTemp[MAX_CHARS];

    switch (mesg)
    {
    case WM_CREATE:
        for (i = 0; i < NO_BUTTON; i++) {
            hBtn[i] = CreateWindow("button", szTitle[i],
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0,
                hWnd, (HMENU)(IDC_BUTTON + i), _hInstance, NULL);
        }
        _fpBtnProc = (WNDPROC)GetWindowLongPtr(hBtn[NO_BUTTON - 1], GWLP_WNDPROC);
        SetWindowLongPtr(hBtn[NO_BUTTON - 1], GWLP_WNDPROC, (LONG_PTR)BtnProc);

        hEdt2 = CreateWindow("edit",
            "",
            WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
            0, 0, 0, 0,
            hWnd, (HMENU)22, _hInstance, NULL);
        break;
    case WM_SIZE:
    {
        int sizex = LOWORD(lParam);
        int sizey = HIWORD(lParam);

        btn_height = sizey / 2;
        btn_width = sizex / NO_BUTTON;

        for (i = 0; i < NO_BUTTON - 1; i++) {
            MoveWindow(hBtn[i], i * btn_width, 0, btn_width, btn_height, true);
        }
        MoveWindow(hBtn[i], i * btn_width, 0, btn_width, btn_height * 2, true);
        MoveWindow(hEdt2, 0, btn_height, btn_width * (NO_BUTTON - 1), btn_height, true);
    }   break;
    case WM_COMMAND:
        int id;
        id = LOWORD(wParam);
        int code;
        code = HIWORD(wParam);

        if (id == 22) {
            if (code == EN_CHANGE) {
                GetWindowText(hEdt2, szTemp, MAX_CHARS - 1);
                SetWindowText(_hEdit, szTemp);
            }
        }
        else {
            for (i = 0; i < NO_BUTTON - 1; i++) {
                if (id == (IDC_BUTTON + i)) {
                    SetWindowText(_hEdit, szMsg[i]);
                    if (id == IDC_BUTTON + 2) {
                        SetWindowText(_hEdit, szMsg[2]);
                        SetWindowText(hEdt2, szMsg[2]);
                    }
                    break;
                }
            }
        }
        break;
    case WM_DESTROY:
        return FALSE;
    }
    return DefWindowProc(hWnd, mesg, wParam, lParam);
}

LRESULT CALLBACK BtnProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
    switch (mesg)
    {
    case WM_LBUTTONDOWN:
        InvalidateRect(_hStatic, NULL, true);
        break;
    case WM_MOUSEMOVE:
        int x, y, mx, my;
        x = LOWORD(lParam);
        y = HIWORD(lParam);

        RECT rt_main, rt_btn;
        GetClientRect(_hStatic, &rt_main);
        GetClientRect(hWnd, &rt_btn);

        int width;
        int height;
        width = rt_main.right - rt_main.left;
        height = rt_main.bottom - rt_main.top;

        mx = x * (width) / (rt_btn.right - rt_btn.left);
        mx = (mx < 1) ? 1 : (mx > (width - 1) ? width - 1 : mx);
        my = y * (height) / (rt_btn.bottom - rt_btn.top);
        my = (my < 1) ? 1 : (my > (height - 1) ? height - 1 : my);

        HDC hdc;
        hdc = GetDC(_hStatic);

        SetPixel(hdc, mx - 1, my - 1, RGB(0, 0, 255));
        SetPixel(hdc, mx, my - 1, RGB(0, 0, 255));
        SetPixel(hdc, mx - 1, my, RGB(0, 0, 255));
        SetPixel(hdc, mx, my, RGB(0, 0, 255));

        ReleaseDC(_hStatic, hdc);
        break;
    }
    return CallWindowProc(_fpBtnProc, hWnd, mesg, wParam, lParam);
}
