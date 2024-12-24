#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "ANSI-escapes.h"
#include "guessgame-functions.h"
#include "guessgame-messages.h"

void start_guess(char *wrd_goal, wrd_struct wrd_clone, int *lives, int *bingos){
	char answer_input; //store guessed letter

	printf("try:");

	//as long as there are plays retries , get a pending character
	while((answer_input = fgetc(stdin)) != '\n' && *lives != 0 && *bingos != 0){
		bool correct = false; //exists or not

		//if the pending character didnt meet the requirments, redo the while
		if( !(isdigit(answer_input) || isalpha(answer_input) ||answer_input ==' ') )
			continue;

		//checks if the taken character exists in wrd_uniq
		//if yes, update values and expose it in wrd_hidden
		//if no, lose the try
		for(int i = 0; wrd_clone.uniq[i]; i++){
			if( wrd_clone.uniq[i] == answer_input){
				correct = true; (*bingos)--;

				wrd_clone.uniq[i] *= -1;
				mark_char(wrd_goal, &wrd_clone, answer_input);

				printf(M_CRCT,answer_input, wrd_clone.hidden);
				break;
			}
		}
		if( !correct )
		{
			(*lives)--;
			printf(M_WRNG ,answer_input, *lives);
		}
	}
}

int main(){
	char wrd_goal[64];//carries the full name

	//get the goal text
	printf(CLR_DISP RST_CUR "enter a string: ");
	getstr_input(wrd_goal);//"aabcccdeee

	//prepare these strings
	wrd_struct wrd_clone = {
		wrd_clone.uniq	= getuniq(wrd_goal),//	"aabcccdeee" >> "abcde"
		wrd_clone.hidden= (char *)malloc((strlen(wrd_goal)*sizeof(char))),//"----------"
		wrd_clone.marked= (char *)malloc((strlen(wrd_goal)*sizeof(char)))//	"aabcccdeee" >> "...b...deee"
	};
	strcpy(wrd_clone.marked, wrd_goal);

	int bingos = strlen(wrd_clone.uniq);// how many correct wrds to guess and win
	int lives = 10;// tries

	int i= (int)strlen(wrd_goal);//bad fix, find root issue
	wrd_clone.hidden[i--] = 0;
	for(; i >= 0; i--) // create the "-----"
		wrd_clone.hidden[i] = '-';


//======[	begin	]=======
	printf(M_GUESS, wrd_clone.hidden,(int)strlen(wrd_clone.hidden));
	while(lives != 0 && bingos != 0)//self explainatory ngl
		start_guess(wrd_goal, wrd_clone, &lives, &bingos);
//======[	 end	]=======
	if (bingos == 0)
		printf("%s\n",M_RUNWON);
	else
	{
		printf("\n"M_RUNLOS, wrd_goal);
		printf("                   "YEL_B" ");
		for(int i=0; wrd_clone.marked[i]!=0; i++)
			if(wrd_clone.marked[i] > 0)
				printf(RED_B BLK" ");
			else
				printf(GRN_B BLK" ");
		printf(YEL_B" \n"RESET);
	}
	free(wrd_clone.uniq);
	return 0;
}
