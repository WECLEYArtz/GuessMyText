CC:=			cc
CFLAG:=			-Wall -Werror -Wextra
build_dir:=		build/
build_name:=	game
sufix:=			-lncurses

all:	dir guessgame-windows-tui.c ../guessgame-functions.h guessgame-functions-tui.c guessgame-main-tui.c
	$(CC) -o $(build_dir)$(build_name) $(CFLAG) \
	guessgame-windows-tui.c \
	guessgame-functions-tui.c \
	guessgame-main-tui.c \
	$(sufix)

dball: dir
	$(CC) -o $(build_dir)$(build_name) $(CFLAG) \
	guessgame-windows-tui.c \
	guessgame-functions-tui.c \
	guessgame-main-tui.c -g $(sufix)
	gdb ./$(build_dir)$(build_name)

tall: all dir
	./$(build_dir)$(build_name)

dir:
	if [ ! -d ./build ];then mkdir build;fi
