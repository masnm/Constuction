#pragma once

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>

#include <gdiplus.h>

#include <GL/gl.h>
typedef BOOL(WINAPI wglSwapInterval_t) (int interval);
static wglSwapInterval_t* wglSwapInterval;

#include <thread>
#include <chrono>
#include <string>

class pixel {
public:
	union {
		uint32_t n = 0xFF000000;
		struct {
			uint8_t r; uint8_t g; uint8_t b; uint8_t a;
		};
	};
	pixel();
	pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
};

class picture
{
public:
	Gdiplus::Bitmap* bmap;
	uint32_t width, height;
	pixel* pixel_array;

	bool load_image(std::wstring src);
	bool create_image(int w, int h);
	pixel* get_array();
};

class picture_engine
{
protected:
	picture_engine();
	~picture_engine();

protected:
	virtual bool onCreate() = 0;
	virtual bool onUpdate() = 0;
	virtual bool onDelete() = 0;

private:
	bool window_active;
	WNDCLASS wc;
	HWND hwnd;
	int screen_width, screen_height, pixel_width, pixel_height;
	std::wstring app_name;

	picture* default_picture;
	GLuint glBuffer;
	HDC			glDeviceContext = nullptr;
	HGLRC		glRenderContext = nullptr;

protected:
	bool create_window();
	void picture_engine_thread();
	bool start_opengl();
	static LRESULT CALLBACK windowEventProgram(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	bool construct(int screen_w = 320, int screen_h = 240, int pw = 2, int ph = 2);
	bool start();

};