#include "sudoku.h"
/*
  -> Saves the current state of the sudoku in a text file 
  -> will not work if the puzzle is empty
  -> stores the data without any newline chars and without any spaces
*/
void saveSudoku(int **puzzle, char *file_name) {
	int i, j, fd;
	char ch, nl = '\n';
	fd = open(file_name, O_RDWR | O_CREAT, S_IRWXU);//ability to store more than 1 file?? == done!
	if(fd == -1) {
		//printf("Error in opening file!\n");
		return;
	}	
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			ch = puzzle[i][j] + '0';
			write(fd, &ch, sizeof(char));
		}
		//write(fd, &nl, sizeof(char));
	}
	close(fd);
}			
			
