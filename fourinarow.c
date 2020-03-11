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
	struct Move *prev;
	struct Move *next;

};

struct Move *history;

int historySize (void) {
	if (history == NULL) {
		return 0;
	} else {
		int moves = 1;
		struct Move *temp = history;
		while (temp->next != NULL)
			temp = temp->next;
		while (temp->prev != NULL) {
			temp = temp->prev;
			moves++;
		}
		return moves;
	}
}

int movesBehind (void) {
	if (history == NULL)
		return 0;
	struct Move *temp = history;
	int behind = 0;
	while (temp->next != NULL) {
		temp = temp->next;
		behind++;
	}
	return behind;
}

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

	struct Move *move = (struct Move *)malloc(sizeof(struct Move));
	move->x = x;
	move->prev = history;
	move->next = NULL;
	if (history != NULL) {
		if (history->next != NULL)
			clearFutureMoves();
		history->next = move;
	}
	history = move;

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
	
	struct Collumn *collumns;
	
};

struct Board board;

void newBoard (void) {
	
	struct Board newBoard;
	newBoard.collumns = (struct Collumn *)malloc(WIDTH * sizeof(struct Collumn));
	for (int i = 0; i < WIDTH; i++) {
		struct Collumn collumn;
		collumn.top = 0;
		collumn.cells = (struct Cell *)malloc(HEIGHT * sizeof(struct Cell));
		newBoard.collumns[i] = collumn;
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

char* getState(int state) {
	if (state == 0) {
		return " ";
	} else if (state == 1) {
		return "x";
	} else if (state == 2) {
		return "o";
	}
}

void printCell (struct Cell cell, int i, int j) {
	char *symbol = getState(cell.state);
	printf("[%s]", symbol);
}

void printBoard (void) {
	for (int i = 0; i < WIDTH; i++) {
		printf(" %d ", i+1);
	}
	printf("\n");
	for (int i = HEIGHT - 1; i >= 0; i --) {
		for (int j = 0; j < WIDTH; j++) {
			printCell(board.collumns[j].cells[i], j, i);
		}
		printf("\n");
	}
}

void insertCell (int x, int state) {
	
	if (x >= WIDTH) {
		printf("X Coord is out of bounds!\n");
		return;
	}
	struct Collumn collumn = board.collumns[x];
	if (collumn.top < HEIGHT) {
		struct Cell newCell;
		newCell.state = state;
		collumn.cells[collumn.top] = newCell;
		collumn.top++;
		board.collumns[x] = collumn;
		newMove(x, state);
	} else {
		printf("That collumn is full!\n");
	}
	
}

int player = 1;

void undo (void) {
	
	if (history != NULL) {
		struct Move move;
		if (history->prev != NULL) {
			history = history->prev;
			struct Move move = *history->next;
		} else {
			move = *history;
		}
		int x = move.x;
		board.collumns[x].cells[board.collumns[x].top - 1].state = 0;
		board.collumns[x].cells[board.collumns[x].top - 1].checked = false;
		board.collumns[x].top--;
		if (player == 1) {
			player = 2;
		} else {
			player = 1;
		}
	}

}

void redo (void) {
	
	if (history != NULL) {
		if (history->next != NULL) {
			history = history->next;
			struct Move move = *history;
			int x = move.x;
			board.collumns[x].cells[board.collumns[x].top].state = player;
			board.collumns[x].top++;
			if (player == 1) {
				player = 2;
			} else {
				player = 1;
			}
		}
	}

}

void printMenu (void) {
	
	printf("Player %s's turn\n", getState(player));
	printf("%d moves behind\n", movesBehind());
	printf(
		"0. Exit\n1. Insert cell\n2. Undo move\n3. Redo move\n"
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
		} else if (option == 2) {
			undo();
			printf("Move undone\n");
		} else if (option == 3) {
			redo();
			printf("Move redone\n");
		} else {
			printf("That's not an option!\n");
		}
	}
	
	printf("\nOK\n");
	return 0;
	
}