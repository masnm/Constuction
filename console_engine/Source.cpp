
#include "engine.h"

class example : public engine
{
public:
	
	virtual bool name_app() override
	{
		m_sAppName = L"MASNM : First Person View ";
		return true;
	}


private:

	int sc_width;
	int sc_height;

	float playerX;
	float playerY;
	float playerA;

	int mapWidth;
	int mapHeight;

	float deep_limit;

	float fov;

	string map;

	virtual bool onCreate() override
	{
		sc_width = get_width();
		sc_height = get_height();

		playerX = 8.0f;
		playerY = 8.0f;
		playerA = 0.0f;

		mapWidth = 16;
		mapHeight = 16;

		deep_limit = 16.0f;

		fov = 3.14159 / 2.0;

		map += "XXXXXXXXXXXXXXXX";
		map += "X..............X";
		map += "X..............X";
		map += "X..............X";
		map += "X..............X";
		map += "X..............X";
		map += "X..............X";
		map += "X..............X";
		map += "X..............X";
		map += "X........x.....X";
		map += "X..............X";
		map += "X..............X";
		map += "X..............X";
		map += "X..............X";
		map += "X..............X";
		map += "XXX.X.X.X.XXXXXX";

		return true;
	}


	virtual bool onUpdate(float fElapsedTime) override
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		if (GetAsyncKeyState(0x41)) playerA -= (0.2f)*fElapsedTime;//a
		if (GetAsyncKeyState(0x44)) playerA += (0.2f)*fElapsedTime;//d
		//if (GetAsyncKeyState(0x43)) ;//c
		//if (GetAsyncKeyState(0x44)) ;//d
		//if (GetAsyncKeyState(0x45)) ;//e
		//if (GetAsyncKeyState(0x46)) ;//f
		//if (GetAsyncKeyState(0x53)) ;//s
		if (GetAsyncKeyState(0x57))//w
		{
			playerX += sinf(playerA) * 5.0f * fElapsedTime;
			playerY += sinf(playerA) * 5.0f * fElapsedTime;
		}
		if (GetAsyncKeyState(0x53))//s
		{
			playerX -= sinf(playerA) * 5.0f * fElapsedTime;
			playerY -= sinf(playerA) * 5.0f * fElapsedTime;
		}


		clear();
		for (int x = 0; x < sc_width; x++)
		{
			float rayA = (playerA - fov / 2.0f) + ((int)x / (int)sc_width) * fov;
			float wall_distance = 0;
			bool wall_found = false;
			float eyeX = sinf(rayA);
			float eyeY = cosf(rayA);
			while (!wall_found && wall_distance < deep_limit) {
				wall_distance += 0.1f;
				int testx = (int)(playerX + eyeX * wall_distance);
				int testy = (int)(playerY + eyeY * wall_distance);
				if (testx < 0 || testx >= mapWidth || testy < 0 || testy >= mapHeight) {
					wall_found = true;
					wall_distance = deep_limit;
				}
				else {
					if (map[testy * mapWidth + testx] == 'X')
						wall_found = true;
				}
			}
			int ceiling = (float)(sc_height / 2.0f) - sc_height / ((float)wall_distance);
			int floor = sc_height - ceiling;

			pixel pv;
			if (wall_distance < deep_limit / 4.0f) pv = solid;
			else if (wall_distance < deep_limit / 3.0f) pv = dsade;
			else if (wall_distance < deep_limit / 2.0f) pv = hsade;
			else if (wall_distance < deep_limit) pv = lsade;
			else pv = none;

			for (int y = 0; y < sc_height; y++) {
				if (y < ceiling) {
					draw(x, y, FG_CYAN);
				}
				else if (y > ceiling && y < floor) {
					//draw(x, y, FG_BLUE,pv);
				}
				else {
					draw(x, y, FG_GREEN);
				}
			}

		}
		

				
		return true;
	}

	virtual bool onDestroy() override
	{
		

		return true;
	}
};

int main()
{
	example game;

	// not work below 120
	if (game.construct(160, 80, 8, 8))
	{
		game.start();
	}


	return 0;
}