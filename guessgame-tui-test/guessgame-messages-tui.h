
#ifndef GUESSGAME_MESSAGES_H
#define GUESSGAME_MESSAGES_H
#include "../ANSI-escapes.h"
	#define M_GUESS "Guess the word in, \"%s\", [%d]\n"

	#define M_CRCT GRN "\x1b[32m\"%c\" exists!\x1b[37m     \"%s\"\n" RESET
	#define M_WRNG YEL "No '%c' [%d tries left].\n" RESET

	#define M_RUNWON BOLD BLK GRN_B " <<< GG >>> " RESET
	#define M_RUNLOS BOLD BLK RED_B " <<< defeat hh >>> " YEL_B " %s \n" RESET


	#define M_TITLE	"G U E S S   M Y   T E X T"

	#define M_MENU_OPT_1	" New run"
	#define M_MENU_OPT_2	" Setting"
	#define M_MENU_OPT_3	" Quit"

#endif
