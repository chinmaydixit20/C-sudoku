#include "sudoku.h"
//similar to solve, uses recursive backtracking algorithm to GENERATE a new puzzle

int solveForGenerate(int **puzzle) {
	/*int rowNo = 0, colNo = 0, num, i = 0;
	if(!findUnassignedLocation(puzzle, &rowNo, &colNo))
		return 1;
	int arr[N];
	while(i < N) {
		num = (rand() % N) + 1;
		if(!usedInArr(arr, num)) {
			arr[i] = num;
			i++;
		}	
	}			
	for(i = 0; i < N; i++) {
		num = arr[i];
		if(isSafe(puzzle, rowNo, colNo, num)) {
			puzzle[rowNo][colNo] = num;
			if(solveForGenerate(puzzle)) 
				return 1;		
			puzzle[rowNo][colNo] = UNASSIGNED;
		}
	}
	return 0;*/
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
//interprets the difficulty of the puzzle using globally declared enum			
int setDifficultyVal(int difficulty) {
	int randNum = rand() % 4;
	switch(difficulty) {
		case EASY:
			return (N * 4) + randNum;
		case MODERATE:
			return (N * 3) + randNum;
		case HARD:
			return (N * 2) + randNum;
	}
}					

int generateSudoku(int **puzzle, int difficulty) {
    	int i = 0, number, rI, rJ, val;
    	int rowIndex, colIndex;
    	val = setDifficultyVal(difficulty);
    	setSize();
    	if(!sol) {
		sol = (int **)malloc(sizeof(int *) * N);
		for(i = 0; i < N; i++)
			sol[i] = (int *)malloc(sizeof(int) * N);
	}
    	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			puzzle[i][j] = 0;
			sol[i][j] = 0;
		}
	}		
	printGrid(puzzle);		
    	srand(time(0));
    	i = 0;
	while(i < 23) {
		rI = rand() % N;
		rJ = rand() % N;
		number = (rand() % N) + 1;
		if(isSafe(puzzle, rI, rJ, number)) {
			puzzle[rI][rJ] = number;
			i++;
		}
	}
	printGrid(puzzle);							 
	if(solveForGenerate(puzzle)) {		 
		copySol(sol, puzzle);	
		printGrid(sol);
		i = 0; 
		while(i < (N * N) - val) {
			rowIndex = rand() % N;
			colIndex = rand() % N;
			if(puzzle[rowIndex][colIndex]) {
				puzzle[rowIndex][colIndex] = 0;
				i++;
			}
		}
		return 1;		
	}	
	else
		return 0;
} 				       						
