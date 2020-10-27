#pragma once

// console_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include <Windows.h>


template<typename type>
struct i2d {
	type x;
	type y;
	i2d() : x(0), y(0) {}
	i2d(type _x, type _y) : x(_x), y(_y) {}
	i2d& operator = (const i2d& v) = default;
	//i2d& operator = (const i2d& right) { this->x = right.x; this->y = right.y; return *this; }
	i2d operator + (const i2d& right) const { return i2d(this->x + right.x, this->y + right.y); }
	i2d operator - (const i2d& right) const { return i2d(this->x - right.x, this->y - right.y); }
	i2d operator / (const int right) const { return i2d(this->x / right, this - y / right); }
	i2d& operator += (const i2d& right) { this->x += right.x; this->y += right.y; return *this; }
	bool operator == (const i2d& right) const { return (this->x == right.x && this->y == right.y); }
};
typedef i2d<int> int_2d;

int_2d screen_dimantion = { 60, 30 };
std::chrono::time_point<std::chrono::system_clock> tp1, tp2;
float elapsed_time;

void set_new_food(int_2d& food_pos, std::vector<int_2d>& snake)
{
	bool again = false;
	do {
		again = false;
		food_pos = { rand() % screen_dimantion.x, rand() % screen_dimantion.y };
		for (auto i : snake) {
			if (i == food_pos) again = true;
		}
	} while (again);
}

int detect_collition(int_2d& food_pos, std::vector<int_2d>& snake)
{
	for (auto i : snake)
		if (i == food_pos)
			return 1;
	int sz = snake.size();
	int_2d head = snake[sz - 1];
	for (int i = 0; i < sz - 2; i++) {
		if (snake[i] == head) return 2;
	}
	return 0;
}

int main()
{
	// Creating Screen Buffer
	wchar_t* screen = new wchar_t[screen_dimantion.x * screen_dimantion.y];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	COORD coaard; coaard.X = screen_dimantion.x; coaard.Y = screen_dimantion.y;
	SMALL_RECT rect; rect.Top = 0; rect.Left = 0; rect.Bottom = screen_dimantion.y - 1; rect.Right = screen_dimantion.x - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
	SetConsoleScreenBufferSize(hConsole, coaard);

	// staring from here
	std::vector<int_2d> snake;
	int_2d xone = { 1,0 }, yone = { 0,1 };
	snake.push_back({ screen_dimantion.x / 2, screen_dimantion.y / 2 });
	for (int i = 1; i < 6; i++) { snake.push_back(snake[i - 1] - xone); }

	int_2d food_pos;
	set_new_food(food_pos, snake);

	int left = 0, right = 2, up = 1, down = 3, dir = down, pdir = down;


	// main game loop
	bool end_game = false;
	while (!end_game) {

		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		elapsed_time = elapsedTime.count();

		//dir == left || dir == right ? std::this_thread::sleep_for(std::chrono::milliseconds(25)) : std::this_thread::sleep_for(std::chrono::milliseconds(50));

		if (GetAsyncKeyState(0x41) && pdir != left) { pdir = dir; dir = right; }	// A
		if (GetAsyncKeyState(0x44) && pdir != right) { pdir = dir; dir = left; }	// D
		if (GetAsyncKeyState(0x53) && pdir != up) { pdir = dir; dir = down; }		// S
		if (GetAsyncKeyState(0x57) && pdir != down) { pdir = dir; dir = up; }		// W

		if (dir == left) {
			snake.erase(snake.begin());
			snake.push_back(snake[snake.size() - 1] + xone);
			if (snake[snake.size() - 1].x >= screen_dimantion.x) snake[snake.size() - 1].x = 0;
		}
		else if (dir == right) {
			snake.erase(snake.begin());
			snake.push_back(snake[snake.size() - 1] - xone);
			if (snake[snake.size() - 1].x < 0) snake[snake.size() - 1].x = screen_dimantion.x - 1;
		}
		else if (dir == up) {
			snake.erase(snake.begin());
			snake.push_back(snake[snake.size() - 1] - yone);
			if (snake[snake.size() - 1].y < 0) snake[snake.size() - 1].y = screen_dimantion.y - 1;
		}
		else if (dir == down) {
			snake.erase(snake.begin());
			snake.push_back(snake[snake.size() - 1] + yone);
			if (snake[snake.size() - 1].y >= screen_dimantion.y) snake[snake.size() - 1].y = 0;
		}

		switch (detect_collition(food_pos, snake))
		{
		case 1:
			set_new_food(food_pos, snake); break;
		case 2:
			end_game = true; break;
		}

		// drawing snake
		for (auto i : snake) {
			screen[i.y * screen_dimantion.x + i.x] = 0x2588;
		}
		// drawing food
		screen[food_pos.y * screen_dimantion.x + food_pos.x] = 0x2588;

		// Presenting frame
		wchar_t s[256];
		swprintf_s(s, 256, L"%s - FPS: %3.2f", L"Snake ", 1.0f / elapsed_time);
		SetConsoleTitle(s);
		WriteConsoleOutputCharacter(hConsole, screen, screen_dimantion.x * screen_dimantion.y, { 0,0 }, &dwBytesWritten);

		// cleaning screen array
		for (int i = 0; i < screen_dimantion.x * screen_dimantion.y; i++) { screen[i] = L' '; }
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

