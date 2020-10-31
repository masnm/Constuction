
#include "picture_engine.h"

class my_window : public picture_engine
{
public:

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
	my_window mw;
	mw.construct(1366, 768, 1, 1);
	mw.start();

	return 0;
}