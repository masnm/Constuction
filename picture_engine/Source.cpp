
#include "picture_engine.h"

#include <stack>
#include <vector>

class my_game : public picture_engine
{
private:
	int  m_nMazeWidth;
	int  m_nMazeHeight;
	int* m_maze;


	// Some bit fields for convenience
	enum
	{
		CELL_PATH_N = 0x01,
		CELL_PATH_E = 0x02,
		CELL_PATH_S = 0x04,
		CELL_PATH_W = 0x08,
		CELL_VISITED = 0x10,
	};


	// Algorithm variables
	int  m_nVisitedCells;
	std::stack<std::pair<int, int>> m_stack;	// (x, y) coordinate pairs
	int  m_nPathWidth;

	// Inherited via picture_engine
	virtual bool onCreate() override
	{
		m_nMazeWidth = 40;
		m_nMazeHeight = 25;
		m_maze = new int[m_nMazeWidth * m_nMazeHeight];
		memset(m_maze, 0x00, m_nMazeWidth * m_nMazeHeight * sizeof(int));
		m_nPathWidth = 3;

		// Choose a starting cell
		int x = rand() % m_nMazeWidth;
		int y = rand() % m_nMazeHeight;
		m_stack.push(std::make_pair(x, y));
		m_maze[y * m_nMazeWidth + x] = CELL_VISITED;
		m_nVisitedCells = 1;

		return true;
	}
	virtual bool onUpdate() override
	{
		// Little lambda function to calculate index in a readable way
		auto offset = [&](int x, int y)
		{
			return (m_stack.top().second + y) * m_nMazeWidth + (m_stack.top().first + x);
		};

		// Do Maze Algorithm
		if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight)
		{
			// Create a set of unvisted neighbours
			std::vector<int> neighbours;

			// North neighbour
			if (m_stack.top().second > 0 && (m_maze[offset(0, -1)] & CELL_VISITED) == 0)
				neighbours.push_back(0);
			// East neighbour
			if (m_stack.top().first < m_nMazeWidth - 1 && (m_maze[offset(1, 0)] & CELL_VISITED) == 0)
				neighbours.push_back(1);
			// South neighbour
			if (m_stack.top().second < m_nMazeHeight - 1 && (m_maze[offset(0, 1)] & CELL_VISITED) == 0)
				neighbours.push_back(2);
			// West neighbour
			if (m_stack.top().first > 0 && (m_maze[offset(-1, 0)] & CELL_VISITED) == 0)
				neighbours.push_back(3);

			// Are there any neighbours available?
			if (!neighbours.empty())
			{
				// Choose one available neighbour at random
				int next_cell_dir = neighbours[rand() % neighbours.size()];

				// Create a path between the neighbour and the current cell
				switch (next_cell_dir)
				{
				case 0: // North
					m_maze[offset(0, -1)] |= CELL_VISITED | CELL_PATH_S;
					m_maze[offset(0, 0)] |= CELL_PATH_N;
					m_stack.push(std::make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));
					break;

				case 1: // East
					m_maze[offset(+1, 0)] |= CELL_VISITED | CELL_PATH_W;
					m_maze[offset(0, 0)] |= CELL_PATH_E;
					m_stack.push(std::make_pair((m_stack.top().first + 1), (m_stack.top().second + 0)));
					break;

				case 2: // South
					m_maze[offset(0, +1)] |= CELL_VISITED | CELL_PATH_N;
					m_maze[offset(0, 0)] |= CELL_PATH_S;
					m_stack.push(std::make_pair((m_stack.top().first + 0), (m_stack.top().second + 1)));
					break;

				case 3: // West
					m_maze[offset(-1, 0)] |= CELL_VISITED | CELL_PATH_E;
					m_maze[offset(0, 0)] |= CELL_PATH_W;
					m_stack.push(std::make_pair((m_stack.top().first - 1), (m_stack.top().second + 0)));
					break;

				}

				m_nVisitedCells++;
			}
			else
			{
				// No available neighbours so backtrack!
				m_stack.pop();
			}
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(500));

		int x = m_stack.top().first, y = m_stack.top().second;
		// draw calls
		clear({ 0,0,0,255 });
		for (int i = 0; i < m_nMazeWidth; i++) {
			for (int j = 0; j < m_nMazeHeight; j++) {
				for (int py = 0; py < m_nPathWidth; py++) {
					for (int px = 0; px < m_nPathWidth; px++) {
						if (m_maze[j * m_nMazeWidth + i] & CELL_VISITED)
							draw(1+i * (m_nPathWidth + 1) + px, 1+j * (m_nPathWidth + 1) + py, 255, 255, 255, 255);
						else
							draw(1 + i * (m_nPathWidth + 1) + px, 1 + j * (m_nPathWidth + 1) + py, 0, 0, 0, 255);
						if ( i==x && j==y)
							draw(1 + i * (m_nPathWidth + 1) + px, 1 + j * (m_nPathWidth + 1) + py, 255, 0, 0, 255);
					}
				}
				for (int p = 0; p < m_nPathWidth; p++) {
					if (m_maze[j * m_nMazeWidth + i] & CELL_PATH_S) {
						draw(1 + i * (m_nPathWidth + 1) + p, 1 + j * (m_nPathWidth + 1) + m_nPathWidth, 255, 255, 255, 255);
					}
					if (m_maze[j * m_nMazeWidth + i] & CELL_PATH_E) {
						draw(1 + i * (m_nPathWidth + 1) + m_nPathWidth, 1 + j * (m_nPathWidth + 1) + p, 255, 255, 255, 255);
					}
				}
			}
		}

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
	game.construct(161,101,8,8);
	game.start();

	return 0;
}