#pragma once

#include "Window.h"
#include "GraphicsEngine.h"

class AppWindow : public Window
{
public:
	AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpadate() override;
	virtual void onDestroy() override;

	~AppWindow();
};

