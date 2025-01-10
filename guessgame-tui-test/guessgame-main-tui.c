#include <ncurses.h>
#include "guessgame-windows-tui.h"

int main(){
	int run_prevstatus = 3;
	while (true){
		run_prevstatus = WindowCreatHome(run_prevstatus);
		if (run_prevstatus == 3)//if exited from "menu"
			break;
	}
	endwin();
	return 0;
}

