#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include "Engine.h"

int nScreenWidth = 120;
int nScreenHeight = 30;

int main()
{
	// Creating Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// setting up everything
	// now only for snake
	std::vector<std::pair<int, int>> sb_pos;
	sb_pos.push_back({ nScreenWidth / 2, nScreenHeight / 2 });
	for (int i = 1; i < 10; i++) { sb_pos.push_back({ sb_pos[i - 1].first - 1, sb_pos[i - 1].second }); }
	std::pair<int, int> snake_head = sb_pos[0];
	int sn_len = 10;

	// now for movement
	int left = 0, right = 2, up = 3, down = 1;
	int dir = 3;

	// variablae for key state
	bool bKey[4];

	// clearing screen // or filling array winth 'space'
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) { screen[i] = L' '; }

	// main game loop
	while (true) {

		// virtual slow down
		if (dir == left || dir == right) std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (dir == up || dir == down) std::this_thread::sleep_for(std::chrono::milliseconds(100));

		// keyboard input
		for (int k = 0; k < 4; k++) {                         //    A   W   D   S
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x41\x57\x44\x53"[k]))) != 0;
		}

		// moveing snake to direction
		for (int i = 0; i < 4; i++) { if (bKey[i]) dir = i; }
		if (dir == right) { snake_head.first++; if (snake_head.first >= nScreenWidth) snake_head.first = 0; }
		if (dir == left) { snake_head.first--; if (snake_head.first < 0) snake_head.first = nScreenWidth - 1; }
		if (dir == up) { snake_head.second++; if (snake_head.second >= nScreenHeight) snake_head.second = 0; }
		if (dir == down) { snake_head.second--; if (snake_head.second < 0) snake_head.second = nScreenHeight - 1; }
		sb_pos.push_back(snake_head);
		sb_pos.erase(sb_pos.begin());
		

		// adding snake to string
		for (int i = 0; i < sb_pos.size(); i++) {
			screen[sb_pos[i].second * nScreenWidth + sb_pos[i].first] = L'#';
		}

		// Presenting frame
		//screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		// cleaning screen
		for (int i = 0; i < nScreenWidth * nScreenHeight; i++) { screen[i] = L' '; }
	}

	//system("pause");
	return 0;
}