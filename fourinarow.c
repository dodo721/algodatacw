#include <stdlib.h>
#include <stdio.h>
//#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#define WIDTH 7
#define HEIGHT 6

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

struct Move {

	int x;
	int player;
	struct Move *prev;
	struct Move *next;

};

struct Move *history;

void clearFutureMoves (void) {

	if (history == NULL)
		return;
	struct Move *currentMove = history;
	while (currentMove->next != NULL) {
		currentMove = currentMove->next;
		currentMove->prev->next = NULL;
		if (currentMove->prev != history) {
			free(currentMove->prev);
		}
	}

	free(currentMove);

}

void newMove (int x, int player) {

	struct Move move;
	move.x = x;
	move.player = player;
	if (history == NULL)
		move.prev = NULL;
	else
		move.prev = history;
	move.next = NULL;
	if (history != NULL)
		if (history->next != NULL)
			clearFutureMoves();
	history = &move;

}

void clearHistory (void) {

	if (history == NULL)
		return;
	while (history->prev != NULL)
		history = history->prev;
	while (history->next != NULL) {
		history = history->next;
		free(history->prev);
	}
	
	free(history);
	history = NULL;

}

struct Collumn {

	struct Cell *cells;
	int top;

};

struct Board {
	
	struct Collumn **collumns;
	
};

struct Board board;

void newBoard (void) {
	
	struct Board newBoard;
	newBoard.collumns = (struct Collumn **)malloc(WIDTH * sizeof(struct Collumn*));
	for (int i = 0; i < WIDTH; i++) {
		struct Collumn collumn;
		collumn.top = 0;
		collumn.cells = (struct Cell *)malloc(HEIGHT * sizeof(struct Cell));
		newBoard.collumns[i] = &collumn;
		for (int j = 0; j < HEIGHT; j++) {
			struct Cell newCell;
			newCell.state = 0;
			newCell.checked = false;
			collumn.cells[j] = newCell;
		}
	}
	printf("\n");
	board = newBoard;
	
}

void printCell (struct Cell cell, int i, int j) {
	char *symbol = " ";
	if (cell.state == 1) {
		symbol = "x";
	} else if (cell.state == 2) {
		symbol = "o";
	}
	printf("[%d,%d %s]", i,j,symbol);
}

void printBoard (void) {
	for (int i = HEIGHT - 1; i >= 0; i --) {
		for (int j = 0; j < WIDTH; j++) {
			printCell(board.collumns[j]->cells[i], j, i);
		}
		printf("\n");
	}
}

void insertCell (int x, int state) {
	
	if (x >= WIDTH) {
		printf("X Coord is out of bounds!\n");
		return;
	}
	struct Collumn *collumn = board.collumns[x];
	if (collumn->top < HEIGHT) {
		printf("Inserting into collumn %d at top %d\n", x, collumn->top);
		struct Cell newCell;
		newCell.state = state;
		collumn->cells[collumn->top] = newCell;
		collumn->top++;
		newMove(x, state);
	} else {
		printf("That collumn is full!\n");
	}
	
}

void undo (void) {

	if (history->prev != NULL) {
		history = history->prev;
		
	}

}

void redo (void) {
	
	if (history->next != NULL) {
		history = history->next;
	}

}

void printMenu (void) {
	
	printf(
		"0. Exit\n1. Insert cell\n"
	);

}

int getNum (void) {
	printf("> ");
	int menu;
	int success = scanf(" %d", &menu);
	while (getchar() != '\n');
	if (success == 0) {
		printf("Entry must be a number!\n\n");
		return -1;
	}
	return menu;
}

int player = 1;

int main (void) {
	
	newBoard();
	while (true) {
		printBoard();
		printf("\n\n");
		printMenu();
		int option = getNum();
		if (option == -1)
			continue;
		if (option == 1) {
			printf("Enter x coord: ");
			int x = getNum();
			if (x == -1)
				continue;
			x--;
			insertCell(x, player);
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