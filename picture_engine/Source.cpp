
#include "picture_engine.h"

class my_game : public picture_engine
{
	// Inherited via picture_engine
	virtual bool onCreate() override
	{
		return true;
	}
	virtual bool onUpdate() override
	{
		return true;
	}
	virtual bool onDelete() override
	{
		return true;
	}
};

int main()
{
	my_game game;
	game.construct();
	game.start();

	return 0;
}