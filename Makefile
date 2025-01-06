CC:=			cc
CFLAG:=			-Wall -Werror -Wextra
build_dir:=		build/
build_name:=	game

all:	dir guessgame-functions.h guessgame-functions.c guessgame-main.c
	$(CC) -o $(build_dir)$(build_name) $(CFLAG) guessgame-functions.c guessgame-main.c 

dball: dir
	$(CC) -o $(build_dir)$(build_name) $(CFLAG) guessgame-functions.c guessgame-main.c -g
	gdb ./$(build_dir)$(build_name)

tall: all dir
	./$(build_dir)$(build_name)

dir:
	if [ ! -d ./build ];then mkdir build;fi
