
#include "engine.h"


class example : public engine
{
private:
	int* arr;
	int* tem;
	int sc = 50;

public:
	
	virtual bool name_app() override
	{
		m_sAppName = L"MASNM : Celular Automata";
		return true;
	}

	virtual bool onCreate() override
	{
		arr = new int[get_width() * get_height()];
		tem = new int[get_width() * get_height()];
		memset(arr, 0, get_width() * get_height() * sizeof(int));
		memset(tem, 0, get_width() * get_height() * sizeof(int));

		for (int i = 0; i < get_width() * get_height(); i++)
			tem[i] = (int)(rand() % 2);
		clear();

		return true;
	}

	void clean()
	{
		for (int i = 0; i < get_width() * get_height(); i++)
			tem[i] = 0;
	}
	void fa()
	{
		for (int i = 0; i < get_width() * get_height(); i++)
			tem[i] = rand() % 2;
	}
	void fb()
	{
		clean();
		auto set = [&](int x, int y, string s) {
			for (auto c : s) {
				tem[y * get_width() + x] = c == 'X' ? 1 : 0; x++;
			}
		};

		set(10, 10, "..X..........X..");
		set(10, 11, "X.X..........X.X");
		set(10, 12, ".XX..........XX.");

		/*set(10, 16, "........XXX.....");
		set(10, 17, ".....XXX........");

		set(10, 21, ".XX..........XX.");
		set(10, 22, "X.X..........X.X");
		set(10, 23, "..X..........X..");*/
	}
	void fc()
	{
		clean();
		auto set = [&](int x, int y, string s) {
			for (auto c : s) {
				tem[y * get_width() + x] = c == 'X' ? 1 : 0; x++;
			}
		};

		set(10, 12, "........................X");
		set(10, 13, "......................X.X");
		set(10, 14, "............XX......XX............XX");
		set(10, 15, "...........X...X....XX............XX");
		set(10, 16, "XX........X.....X...XX");
		set(10, 17, "XX........X...X.XX....X.X");
		set(10, 18, "..........X.....X.......X");
		set(10, 19, "...........X...X......");
		set(10, 20, "............XX........");
	}
	void fd()
	{
		clean();
		auto set = [&](int x, int y, string s) {
			for (auto c : s) {
				tem[y * get_width() + x] = c == 'X' ? 1 : 0; x++;
			}
		};
		int i = 01;
		for (; i < get_width()-50; ) {
			set(i, i+0, ".......");
			set(i, i+1, "...XXX.");
			set(i, i+2, "..X..X.");
			set(i, i+3, ".X...X.");
			set(i, i+4, ".X..X..");
			set(i, i+5, ".XXX...");
			set(i, i+6, ".......");
			i += 7;
		}
	}
	void fe()
	{
		clean();
		auto set = [&](int x, int y, string s) {
			for (auto c : s) {
				tem[y * get_width() + x] = c == 'O' ? 1 : 0; x++;
			}
		};

		set(10, 10, "................O.................");
		set(10, 11, "..............O.O.O...............");
		set(10, 12, "............O.O.O.O.O.............");
		set(10, 13, "..........O.O.O.O.O.O.O...........");
		set(10, 14, "........O.O.O..OO.O.O.O.O.........");
		set(10, 15, "......O.O.O.O......O..O.O.O.......");
		set(10, 16, "....O.O.O..O..........O.O.O.O.....");
		set(10, 17, ".....OO.O..............O..O.O.O...");
		set(10, 18, "...O...O..................O.OO....");
		set(10, 19, "....OOO....................O...O..");
		set(10, 20, "..O.........................OOO...");
		set(10, 21, "...OO...........................O.");
		set(10, 22, ".O...O........................OO..");
		set(10, 23, "..OOOO.......................O...O");
		set(10, 24, "O.............................OOO.");
		set(10, 25, ".OOO.............................O");
		set(10, 26, "O...O.......................OOOO..");
		set(10, 27, "..OO........................O...O.");
		set(10, 28, ".O...........................OO...");
		set(10, 29, "...OOO.........................O..");
		set(10, 30, "..O...O....................OOO....");
		set(10, 31, "....OO.O..................O...O...");
		set(10, 32, "...O.O.O..O..............O.OO.....");
		set(10, 33, ".....O.O.O.O..........O..O.O.O....");
		set(10, 34, ".......O.O.O..O......O.O.O.O......");
		set(10, 35, ".........O.O.O.O.OO..O.O.O........");
		set(10, 36, "...........O.O.O.O.O.O.O..........");
		set(10, 37, ".............O.O.O.O.O............");
		set(10, 38, "...............O.O.O..............");
		set(10, 39, ".................O................");
	}
	void ff()
	{
		clean();
		auto set = [&](int x, int y, string s) {
			for (auto c : s) {
				tem[y * get_width() + x] = c == 'O' ? 1 : 0; x++;
			}
		};

		set(10, 10, "..............OO......OO......OO...O.OO..........");
		set(10, 11, "....O........O..O....O..O....O..O..OO.O..........");
		set(10, 12, "O..O.O....O...OO..O...OO..O...O.O.....O.OO.......");
		set(10, 13, "OOOO.O..OOOOOO..OOOOOO..OOOOOO..OOOOOO.O.O.......");
		set(10, 14, ".....O.O.....O.O.....O.O.....O.O.....O.O......OO.");
		set(10, 15, "..OO.O.O.O.O...O.O.O...O.O.O...O.O.O...O.O.....O.");
		set(10, 16, ".O.....O.O...O.O.O...O.O.O...O.O.O...O.O.O.O.OO..");
		set(10, 17, ".OO......O.O.....O.O.....O.O.....O.O.....O.O.....");
		set(10, 18, ".......O.O.OOOOOO..OOOOOO..OOOOOO..OOOOOO..O.OOOO");
		set(10, 19, ".......OO.O.....O.O...O..OO...O..OO...O....O.O..O");
		set(10, 20, "..........O.OO..O..O....O..O....O..O........O....");
		set(10, 21, "..........OO.O...OO......OO......OO..............");
	}


