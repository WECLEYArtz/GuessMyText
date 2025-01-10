CC:=			cc
CFLAG:=			-Wall -Werror -Wextra
build_dir:=		build/
build_name:=	game
sufix:=			-lncurses

all:	dir guessgame-windows.c guessgame-functions.h guessgame-functions.c guessgame-main.c
	$(CC) -o $(build_dir)$(build_name) $(CFLAG) \
	guessgame-windows.c \
	guessgame-functions.c \
	guessgame-main.c \
	$(sufix)

dball: dir
	$(CC) -o $(build_dir)$(build_name) $(CFLAG) \
	guessgame-windows-.c \
	guessgame-functions-.c \
	guessgame-main-.c -g $(sufix)
	gdb ./$(build_dir)$(build_name)

tall: all dir
	./$(build_dir)$(build_name)

dir:
	if [ ! -d ./build ];then mkdir build;fi
