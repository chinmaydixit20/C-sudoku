#include "sudoku.h"
/*
  -> Recieves the puzzle through argument
  -> uses recursive backtracking algorithm to solve the puzzle
  -> if it cannot be solved, returns 0 which is appropriately interpreted in the main function
*/
int solveSudoku(int **puzzle) {
	int rowNo = 0, colNo = 0, num;
	if(!findUnassignedLocation(puzzle, &rowNo, &colNo))
		return 1;
	for(num = 1; num <= N; num++) {
		if(isSafe(puzzle, rowNo, colNo, num)) {
			puzzle[rowNo][colNo] = num;
			if(solveSudoku(puzzle))
				return 1;	
			puzzle[rowNo][colNo] = UNASSIGNED;
		}
	}
	return 0;
}
								
int solve(int **puzzle) { 
	setSize();   
	if(solveSudoku(puzzle)) {
		printGrid(puzzle);
		return 1;
	}	 
	else {
		printf("Invalid Puzzle!\n"); 
		return 0;
	}	 
} 
