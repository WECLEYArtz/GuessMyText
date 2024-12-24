#ifndef GUESSGAME_FUNCTIONS_H
#define GUESSGAME_FUNCTIONS_H
	typedef struct {
		char *uniq; 
		char *hidden;
		char *marked;
	}wrd_struct;

	char *getuniq(char *string);

	void getstr_input(char *str);

	void mark_char(char *str_exposed, wrd_struct *str_target, char keychar);

	void start_guess(char *wrd_goal, wrd_struct wrd_clone, int *lives, int *bingos);

#endif
