#include "Window.h"

Window* window = nullptr;

Window::Window()
{
    m_hwnd = NULL;
    m_is_run = false;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        // event fired when window will be created
        window->onCreate();
        break;
    }
    case WM_DESTROY:
    {
        // event fired when window will be destroyed
        window->onDestroy();
        ::PostQuitMessage(0);
        break;
    }
    default:
        return ::DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return NULL;
}

bool Window::init()
{
    WNDCLASSEX wc = { 0 };
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    //wc.cbSize = sizeof(wc);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc;

    if (!::RegisterClassEx(&wc))        // if the initialization class failed
        return false;

    if (!window)
        window = this;

    m_hwnd = ::CreateWindowExW ( WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX", WS_OVERLAPPEDWINDOW, 100,100, 1366, 720,
        NULL, NULL, NULL, NULL);

    if (!m_hwnd)                        // if failed to create window
        return false;

    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    if (!window)
        window = this;

    // setting m_is_run is true to set window is running and inittialized
    m_is_run = true;

    return true;
}

bool Window::broadcast()
{
    MSG msg;
    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    window->onUpadate();

    Sleep(0);           // virtual slowdown

    return true;
}

bool Window::release()
{
    // destroying the window
    if (!::DestroyWindow(m_hwnd))
        return false;

    return true;
}

bool Window::isRun()
{
    return m_is_run;
}

void Window::onCreate()
{
}

void Window::onUpadate()
{
}

void Window::onDestroy()
{

    m_is_run = false;
}

Window::~Window()
{
}
