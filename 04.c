#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "inputs/04.h"

#define SIZE 5
#define N_BOARDS 100

typedef struct {
    int number;
    bool marked;
}BingoCell;

int markBoard(BingoCell *board, int draw) {
    for (int cell = 0; cell < (SIZE * SIZE); cell++) {
        if (board[cell].number != draw) continue;
        board[cell].marked = true;
    }

    return 0;
}

bool boardFinished(BingoCell *board) {
    // Check for complete column
    for (int col = 0; col < SIZE; col++){
        int marked_col_vals = 0;
        for (int cell = 0; cell < (SIZE * SIZE); cell++) {
            if (cell % SIZE != col) continue;
            if (!board[cell].marked) {
                marked_col_vals = 0;
                break;
            }
            marked_col_vals += 1;

            if (marked_col_vals == SIZE) {
                return true;
            }
        }
    }

    // Check for complete row
    for (int row = 0; row < SIZE; row++) {
        int marked_row_vals = 0;
        for (int cell = 0; cell < (SIZE * SIZE); cell++) {
            if (cell < (row * SIZE) || cell >= ((row + 1) * SIZE)) continue;
            if (!board[cell].marked) {
                marked_row_vals = 0;
                break;
            }
            marked_row_vals += 1;

            if (marked_row_vals == SIZE) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    const unsigned char *s = input;
    int drawn_numbers[500] = {0};
    int n = 0;
    BingoCell boards[N_BOARDS][SIZE * SIZE];

    while (*s != '\0') {

        // Read in numbers to be drawn
        while (*s != '\n') {
            while (*s < '0' || *s > '9') s++;
            while (*s >= '0' && *s <= '9') {
                drawn_numbers[n] = (drawn_numbers[n] * 10) + (*s - '0');
                s++;
            }
            s++;
            n++;
        }

        // Skip down to board descriptions
        s++;

        // Read in individual bingo boards
        for (int b = 0; b < N_BOARDS; b++) {

            BingoCell board[SIZE * SIZE];
            int value;
            for (int cell = 0; cell < (SIZE * SIZE); cell++) {
                value = 0;

                while (*s < '0' || *s > '9') s++;
                while (*s >= '0' && *s <= '9') {
                    value = (value * 10) + (*s - '0');
                    s++;
                }
                board[cell].number = value;
                board[cell].marked = false;
                s++;
            }

            // Add individual board to main array
            for (int c = 0; c < (SIZE * SIZE); c++) {
                boards[b][c] = board[c];
            }
        }
        break;
    }


    int unfinished_boards[N_BOARDS];
    for (int board = 0; board < N_BOARDS; board++) {
        unfinished_boards[board] = 1;
    }

    int n_unfinished_boards = -1;
    int last_board, winning_number;
    for (int i = 0; i < n; i++) {
        // Mark off an individual number on each board
        for (int board_i = 0; board_i < N_BOARDS; board_i++) {
            markBoard(boards[board_i], drawn_numbers[i]);

            if (boardFinished(boards[board_i])) {
                unfinished_boards[board_i] = 0;

                // Check if a single board remains unfinished
                n_unfinished_boards = 0;
                for (int b = 0; b < N_BOARDS; b++) {
                    if (unfinished_boards[b] == 1) n_unfinished_boards++;
                }
                if (n_unfinished_boards == 0) {
                    winning_number = drawn_numbers[i];
                    last_board = board_i;
                    break;
                }
            }
        }
        if (n_unfinished_boards == 0) break;
    }

    // Sum unmarked numbers of selected board
    int unmarked = 0;
    for (int cell = 0; cell < (SIZE * SIZE); cell++) {
        if (boards[last_board][cell].marked) continue;
        unmarked += boards[last_board][cell].number;
    }

    printf("%d\n", unmarked * winning_number);

    return 0;
}
