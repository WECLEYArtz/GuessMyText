#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "guessgame-functions.h"
#include "guessgame-messages.h"

void start_guess(char *wrd_goal, char *wrd_uniq, char *wrd_hidden,
				int *lives, int *bingos){
	char answer_input; //store guessed letter

	printf("try:");

	//as long as there are plays retries , get a pending character
	while((answer_input = fgetc(stdin)) != '\n' && *lives != 0 && *bingos != 0){
		int correct = 0; //exists or not

		//if the pending character didnt meet the requirments, redo the while
		if( !(isdigit(answer_input) || isalpha(answer_input) ||answer_input ==' ') )
			continue;

		//checks if the taken character exists in wrd_uniq
		//if yes, update values and expose it in wrd_hidden
		//if no, lose the try
		for(int i = 0; wrd_uniq[i]; i++){
			if( wrd_uniq[i] == answer_input){

				correct = 1;
				(*bingos)--;

				wrd_uniq[i] = '\200';
				exposechar(wrd_goal, wrd_hidden, answer_input);
				printf(M_CRCT,answer_input, wrd_hidden);
				break;
			}
		}
		if( correct == 0)
		{
			(*lives)--;
			printf(M_WRNG ,answer_input, *lives);
		}
	}
}

int main(){
	char wrd_goal[64];//carries the full name


	//ask for and get the goal text
	printf(CLR_DISP RST_CUR "enter a string: ");
	fgets(wrd_goal, 64, stdin);
	printf(CLR_DISP RST_CUR);
	wrd_goal[strcspn(wrd_goal, "\n")] = 0;// no tailing "\n"

	//prepare these strings
	char *wrd_uniq = getuniq(wrd_goal);
	char wrd_hidden[strlen(wrd_goal)];// the "-----", am i better off mallocating?...

	int i= (int)strlen(wrd_goal);//bad fix, find root issue
	wrd_hidden[i--] = 0;
	for(; i >= 0; i--) // create the "-----"
		wrd_hidden[i] = '-';

	int bingos = strlen(wrd_uniq);// how many correct wrds to guess and win
	int lives = 10;// tries

//======[	begin	]=======
	printf(M_GUESS, wrd_hidden,(int)strlen(wrd_hidden));
	while(lives != 0 && bingos != 0)//self explainatory ngl
		start_guess(wrd_goal, wrd_uniq, wrd_hidden, &lives, &bingos);
//======[	 end	]=======
	if (bingos == 0)
		printf("%s\n",M_RUNWON);
	else
		printf("%s\n",M_RUNLOS);
	free(wrd_uniq);
	return 0;
}
