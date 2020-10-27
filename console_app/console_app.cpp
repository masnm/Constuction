#include "main_engine.h"

class snake : public asn::asn_console_engine
{
public:
	std::string app_name() override
	{
		std::string name = "Snake Game";
		return name;
	}

	bool update_loop(float elapsed_time) override
	{
		clear();
		wchar_t c = L'A';
		for (int i = 0; i < width ; i++) {
			screen[i] = c;
		}
		return true;
	}
};

int main()
{
	snake game;
	if (game.create_console(128,128,8,8)) {
		game.start();
	}

	return 0;
}