#include <ncurses.h>
#include "guessgame-messages.h"
#include "guessgame-functions.h"
#include "string.h"

WINDOW *WindowCreatTitle();
WINDOW *WindowCreatStatus(int run_prevstatus);
WINDOW *WindowCreatMenu();

int WindowCreatHome(int run_prevstatus){
	// printf("we have %d",run_prevstatus);
	// getchar();

	initscr();

	WindowCreatTitle();						//Creat and show title.
	if (run_prevstatus != 3)				//Only if a game run,
		WindowCreatStatus(run_prevstatus);	//then creat and show "status".
	WINDOW *win_Menu	= WindowCreatMenu();//Creat and show "menu".

	int win_menu_select= 2;
	int win_menu_act;//action done on menu

	while ((win_menu_act = wgetch(win_Menu)) != 'q'){
		switch (win_menu_act) {
			case KEY_UP:
				mvwprintw(win_Menu, win_menu_select, 2, " ");
				if(win_menu_select == 2 && (win_menu_select = 6))
					mvwprintw(win_Menu, win_menu_select, 2, ">");
				else
					mvwprintw(win_Menu, (win_menu_select-=2), 2, ">");
				break;

			case KEY_DOWN:
				mvwprintw(win_Menu, win_menu_select, 2, " ");
				if(win_menu_select == 6 && (win_menu_select = 2))
					mvwprintw(win_Menu, win_menu_select, 2, ">");
				else
					mvwprintw(win_Menu, (win_menu_select+=2), 2, ">");
				break;

			case '\n':
				switch (win_menu_select){
					case 2:
						endwin();
						return (RunStart());
					case 4:
						mvwprintw(win_Menu,4,12,"[W I P]");
						break;
					case 6:
						mvwprintw(win_Menu,6,2,"exit");
						return (3);
				}
		}
		//win and lose menu execution?
		// BufferClear();
	}
	endwin();
	return 3;
}

WINDOW *WindowCreatTitle(){
	int win_title_posx = (getmaxx(stdscr)-25)/2;

	WINDOW *win_Title	= newwin(3, 25, 2, win_title_posx);
	box(win_Title,0,0);
	mvwprintw(win_Title,1, 0, M_TITLE);
	wrefresh(win_Title);
	return (win_Title);
}

WINDOW *WindowCreatStatus(int run_prevstatus){
	char status[6];

	if(run_prevstatus == 1)
		strcpy(status,"gg");
	else if(run_prevstatus == 0)
		strcpy(status,"L hh");
	else
		return(0);
	status[5] = 0;

	int win_Status_posx = (getmaxx(stdscr)-25)/2;

	WINDOW *win_Status	= newwin(3, 25, 7, win_Status_posx);
	box(win_Status,0,0);
	mvwprintw(win_Status,1, 3, "%s",status);
	wrefresh(win_Status);
	return (win_Status);
}

WINDOW *WindowCreatMenu(){
	int win_menu_posx = (getmaxx(stdscr)-20)/2;
	WINDOW *win_Menu	= newwin(9, 20, 10, win_menu_posx);
	box(win_Menu,0,0);

	mvwprintw(win_Menu,	2, 3 , M_MENU_OPT_1);
	mvwprintw(win_Menu,	4, 3, M_MENU_OPT_2);
	mvwprintw(win_Menu,	6, 3, M_MENU_OPT_3);
	mvwprintw(win_Menu,	2, 2, ">");

	noecho();
	keypad(win_Menu, TRUE);//for arrows ig

	return (win_Menu);
}

