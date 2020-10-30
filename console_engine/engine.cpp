#include "engine.h"

engine::engine()
{
	m_nScreenWidth = 80;
	m_nScreenHeight = 30;

	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	m_sAppName = L"Default";
}

bool engine::construct(int sw, int sh, int fw, int fh)
{
	if (!name_app())
		return false;
	m_nScreenWidth = sw;
	m_nScreenHeight = sh;

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fw;
	cfi.dwFontSize.Y = fh;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");

	if (!SetCurrentConsoleFontEx(m_hConsole, false, &cfi))
		return false;

	COORD coordLargest = GetLargestConsoleWindowSize(m_hConsole);
	if (m_nScreenHeight > coordLargest.Y)
		return false;
	if (m_nScreenWidth > coordLargest.X)
		return false;

	COORD buffer = { (short)m_nScreenWidth, (short)m_nScreenHeight };
	if (!SetConsoleScreenBufferSize(m_hConsole, buffer))
		return false;

	small_rec.Top = 0;
	small_rec.Left = 0;
	small_rec.Bottom = (short)m_nScreenHeight - 1;
	small_rec.Right = (short)m_nScreenWidth - 1;
	//small_rec = { 0, 0, (short)m_nScreenWidth - 1, (short)m_nScreenHeight - 1 };
	if (!SetConsoleWindowInfo(m_hConsole, TRUE, &small_rec))
		return false;

	m_bufScreen = new CHAR_INFO[m_nScreenWidth * m_nScreenHeight];


	return true;
}

void engine::start()
{
	m_bAtomActive = true;

	thread t = thread(&engine::engine_thread, this);

	//m_cvGameFinished.wait(unique_lock<mutex> (m_muxGame));

	t.join();
}

void engine::engine_thread()
{
	if (!onCreate())
		return;

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	// Run as fast as possible
	while (m_bAtomActive)
	{
		// Handle Timing
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();


		// Handle Frame Update
		if (!onUpdate(fElapsedTime))
			m_bAtomActive = false;

		// Update Title & Present Screen Buffer
		wchar_t s[128];
		swprintf_s(s, 128, L"%s - FPS: %3.2f ", m_sAppName.c_str(), 1.0f / fElapsedTime);
		//swprintf_s(s, 128, L"%s", m_sAppName.c_str());
		SetConsoleTitle(s);
		WriteConsoleOutput(m_hConsole, m_bufScreen, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { 0,0 }, &small_rec);
	}

	if (!onDestroy())
		return;

	m_cvGameFinished.notify_one();
}

engine::~engine()
{
	SetConsoleActiveScreenBuffer(console_handle);
	delete[] m_bufScreen;
}

void engine::clip(int& x, int& y)
{
	if (x >= m_nScreenWidth) x = m_nScreenWidth - 1;
	if (x <= 0) x = 0;
	if (y >= m_nScreenHeight) y = m_nScreenHeight - 1;
	if (y <= 0) y = 0;
}

bool engine::clear(engine::colour col)
{
	CHAR_INFO c; c.Attributes = col;
	c.Char.UnicodeChar = solid;
	for (int i = 0; i < m_nScreenWidth * m_nScreenHeight; i++) {
		m_bufScreen[i] = c;
	}
	return true;
}


bool engine::draw(int x, int y, engine::colour col, pixel px)
{
	clip(x, y);
	m_bufScreen[y * m_nScreenWidth + x].Char.UnicodeChar = px;
	m_bufScreen[y * m_nScreenWidth + x].Attributes = col;
	return true;
}

bool engine::draw(i2d pos, engine::colour col, pixel px)
{
	return draw(pos.x, pos.y, col, px);
}

int engine::get_width()
{
	return m_nScreenWidth;
}

int engine::get_height()
{
	return m_nScreenHeight;
}
