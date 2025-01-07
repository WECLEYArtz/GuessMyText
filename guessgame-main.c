#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "ANSI-escapes.h"
#include "guessgame-functions.h"
#include "guessgame-messages.h"

void RunStart();
int main(){
	//optons
	printf(CLR_DISP RST_CUR);
	while (true){
		printf(M_RETRY);
		char opt = getchar();
		switch (opt) {
			case '\n':
				printf(SHW_CUR);
				RunStart();
				break;
			case 'm':
				printf(CLR_DISP RST_CUR"coming soon...\n");
				break;
			case 'q':
				exit(0);
			default :
				printf(CLR_DISP RST_CUR"invalid option\n");
		}
		// BufferClear();
	}
	return 0;
}

void RunStart(){
	//======[	INITIALIZE	MAIN	STRING	]=======
	//goal_text gltxt
	char goal_text[64];//carries the full text
	int bingos;	//how many character to find
	int tries;	//how many times submissions allowed

	printf(CLR_DISP RST_CUR "Enter your text: ");
	GetStrInput(goal_text);// get the text under conditions

	Work_Clones Goal_Work_Clone;//to assist marks for the progress
	Goal_Work_Clone.uniq	= GetUniqChars(goal_text);
	//	"aabcccdeee" >> "abcde"
	Goal_Work_Clone.hidden= (char *)malloc((strlen(goal_text)*sizeof(char)));
	// "----------"
	Goal_Work_Clone.marked= (char *)malloc((strlen(goal_text)*sizeof(char)));
	//	"aabcccdeee" >> "...b...deee"

	strcpy(Goal_Work_Clone.marked, goal_text);

	bingos = strlen(Goal_Work_Clone.uniq);// how many correct wrds to guess and win
	tries = 10;// tries

	int i= (int)strlen(goal_text);// fill it to "-----", it just works
	Goal_Work_Clone.hidden[i--] = 0;
	for(; i >= 0; i--) // fill it to "-----"
		Goal_Work_Clone.hidden[i] = '-';

	printf(M_GUESS, Goal_Work_Clone.hidden,(int)strlen(Goal_Work_Clone.hidden));

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

			if( VerifyGuess(goal_text, &Goal_Work_Clone, answer_input) )//returns boolean
			{
				(bingos)--;
				printf(M_CRCT,answer_input, Goal_Work_Clone.hidden);
			}
			else
			{
				(tries)--;
				printf(M_WRNG ,answer_input, tries);
			}
		}
	}


	if (bingos == 0)
		printf(CLR_DISP RST_CUR "%s\n",M_RUNWON);
	else 
	{
		printf(CLR_DISP RST_CUR "\n"M_RUNLOS, goal_text);
		printf("                   "YEL_B" ");
		for(int i=0; Goal_Work_Clone.marked[i]!=0; i++)
			if(Goal_Work_Clone.marked[i] > 0)
				printf(RED_B BLK" ");
			else
				printf(GRN_B BLK" ");
		printf(YEL_B" \n\n"RESET);
	}
	free(Goal_Work_Clone.uniq);
	free(Goal_Work_Clone.hidden);
	free(Goal_Work_Clone.marked);
	BufferClear();
}
