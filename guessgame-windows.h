#include <ncurses.h>
#ifndef GUESSGAME_WINDOWS_TUI_H
#define GUESSGAME_WINDOWS_TUI_H
	WINDOW *WindowCreatTitle();
	WINDOW *WindowCreatStatus(bool result);
	WINDOW *WindowCreatMenu();
	bool WindowCreatHome(int run_prevstatus);
#endif
