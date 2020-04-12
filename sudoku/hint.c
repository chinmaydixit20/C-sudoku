#include "sudoku.h"
/* getHint() will change a location to an integer value corresponding to any random location in the puzzle array
   -> will do so by generating a set of two random numbers, i and j
   -> will check puzzle[i][j], and if the value is 0, then will fetch the solution value and change the same
   -> the function will not be called if the puzzle has already been filled
   -> limited number of hints
*/

void getHint(int **puzzle) {
	srand(time(0));
	int i, j;
	while(1) {
		i = (rand() % N);
		j = (rand() % N);
		if(puzzle[i][j] == 0) {
			puzzle[i][j] = sol[i][j];
			break;
		}	
	}
	printf("Hint: Row %d Column %d Value %d\n", i, j, sol[i][j]);
}			
			
