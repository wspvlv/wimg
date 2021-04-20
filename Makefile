INP = src/main.c
OBJ = bin/wimg.x
INC = -I/home/wispy/prj/wlib/inc
WARN = -Wall -Wextra -Wpedantic
LIB = -L/home/wispy/prj/wlib/lib/wc -l:io.l -l:types/char.l -lSDL2
all :
	gcc $(INP) -o $(OBJ) $(INC) $(WARN) $(LIB)