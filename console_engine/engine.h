#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>
using namespace std;

#include <windows.h>

class engine
{
protected:
	enum colour : wchar_t
	{
		FG_BLACK = 0x0000,
		FG_DARK_BLUE = 0x0001,
		FG_DARK_GREEN = 0x0002,
		FG_DARK_CYAN = 0x0003,
		FG_DARK_RED = 0x0004,
		FG_DARK_MAGENTA = 0x0005,
		FG_DARK_YELLOW = 0x0006,
		FG_GREY = 0x0007,
		FG_BLUE = 0x0009,
		FG_GREEN = 0x000A,
		FG_CYAN = 0x000B,
		FG_RED = 0x000C,
		FG_MAGENTA = 0x000D,
		FG_YELLOW = 0x000E,
		FG_WHITE = 0x000F,
		BG_BLACK = 0x0000,
		BG_DARK_BLUE = 0x0010,
		BG_DARK_GREEN = 0x0020,
		BG_DARK_CYAN = 0x0030,
		BG_DARK_RED = 0x0040,
		BG_DARK_MAGENTA = 0x0050,
		BG_DARK_YELLOW = 0x0060,
		BG_GREY = 0x0070,
		BG_BLUE = 0x0090,
		BG_GREEN = 0x00A0,
		BG_CYAN = 0x00B0,
		BG_RED = 0x00C0,
		BG_MAGENTA = 0x00D0,
		BG_YELLOW = 0x00E0,
		BG_WHITE = 0x00F0,
	};
	enum pixel : wchar_t
	{
		solid = 0x2588
	};
private:
	HANDLE console_handle;
	CONSOLE_SCREEN_BUFFER_INFO c_scr_buff_info;
	HANDLE m_hConsole;
	SMALL_RECT small_rec;


protected:
	int m_nScreenWidth;
	int m_nScreenHeight;
	CHAR_INFO* m_bufScreen;
	atomic<bool> m_bAtomActive;
	condition_variable m_cvGameFinished;
	mutex m_muxGame;
	wstring m_sAppName;



public:
	engine();
	bool construct (int sw, int sh, int fw, int fh);
	void start();
	void engine_thread();
	~engine();



public:
	void clip(int& x, int& y);
	bool clear(engine::colour col);
	bool draw(int x, int y, engine::colour col, pixel px = solid);



public:
	virtual bool name_app() = 0;
	virtual bool onCreate() = 0;
	virtual bool onUpdate(float fElapsedTime) = 0;
};