#include <stdio.h>
//#include <math.h>
#include <stdbool.h>

#define WIDTH 7
#define HEIGHT 6

int currentStep = 0;

struct Cell {
	
	int state;
	/*struct cell *u;
	struct cell *d;
	struct cell *l;
	struct cell *r;
	struct cell *dlu;
	struct cell *dld;
	struct cell *dru;
	struct cell *drd;*/
	bool checked;
	
};

struct Board {
	
	struct Cell **cells;
	
};

struct Board newBoard (void) {
	
	struct Board board;
	board.cells = (struct Cell **)malloc(HEIGHT * sizeof(struct Cell *));
	for (int i = 0; i < HEIGHT; i++) {
		board.cells[i] = (struct Cell *)malloc(WIDTH * sizeof(struct Cell));
		for (int j = 0; j < WIDTH; j++) {
			struct Cell newCell;
			newCell.state = 0;
			newCell.checked = false;
			board.cells[i][j] = newCell;
		}
	}
	return board;
	
}

void printBoard (struct Board board) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			printf("[%d]", board.cells[i][j].state);
		}
		printf("\n");
	}
}

struct Board insertCell (struct Board board, int x, int y, int state) {
	
	struct Cell newCell;
	newCell.state = state;
	board.cells[y][x] = newCell;
	return board;
	
}

void printMenu (void) {
	
	printf("1. Insert cell\n");
	
}

int main (void) {
	
	struct Board board = newBoard();
	printBoard(board);
	printf("\n\n");
	board = insertCell(board, 4, 3, 1);
	printBoard(board);
	printf("OK\n");
	return 0;
	
}