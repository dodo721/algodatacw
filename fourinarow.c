#include <stdio.h>
//#include <math.h>
#include <stdbool.h>

#define WIDTH 7
#define HEIGHT 6

int currentStep = 0;
int player = 1;

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
			char* symbol = " ";
			if (board.cells[i][j].state == 1) {
				symbol = "x";
			} else if (board.cells[i][j].state == 2) {
				symbol = "o";
			}
			printf("[%s]", symbol);
		}
		printf("\n");
	}
}

struct Board insertCell (struct Board board, int x, int state) {
	
	if (x >= WIDTH) {
		printf("X Coord is out of bounds!\n");
		return board;
	}
	struct Cell newCell;
	newCell.state = state;
	int y = 0;
	while (board.cells[y + 1][x].state == 0) {
		if (y == HEIGHT - 2) {
			if (board.cells[y + 1][x].state == 0)
				y++;
			break;
		}
		y++;
	}
	board.cells[y][x] = newCell;
	return board;
	
}

void printMenu (void) {
	
	printf(
		"0. Exit\n1. Insert cell\n"
	);
	
}

int getNum (void) {
	int num = getchar();
	num -= '0';
	getchar();
	return num;
}

int main (void) {
	
	struct Board board = newBoard();
	while (true) {
		printBoard(board);
		printf("\n\n");
		printMenu();
		int option = getNum();
		if (option == 1) {
			printf("Enter x coord: ");
			int x = getNum() - 1;
			board = insertCell(board, x, player);
			if (player == 1)
				player = 2;
			else
				player = 1;
		} else if (option == 0) {
			printf("Bye!");
			break;
		}
	}
	
	printf("\nOK\n");
	return 0;
	
}