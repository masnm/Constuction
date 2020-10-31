#include "picture_engine.h"



bool picture_engine::construct(int screen_w, int screen_h, int pw, int ph)
{
	screen_width = screen_w; screen_height = screen_h;
	pixel_width = pw; pixel_height = ph;

	return true;
}

picture_engine::picture_engine()
{
	window_active = false;
	wc = { 0 };
	hwnd = NULL;
	app_name = L"Failure";
}

picture_engine::~picture_engine()
{
}

bool picture_engine::create_window()
{
	// setting up the window class
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpfnWndProc = windowEventProgram;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.lpszMenuName = L"Menu Name";
	wc.hbrBackground = nullptr;

	wc.lpszClassName = L"PictureEngine";
	RegisterClass(&wc);

	// Define window furniture
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
	RECT rWndRect = { 0, 0, (LONG)screen_width * (LONG)pixel_width, (LONG)screen_height * (LONG)pixel_height };

	// Keep client size as requested
	AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);

	int width = rWndRect.right - rWndRect.left;
	int height = rWndRect.bottom - rWndRect.top;

	hwnd = CreateWindowEx(dwExStyle, L"PictureEngine", L"", dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, GetModuleHandle(nullptr), this);

	return true;
}

bool picture_engine::start()
{
	if (!create_window())
		return false;

	window_active = true;
	std::thread t = std::thread(&picture_engine::picture_engine_thread, this);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	t.join();

	return true;
}

void picture_engine::picture_engine_thread()
{
	if (!onCreate())
		window_active = false;

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	while (window_active) {
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();
		if (!onUpdate())
			window_active = false;
		wchar_t sTitle[256];
		swprintf(sTitle, 256, L"%s - FPS: %3.2f", app_name.c_str(), 1.0f / fElapsedTime);
		SetWindowText(hwnd, sTitle);
	}
	if (!onDelete())
		return;
	PostMessage(hwnd, WM_DESTROY, 0, 0);
}

LRESULT CALLBACK picture_engine::windowEventProgram(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static picture_engine* sge;
	switch (uMsg)
	{
	case WM_CREATE:		sge = (picture_engine*)((LPCREATESTRUCT)lParam)->lpCreateParams;	return 0;
	case WM_CLOSE:		sge->window_active = false;									return 0;
	case WM_DESTROY:	PostQuitMessage(0);			return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}