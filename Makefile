INP = src/main.c
OBJ = bin/wimg
INC = -I/home/wispy/prj/wlib/inc
WARN = -Wall -Wextra -Wpedantic
LIB = -L/home/wispy/prj/wlib/lib/wc -l:io.l -l:types/char.l -lSDL2
unix:
	gcc $(INP) -o $(OBJ) $(INC) $(WARN) $(LIB)
wos :
	gcc $(INP) -o $(OBJ).x $(INC) $(WARN) $(LIB)