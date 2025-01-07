
#ifndef GUESSGAME_MESSAGES_H
#define GUESSGAME_MESSAGES_H
#include "ANSI-escapes.h"
	#define M_GUESS "Guess the word in, \"%s\", [%d]\n"

	#define M_CRCT GRN "\x1b[32m\"%c\" exists!\x1b[37m     \"%s\"\n" RESET
	#define M_WRNG YEL "No '%c' [%d tries left].\n" RESET

	#define M_RUNWON BOLD BLK GRN_B " <<< GG >>> " RESET
	#define M_RUNLOS BOLD BLK RED_B " <<< defeat hh >>> " YEL_B " %s \n" RESET

	#define M_RETRY_OPT1 BLK " " MAG_B" new run   (enter) \n" RESET
	#define M_RETRY_OPT2 BLK " " MAG_B" setting   (s)     \n" RESET
	#define M_RETRY_OPT3 BLK " " MAG_B" quit      (q)     \n" RESET

	#define M_RETRY BLK WHT_B "    Guess My Text    \n" RESET\
			M_RETRY_OPT1 M_RETRY_OPT2 M_RETRY_OPT3

#endif
