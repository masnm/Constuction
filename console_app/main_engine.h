#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include <Windows.h>


namespace asn {

	// 2d inplementation
	template<typename type>
	struct i2d {
		type x;
		type y;
		i2d() : x(0), y(0) {}
		i2d(type _x, type _y) : x(_x), y(_y) {}
		i2d& operator = (const i2d& v) = default;
		//i2d& operator = (const i2d& right) { this->x = right.x; this->y = right.y; return *this; }
		i2d operator + (const i2d& right) const { return i2d(this->x + right.x, this->y + right.y); }
		i2d operator - (const i2d& right) const { return i2d(this->x - right.x, this->y - right.y); }
		i2d operator / (const int right) const { return i2d(this->x / right, this - y / right); }
		i2d& operator += (const i2d& right) { this->x += right.x; this->y += right.y; return *this; }
		bool operator == (const i2d& right) const { return (this->x == right.x && this->y == right.y); }
	};
	typedef i2d<int> int_2d;


	// main calss for use
	class asn_console_engine {
	protected:
		float elapsed_time;
		int width, height;
		wchar_t* name;
		wchar_t* screen;
		HANDLE console_handle;
		DWORD dwBytesWritten = 0;
	public:
		bool create_console(int width, int height, int fw, int fh);
		virtual std::string app_name() = 0;
		virtual bool update_loop(float elapsed_time) = 0;
		void update_frame();
		void start();
	public:
		void clear();
	};

	bool asn_console_engine::create_console(int width, int height, int fw, int fh) {

		this->width = width, this->height = height;

		// Creating Screen Buffer
		screen = new wchar_t[width * height];
		console_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = fw;
		cfi.dwFontSize.Y = fh;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FF_DONTCARE;
		//cfi.FontWeight = FW_NORMAL;
		SetCurrentConsoleFontEx(console_handle, false, &cfi);

		COORD coaard; coaard.X = (short)width; coaard.Y = (short)height;
		SMALL_RECT rect; rect.Top = 0; rect.Left = 0; rect.Bottom = width - 1; rect.Right = height - 1;
		SetConsoleWindowInfo(console_handle, TRUE, &rect);
		SetConsoleScreenBufferSize(console_handle, coaard);

		SetConsoleActiveScreenBuffer(console_handle);

		return true;
	}
	
	void asn_console_engine::update_frame()
	{
		wchar_t s[256];
		swprintf_s(s, 256, L"%s - FPS: %3.2f", this->name, 1.0f / elapsed_time);
		SetConsoleTitle(s);
		WriteConsoleOutputCharacter(this->console_handle, this->screen, width*height, { 0,0 }, &this->dwBytesWritten);
	}

	void asn_console_engine::start()
	{
		std::chrono::time_point<std::chrono::system_clock> tp1, tp2;
		std::string str = app_name();
		this->name = new wchar_t[str.length()+1];
		name[str.length()] = '\0';
		for (int i = 0; i < str.length(); i++) {
			name[i] = str[i];
		}

		while (update_loop(elapsed_time)) {
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			elapsed_time = elapsedTime.count();
			update_frame();
		}
	}

	void asn_console_engine::clear()
	{
		for (int i = 0; i < width*height; i++ ) {
			screen[i] = L'P';
		}
	}
}