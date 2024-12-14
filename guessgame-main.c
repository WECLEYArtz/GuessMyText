#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guessgame-functions.h"
#include "guessgame-messages.h"

int main(){
	char word_result[124];//carries the full name "abdsamad"
	printf(CLR_DISP RST_CUR "enter a string: ");
	fgets(word_result, 100, stdin);// get input to word_result
	printf(CLR_DISP RST_CUR);
	word_result[strcspn(word_result, "\n")] = 0;// no tailing "\n"

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

	printf(M_GUESS, word_hidden,(int)strlen(word_hidden));
//======[	begin	]=======
	while(lives != 0 && bingos != 0){
		start_guess(word_result, word_uniq, word_hidden, &lives, &bingos);
	}

//======[	 end	]=======
	if (bingos == 0)
		printf("%s\n",M_RUNWON);
	else
		printf("%s\n",M_RUNLOS);
	free(word_uniq);
	return 0;
}
