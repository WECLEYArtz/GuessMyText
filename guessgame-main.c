#include <stdio.h>
#include <string.h>
#include "guessgame_functions.h"

int main(){
	char word_result[124];//carries the full name "abdsamad"
	printf("\033[2J\033[H");
	printf("enter a string: ");
	// clear_buffer();
	fgets(word_result, 100, stdin);// get input to word_result
	printf("\033[2J\033[H");
	word_result[strcspn(word_result, "\n")] = 0;// no tailing "\n"

	// printf("result: '%s'\n", word_result);

	char *word_uniq = getuniq(word_result);//unique chars from input "abdsm"
	char word_hidden[strlen(word_result)];// the "-----"

	int i= 0;//bad fix, find root issue
	for(; i < (int)strlen(word_result); i++) // create the "-----"
		word_hidden[i] = '-';
	word_hidden[i] = 0;
	// used to be
	// for(int i= 0; i < (int)strlen(word_result); i++) // create the "-----"
	// 	word_hidden[i] = '-';

	int bingos = strlen(word_uniq);// how many correct words to guess and win
	int lives = 10;// tries

	printf("Guess the word in, \"%s\", [%d]\n\n", word_hidden,(int)strlen(word_hidden));
//======[	begin	]=======
	while(lives != 0 && bingos != 0){
		start_guess(word_result, word_uniq, word_hidden, &lives, &bingos);
	}

//======[	 end	]=======
	if (bingos == 0)
		puts("\x1b[92m<<< GG >>>\x1b[37m\n");
	else
		puts("\x1b[31m<<< defeat hh >>>\x1b[37m");
	return 0;
}
