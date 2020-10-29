
#include "engine.h"

class example : public engine
{
public:

	// Inherited via engine
	virtual bool onCreate() override
	{
		return true;
	}
	virtual bool onUpdate(float fElapsedTime) override
	{
		if (GetAsyncKeyState(0x41)) return false;
		for (int i = 0; i < 160; i++)
			for (int j = 0; j < 120; j++)
				draw(i, j, FG_BLACK);
		return true;
	}
};

int main()
{
	// Use olcConsoleGameEngine derived app
	example game;

	// Create a console with resolution 160x100 characters
	// Each character occupies 8x8 pixels
	game.construct( 160, 120, 8, 8);

	// Start the engine!
	game.start();

	return 0;
}