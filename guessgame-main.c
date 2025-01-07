#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "ANSI-escapes.h"
#include "guessgame-functions.h"
#include "guessgame-messages.h"

void start_run();
int main(){
	//optons
		printf(CLR_DISP RST_CUR);
	while (true){
		printf("[[[	GUESS MY TEXT ]]\n\n");
		printf("(1) start:\n(2) mod:\n(3) quit:\n");

		char opt = fgetc(stdin);
		switch (opt) {
			case '1':
				getchar();
				start_run();
				break;
			case '2':
				printf(CLR_DISP RST_CUR"coming soon...\n");
				break;
			case '3':
				exit(0);
			default :
				printf(CLR_DISP RST_CUR"invalid option\n");
		}
		clear_buffer();
	}
	return 0;
}

void start_run(){
	//======[	INITIALIZE	MAIN	STRING	]=======
	char wrd_goal[64];//carries the full name
	int bingos;	//how many character to find
	int tries;	//how many times submissions allowed

	printf(CLR_DISP RST_CUR "Enter your text: ");
	getstr_input(wrd_goal);// get the text under conditions

	wrd_struct wrd_clone;//to assist marks for the progress
	wrd_clone.uniq	= getuniq(wrd_goal);
	//	"aabcccdeee" >> "abcde"
	wrd_clone.hidden= (char *)malloc((strlen(wrd_goal)*sizeof(char)));
	// "----------"
	wrd_clone.marked= (char *)malloc((strlen(wrd_goal)*sizeof(char)));
	//	"aabcccdeee" >> "...b...deee"

	strcpy(wrd_clone.marked, wrd_goal);

	bingos = strlen(wrd_clone.uniq);// how many correct wrds to guess and win
	tries = 10;// tries

	int i= (int)strlen(wrd_goal);// fill it to "-----", it just works
	wrd_clone.hidden[i--] = 0;
	for(; i >= 0; i--) // fill it to "-----"
		wrd_clone.hidden[i] = '-';

	printf(M_GUESS, wrd_clone.hidden,(int)strlen(wrd_clone.hidden));

	//======[	PROCESS		THE		RUN	]=======
	while(tries != 0 && bingos != 0)//self explainatory ngl
	{
		char answer_input; //store guessed letters

		printf("try	>");

		//as long as there are plays retries , get a pending character
		while((answer_input = fgetc(stdin)) != '\n' && tries != 0 && bingos != 0){

			//if the pending character didnt meet the requirments, redo the while
			if( !(isdigit(answer_input)
				||isalpha(answer_input)
				||answer_input ==' ')
				)
				continue;

			if( check_guess(wrd_goal, &wrd_clone, answer_input) )//returns boolean
			{
				(bingos)--;
				printf(M_CRCT,answer_input, wrd_clone.hidden);
			}
			else
			{
				(tries)--;
				printf(M_WRNG ,answer_input, tries);
			}
		}
	}


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
	free(wrd_clone.hidden);
	free(wrd_clone.marked);
	clear_buffer();

	printf(M_RETRY);
	char action = getchar();
		switch (action) {
			case '\n':
				start_run();
				break;
			case 'q':
				printf("Quit\n");
				exit(0);
			default :
				printf(CLR_DISP RST_CUR);
				return;
		}
}
