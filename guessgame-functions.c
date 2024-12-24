#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "guessgame-functions.h"
#include "ANSI-escapes.h"

void getstr_input(char *str){
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
	printf(CLR_DISP RST_CUR);// clear screen
	strcpy(str, buffer);
	return;
}

char *getuniq(char *string){
	size_t string_len = strlen(string);
	char *uniq_chars_buffer;

	while ( (uniq_chars_buffer = malloc(string_len *sizeof(char)))  == NULL );
	//to stores the chars seeked from goal string

	for(unsigned int p=0, u=0, n=0; p < string_len; p++) //loop over the goal string
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
	//use less memory
	char *ptr;
	while ( (ptr = malloc(strlen(uniq_chars_buffer) *sizeof(char))) == NULL );
	strcpy (ptr, uniq_chars_buffer);
	free(uniq_chars_buffer);

	return ptr;
}

void mark_char(char *wrd_exposed, wrd_struct *wrd_targets, char keychar)
{
	for(unsigned int i = 0; wrd_exposed[i]; i++)
		if( wrd_exposed[i] == keychar )
		{
			wrd_targets->hidden[i] = wrd_exposed[i];
			wrd_targets->marked[i] *= -1;
		}
}
