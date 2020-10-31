#pragma once

#include <Windows.h>
#include <thread>
#include <chrono>
#include <string>

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

protected:
	bool create_window();
	void picture_engine_thread();
	static LRESULT CALLBACK windowEventProgram(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	bool construct(int screen_w = 320, int screen_h = 240, int pw = 2, int ph = 2);
	bool start();

};