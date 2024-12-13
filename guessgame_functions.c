
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "guessgame_functions.h"

char *getuniq(char *word_result){
	int word_result_size = strlen(word_result);

	//to stores the chars as it seeks them from result str
	char *word_uniq_buffer = malloc(word_result_size *sizeof(char));

	//store a new character from result str
	//then strcopy to buffer to a new smaller string size

	for(int p=0, u=0, n=0; p < word_result_size; p++)
	{
		for(; word_uniq_buffer[n] ; n++)
			if (word_result[p] == word_uniq_buffer[n])
				{n=0; break; }
		if(n == (int)strlen(word_uniq_buffer))
		{
			word_uniq_buffer[u++] = word_result[p];
			n=0;
		}
	}
	char *ptr = malloc(strlen(word_uniq_buffer) *sizeof(char));
	strcpy (ptr, word_uniq_buffer);
	free(word_uniq_buffer);
	return ptr;
}

void exposeword(char *word_result, char *word_hidden, char answer_input)
{
	for(int i = 0; word_result[i]; i++)
		if( word_result[i] == answer_input )
			word_hidden[i] = word_result[i];
}

void start_guess(char *word_result, char *word_uniq, char *word_hidden,
				int *lives, int *bingos){
	char answer_input; //store guessed letter

	printf("try:");

	while((answer_input = fgetc(stdin)) != '\n'){
		//  add returning terminal cursor to position!
		int correct = 0; //exists or not
		if( !(isdigit(answer_input) || isalpha(answer_input) ||answer_input ==' ') )
			continue;
		//checks if the taken character exists, and expose it in word_hidden
		//
		for(int i = 0; word_uniq[i]; i++){
			if( word_uniq[i] == answer_input){

				correct = 1;
				(*bingos)--;

				word_uniq[i] = '\200';
				exposeword(word_result, word_hidden, answer_input);
				printf("\x1b[32m\"%c\" exists!\x1b[37m     \"%s\"\n",
						answer_input, word_hidden);
				break;
			}
		}
		if( correct == 0)
		{
			(*lives)--;
			printf("\x1b[33mNo '%c' [%d tries left].\x1b[37m\n",answer_input, *lives);
			//\"%c\" exists!\x1b[37m
		}
	}
}
