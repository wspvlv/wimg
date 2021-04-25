INP = src/main.c
OBJ = bin/wimg
OBJ_REL = release/wimg
INC = -I/home/wispy/prj/wlib/inc
WARN = -Wall -Wextra -Wpedantic
LIB_REL = -L./release/lib/wc -L./release/lib -lSDL2 -lSDL2_image -lz -l:io.l -l:types/char.l -l:types/array.l -l:types/int.l -l:math/mathi.l
LIB = -L/home/wispy/prj/wlib/lib/wc -lSDL2 -lSDL2_image -lz -l:io.l -l:types/char.l -l:types/array.l -l:types/int.l -l:math/mathi.l
unix:
	gcc $(INP) -o $(OBJ) $(INC) $(WARN) $(LIB)
wos :
	gcc $(INP) -o $(OBJ).x $(INC) $(WARN) $(LIB)
unix_release:
	gcc $(INP) -o $(OBJ_REL) $(INC) $(WARN) $(LIB_REL)