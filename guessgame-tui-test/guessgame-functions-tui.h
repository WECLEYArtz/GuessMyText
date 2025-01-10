#ifndef GUESSGAME_FUNCTIONS_H
#define GUESSGAME_FUNCTIONS_H
	typedef struct {
		char *uniq; 
		char *hidden;
		char *marked;
	}Work_Clones;

	int RunStart(); //start proccesing the game

	char *GetUniqChars(char *string);

	void GetStrInput(char *str);

	void BufferClear();
	void BufferDump();//will be added for dubug

	// checking methods
	bool VerifyGuess(char *str_exposed, Work_Clones *str_target, char keychar);

#endif
