// console_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include <Windows.h>

struct i2d {
	int x;
	int y;

};

int nScreenWidth = 60;
int nScreenHeight = 30;

int main()
{
	// Creating Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	//SetConsoleMode(hConsole, ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN );

	COORD coaard; coaard.X = nScreenWidth; coaard.Y = nScreenHeight;
	SMALL_RECT rect; rect.Top = 0; rect.Left = 0; rect.Bottom = nScreenHeight - 1; rect.Right = nScreenWidth - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
	SetConsoleScreenBufferSize(hConsole, coaard);


	CONSOLE_SCREEN_BUFFER_INFO bf;
	GetConsoleScreenBufferInfo(hConsole, &bf);


	// clearing screen // or filling array winth 'space'
	//for (int i = 0; i < nScreenWidth * nScreenHeight; i++) { screen[i] = L' '; }

	// main game loop
	while (true) {

		screen[nScreenWidth * nScreenHeight - 1] = L'E';
		screen[nScreenWidth-1] = L'W';
		screen[0] = L'S';

		// Presenting frame
		//screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		// cleaning screen
		for (int i = 0; i < nScreenWidth * nScreenHeight; i++) { screen[i] = L' '; }
	}

	//system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
