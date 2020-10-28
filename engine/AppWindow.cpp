#include "AppWindow.h"

AppWindow::AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
}

void AppWindow::onUpadate()
{
	Window::onUpadate();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsEngine::get()->release();
}

AppWindow::~AppWindow()
{
}