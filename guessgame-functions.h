#ifndef GUESSGAME_FUNCTIONS_H
#define GUESSGAME_FUNCTIONS_H
	char *getuniq(char *word_result);
	void exposeword(char *word_result, char *word_hidden, char answer_input);
	void start_guess(char *word_result, char *word_uniq, char *word_hidden,
				int *lives, int *bingos);
#endif