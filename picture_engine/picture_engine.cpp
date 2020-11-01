#include "picture_engine.h"



bool picture_engine::construct(int screen_w, int screen_h, int pw, int ph)
{
	screen_width = screen_w; screen_height = screen_h;
	pixel_width = pw; pixel_height = ph;

	default_picture = new picture;
	default_picture->create_image(screen_width, screen_height);

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
	delete default_picture;
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
	start_opengl();
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &glBuffer);
	glBindTexture(GL_TEXTURE_2D, glBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

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

		// start opengl test
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, default_picture->get_array());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
		/*glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex2f(-0.8, -0.8);
		glColor3f(0, 1, 0);
		glVertex2f(0.8, -0.8);
		glColor3f(0, 0, 1);
		glVertex2f(0, 0.9);
		glEnd();*/
		// end opwngl test
		SwapBuffers(glDeviceContext);

		wchar_t sTitle[256];
		swprintf(sTitle, 256, L"%s - FPS: %3.2f", app_name.c_str(), 1.0f / fElapsedTime);
		SetWindowText(hwnd, sTitle);
	}
	if (!onDelete())
		return;
	PostMessage(hwnd, WM_DESTROY, 0, 0);
}

bool picture_engine::start_opengl()
{
	glDeviceContext = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	int pf = 0;
	if (!(pf = ChoosePixelFormat(glDeviceContext, &pfd))) return false;
	SetPixelFormat(glDeviceContext, pf, &pfd);

	if (!(glRenderContext = wglCreateContext(glDeviceContext))) return false;
	wglMakeCurrent(glDeviceContext, glRenderContext);

	wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
	wglSwapInterval(0);

	return true;
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



// for picture class
bool picture::load_image(std::wstring src)
{	
	return false;
}

bool picture::create_image(int w, int h)
{
	//if (pixel_array) delete[] pixel_array;
	width = w; height = h;
	pixel_array = new pixel[width * height];
	for (int i = 0; i < width * height; i++) pixel_array[i] = pixel();

	return true;
}

pixel* picture::get_array()
{
	return pixel_array;
}


// for pixel class
pixel::pixel()
{
	r = 255; g = 1; b = 0; a = 255;
}

pixel::pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	r = red; g = green; b = blue; a = alpha;
}
