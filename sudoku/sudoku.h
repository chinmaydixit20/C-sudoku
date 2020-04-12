#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#define N 9
#define UNASSIGNED 0

void getHint(int **puzzle);
int findUnassignedLocation(int **puzzle, int *rowNo, int *colNo);
int solveSudoku(int **puzzle);
int usedInRow(int **puzzle, int row, int num);			 				
int usedInColumn(int **puzzle, int col, int num);
int usedInBox(int **puzzle, int boxStartRow, int boxStartColumn, int num); 
int isSafe(int **puzzle, int row, int col, int num);
int solve(int **puzzle);
void printGrid(int **puzzle);
int generateSudoku(int **puzzle, int difficulty);
int usedInArr(int *arr, int num);
int solveForGenerate(int **puzzle);
int setDifficultyVal(int difficulty);
void copySol(int **sol, int **puzzle);
void saveSudoku(int **puzzle, char *file_name);
void resume(int **puzzle,  char *filename);
void setSize();
int check(int **puzzle);
enum difficulty {EASY = 1, MODERATE, HARD};

int **sol;
int row, col;
