all : Programme

Programme : programme.o fonction.o FoncCurse.o FcBasique.o
	gcc fonction.o programme.o FoncCurse.o FcBasique.o -o Programme -lm -lncurses
	make clean
programme.o : programme.c
	gcc -c programme.c -Wall -o programme.o -lm -lncurses

fonction.o : fonction.c fonction.h
	gcc -c fonction.c -Wall -o fonction.o -lm -lncurses

FoncCurse.o : FoncCurse.c
	gcc -c FoncCurse.c -Wall -o FoncCurse.o -lm -lncurses

FcBasique.o : FcBasique.c
	gcc -c FcBasique.c -Wall -o FcBasique.o -lm -lncurses

clean:
	rm -rf *.o
