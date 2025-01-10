#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>

#include "guessgame-functions-tui.h"
#include "guessgame-messages-tui.h"

#include "../ANSI-escapes.h"

void BufferClear(){
	char trash;
	while((trash = fgetc(stdin)) != '\n' && trash != EOF);
}

bool VerifyGuess(char *wrd_exposed, Work_Clones *Goal_Work_Clone, char answer_input)
{
	//checks if the taken character exists in wrd_uniq
	//if yes, update values and expose it in wrd_hidden
	//if no, lose the try
	for(int i = 0; Goal_Work_Clone->uniq[i]; i++){
		if( Goal_Work_Clone->uniq[i] == answer_input){

			Goal_Work_Clone->uniq[i] *= -1;//that one character it guessed
			for(unsigned int i = 0; wrd_exposed[i]; i++)
				if( wrd_exposed[i] == answer_input )
				{
					Goal_Work_Clone->hidden[i] = wrd_exposed[i];
					Goal_Work_Clone->marked[i] *= -1;
				}
			return true;
		}
	}
	return false;
}

void GetStrInput(char *str){ //responsible of getting a valid text
	char buffer[64];
	bool valid;

	do{
		valid = true;
		fgets(buffer, 64, stdin);
		buffer[strcspn(buffer, "\n")] = 0;// no tailing "\n"


		if (!buffer[0]){
			printf("nothing inputed, try again:");
			valid = false;
			continue;
		}

		for(int i= 0; buffer[i] != 0; i++)
		{
			if (!(isdigit(buffer[i]) || isalpha(buffer[i]) ||buffer[i] == ' '))
			{
				printf(" %c is invalid\nEnter a valid string:",buffer[i]);
				valid = false;
				break;
			}
		}
	}while(!valid);
	printf(CLR_DISP RST_CUR);	//clear screen
	strcpy(str, buffer);		//no memory traveling trought pointers till now
	return;
}

char *GetUniqChars(char *string){ //collect the unique characters in a string
	size_t string_len = strlen(string);
	char *uniq_chars_buffer;

	while ( (uniq_chars_buffer = malloc(string_len *sizeof(char)))  == NULL );
	//to stores the chars seeked from goal string

	int u=0;
	for(unsigned int p=0, n=0; p < string_len; p++) //loop over the goal string
	{
		for(; uniq_chars_buffer[n] ; n++) //compare every character in string with
										//ones in uniq_buffer, if exists, skip
										//if not. (reached end of uniq_buffer),
										//add the looked up character
										//uniq_chars_buffer[n] to uniq_buffer.
			if (string[p] == uniq_chars_buffer[n])
				{n=0; break; }
		if(n == (size_t)strlen(uniq_chars_buffer))
		{
			uniq_chars_buffer[u++] = string[p];
			n=0;
		}
	}
	uniq_chars_buffer[u] = 0;
	//use less memory
	char *ptr;
	while ( (ptr = malloc(strlen(uniq_chars_buffer) *sizeof(char))) == NULL );
	strcpy (ptr, uniq_chars_buffer);
	free(uniq_chars_buffer);

	return ptr;
}

int RunStart(){
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

	int run_prevstatus;
	if (bingos == 0)
		run_prevstatus = 1;
	else 
	{
		//crazy ass feature to be converted
		printf(CLR_DISP RST_CUR "\n"M_RUNLOS, goal_text);
		printf("                   "YEL_B" ");
		for(int i=0; Goal_Work_Clone.marked[i]!=0; i++)
			if(Goal_Work_Clone.marked[i] > 0)
				printf(RED_B BLK" ");
			else
				printf(GRN_B BLK" ");
		printf(YEL_B" \n\n"RESET);
		BufferClear();
		getchar();
		//crazy ass feature to be converted

		run_prevstatus = 0;
	}

	free(Goal_Work_Clone.uniq);
	free(Goal_Work_Clone.hidden);
	free(Goal_Work_Clone.marked);
	BufferClear();

	return (run_prevstatus);
}
