#include "sudoku.h"
//finds unassigned or blank locations in the puzzle
int findUnassignedLocation(int **puzzle, int *rowNo, int *colNo) {
	for(*rowNo = 0; *rowNo < N; (*rowNo)++)
		for(*colNo = 0; *colNo < N; (*colNo)++) 
			if(!puzzle[*rowNo][*colNo])
				return 1;			
	return 0;
}
//checks existance in row
int usedInRow(int **puzzle, int rowNo, int num) {
	int colNo;
	for(colNo = 0; colNo < N; colNo++)
		if(puzzle[rowNo][colNo] == num)
			return 1;
	return 0;
}			 				
//checks existance in column
int usedInColumn(int **puzzle, int colNo, int num) {
	int rowNo;
	for(rowNo = 0; rowNo < N; rowNo++)
		if(puzzle[rowNo][colNo] == num)
			return 1;
	return 0;
}					
//checks existance in box
int usedInBox(int **puzzle, int boxStartRow, int boxStartColumn, int num) {
	int rowNo, colNo;
	for(rowNo = 0; rowNo < row; rowNo++)
		for(colNo = 0; colNo < col; colNo++)
			if(puzzle[rowNo + boxStartRow][colNo + boxStartColumn] == num)
				return 1;
	return 0;
}
//checks whether input value is feasible or not
int isSafe(int **puzzle, int rowNo, int colNo, int num) {
	return !usedInRow(puzzle, rowNo, num) && !usedInColumn(puzzle, colNo, num) && 
	       !usedInBox(puzzle, rowNo - (rowNo % row), colNo - (colNo % col), num) && puzzle[rowNo][colNo] == UNASSIGNED;
}
//additional function part of attempt to randomise values even further
int usedInArr(int *arr, int num) {
	int colNo;
	for(colNo = 0; colNo < N; colNo++)
		if(arr[colNo] == num)
			return 1;
	return 0;
}
//used for printing the puzzle in the shell
void printGrid(int **puzzle) 
{ 
    for (int rowP = 0; rowP < N; rowP++) 
    { 
       for (int colP = 0; colP < N; colP++) 
             printf("%2d", puzzle[rowP][colP]); 
        printf("\n"); 
    } 
}
//function helps in setting the row and column parameters of the puzzle if the size is changed
void setSize() {
	switch(N) {
		case 6:
			row = 2;
			break;
		case 9: 
			row = 3;
			break;		  
		case 16: 
			row = 4;
			break;
		case 25:
			row = 5;
			break; 
		default:
			return;
	}
	col = N / row;
}
//copies data from one array to another
void copySol(int **sol, int **puzzle) {
	int rowNo, colNo;
	for(rowNo = 0; rowNo < N; rowNo++)
		for(colNo = 0; colNo < N; colNo++) 
			sol[rowNo][colNo] = puzzle[rowNo][colNo];
}
//used to cross-check puzzle and its solution
int check(int **puzzle) {
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if(puzzle[i][j] != sol[i][j])
				return 0;
	return 1;				
}	
