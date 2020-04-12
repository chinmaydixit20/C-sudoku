
WARN = -Wall

GTKLIB = `pkg-config --cflags --libs gtk+-3.0`



all: sudoku

sudoku: main.o generate.o sudoku.o save.o resume.o solve.o hint.o
	gcc -o sudoku main.o generate.o sudoku.o save.o resume.o solve.o hint.o $(GTKLIB)

main.o: main.c sudoku.h
	gcc -c main.c $(GTKLIB)

sudoku.o: sudoku.c sudoku.h
	gcc -c sudoku.c

generate.o: generate.c sudoku.h
	gcc -c generate.c

save.o: save.c sudoku.h
	gcc -c save.c

resume.o: resume.c sudoku.h
	gcc -c resume.c	
	
solve.o: solve.c sudoku.h
	gcc -c solve.c	
	
hint.o: hint.c sudoku.h
	gcc -c hint.c				

.PHONY: clean

clean:
	rm -f *.o sudoku