	virtual bool onUpdate(float fElapsedTime) override
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(sc));

		if (GetAsyncKeyState(0x41)) fa();//a
		if (GetAsyncKeyState(0x42)) fb();//b
		if (GetAsyncKeyState(0x43)) fc();//c
		if (GetAsyncKeyState(0x44)) fd();//d
		if (GetAsyncKeyState(0x45)) fe();//e
		if (GetAsyncKeyState(0x46)) ff();//f
		if (GetAsyncKeyState(0x53)) sc == 0 ? sc = 50 : sc = 0;//s
		//if (GetAsyncKeyState(0x57));//w

		auto cell = [&](int x, int y)
		{
			return arr[y * get_width() + x];
		};

		for (int i = 0; i < get_width() * get_height(); i++)
			arr[i] = tem[i];

		for ( int i = 1 ; i < get_width()-1; i++ )
			for (int j = 1; j < get_height()-1; j++ )
			{
				int neighbour = cell(i - 1, j - 1) + cell(i - 1, j + 0) + cell(i - 1, j + 1)
					+ cell(i - 0, j - 1) + 0 + cell(i - 0, j + 1)
					+ cell(i + 1, j - 1) + cell(i + 1, j + 0) + cell(i + 1, j + 1);

				int n = j * get_width() + i;
				if (tem[n])
					tem[n] = neighbour == 2 || neighbour == 3;
				else
					tem[n] = neighbour == 3;

				if (arr[n])
					draw(i, j, FG_BLUE);
				else
					draw(i, j, FG_BLACK);
			}

				
		return true;
	}

	virtual bool onDestroy() override
	{
		//delete arr;
		//delete tem;

		return true;
	}
};

int main()
{
	example game;

	// not work below 120
	if (game.construct(160, 120, 8, 8))
	{
		game.start();
	}


	return 0;
}