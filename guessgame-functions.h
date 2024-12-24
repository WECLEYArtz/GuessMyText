#ifndef GUESSGAME_FUNCTIONS_H
#define GUESSGAME_FUNCTIONS_H
	char *getuniq(char *string);
	void getstr_input(char *str);
	void exposechar(char *wrd_exposed, char *wrd_hidden, char keychar);
	void start_guess(char *wrd_goal, char *wrd_uniq, char *wrd_hidden,
				int *lives, int *bingos);
#endif
