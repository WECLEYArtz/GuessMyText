CC:=			cc
CFLAG:=			-Wall -Werror -Wextra
build_dir:=		build/
build_name:=	game

all:	guessgame-functions.h guessgame-functions.c guessgame-main.c
	$(CC) -o $(build_dir)$(build_name) $(CFLAG) guessgame-functions.c guessgame-main.c 

gdball:
	$(CC) -o $(build_dir)$(build_name) $(CFLAG) guessgame-functions.c guessgame-main.c -g 
