
#ifndef GUESSGAME_MESSAGES_H
#define GUESSGAME_MESSAGES_H
#include "ANSI-escapes.h"
	#define M_GUESS "Guess the word in, \"%s\", [%d]\n"

	#define M_CRCT GRN "\x1b[32m\"%c\" exists!\x1b[37m     \"%s\"\n" RESET
	#define M_WRNG YEL "No '%c' [%d tries left].\n" RESET

	#define M_RUNWON BOLD BLK GRN_B " <<< GG >>> " RESET
	#define M_RUNLOS BOLD BLK RED_B " <<< defeat hh >>> " YEL_B " %s \n" RESET

	#define M_RETRY_OPT1 BLK WHT_B " " MAG_B" (enter)	new run\n" 
	#define M_RETRY_OPT2 BLK WHT_B " " MAG_B" (q)		quit\n"
	#define M_RETRY_OPT3 BLK WHT_B " " MAG_B" (else)	home menu\n"
	#define M_RETRY		BLK WHT_B			" retry?      			\n"\
			M_RETRY_OPT1 M_RETRY_OPT2 M_RETRY_OPT3\
			RESET		BLK WHT_B			"             " RESET 
#endif
