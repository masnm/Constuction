
#include <fstream>
#include "engine.h"

class example : public engine
{
public:
	
	virtual bool name_app() override
	{
		m_sAppName = L"Hello";
		return true;
	}
	
	virtual bool onCreate() override
	{
		return true;
	}

	virtual bool onUpdate(float fElapsedTime) override
	{
		if (GetAsyncKeyState(0x41)) return false;
		for (int i = 0; i < 120; i++)
			for (int j = 0; j < 120; j++) {
				//draw(i, j, FG_BLACK);
				int c = rand() % 9;
				switch (c) {
				case 0: draw(i, j, FG_BLACK); break;
				case 1: draw(i, j, FG_BLUE); break;
				case 2: draw(i, j, FG_CYAN); break;
				case 3: draw(i, j, FG_DARK_BLUE); break;
				case 4: draw(i, j, FG_DARK_CYAN); break;
				case 5: draw(i, j, FG_DARK_GREEN); break;
				case 6: draw(i, j, FG_DARK_MAGENTA); break;
				case 7: draw(i, j, FG_DARK_RED); break;
				case 8: draw(i, j, FG_DARK_YELLOW); break;
				case 9: draw(i, j, FG_GREEN); break;
				default: draw(i, j, FG_GREY); break;
				}
			}
				
		return true;
	}
};

int main()
{
	example game;

	/*std::ofstream fl("out.txt");

	int n = 400;
	for (int i = 0; i < n; i++) {
		if (game.construct(i, i, 4, 4)) {
			fl << i << "\n";
		}
	}
	fl.close();*/
	// not work below 120
	if (game.construct(120, 120, 4, 4))
	{
		game.start();
	}


	return 0;
}