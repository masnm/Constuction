#pragma once


#include <Windows.h>


class Window
{
public:
	Window();
	// initialize the window
	bool init();

	bool broadcast();

	// reslesae the window
	bool release();


	bool isRun();

	// events
	virtual void onCreate() = 0;
	virtual void onUpadate() = 0;
	virtual void onDestroy();

	~Window();

protected:
	HWND m_hwnd;
	bool m_is_run;
};

