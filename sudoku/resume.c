#include "sudoku.h"
/*
  -> reads from a text file containing charcters using read() function
  -> saves the values in the puzzle array which in turn changes the value of the 2d array in the main function
*/
void resume(int **puzzle, char *filename) {
	int i = 0, j = 0, fd, val;
	char ch;
	fd = open(filename, O_RDONLY);
	if(fd == -1) {
		printf("Save state does not exist!\n");
		return;
	}

	while(read(fd, &ch, sizeof(char)) && i < N && j < N) {
		if(ch != '\n' && ch != ' ') {
			if(j == N - 1) {
				i++;
				j = 0;
			}
			else {
				val = ch - '0';
				puzzle[i][j] = val;
				j++;
			}
		}	
	}							
	close(fd);
}				
