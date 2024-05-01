#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[5][5];
char player_A = 'X';
char player_B = 'O';
char current_player = 'A';

void initialize_board() {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            board[i][j] = ' ';
        }
    }
}

void print_board() {
    int i, j;
    printf("\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf(" %c ", board[i][j]);
            if (j != 4) {
                printf("|");
            }
        }
        printf("\n");
        if (i != 4) {
            printf("---+---+---+---+---\n");
        }
    }
    printf("\n");
}

int is_valid_move(int row, int col) {
    if (row < 0 || row >= 5 || col < 0 || col >= 5) {
        return 0;
    }
    if (board[row][col] != ' ') {
        return 0;
    }
    return 1;
}

int check_win(char symbol) {
    int i, j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                return 1;
            }
        }
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            if (board[j][i] == symbol && board[j + 1][i] == symbol && board[j + 2][i] == symbol) {
                return 1;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if (board[i][i] == symbol && board[i + 1][i + 1] == symbol && board[i + 2][i + 2] == symbol) {
            return 1;
        }
        if (board[i][4 - i] == symbol && board[i + 1][3 - i] == symbol && board[i + 2][2 - i] == symbol) {
            return 1;
        }
    }

    return 0;
}

int is_draw() {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void switch_player() {
    if (current_player == 'A') {
        current_player = 'B';
    }
    else {
        current_player = 'A';
    }
}

void make_move(int row, int col) {
    if (current_player == 'A') {
        board[row][col] = player_A;
    }
    else {
        board[row][col] = player_B;
    }
}

void play_game() {
    int row, col;
    int game_finished = 0;
    initialize_board();
    while (!game_finished) {
        print_board();
        printf("행과 열을 입력하세요. (x, y): ");
        scanf("%d %d", &col, &row);
        if (!is_valid_move(row - 1, col - 1)) {
            printf("놓을 수 없습니다. 다시하세요\n");
            continue;
        }
        make_move(row - 1, col - 1);
        if (check_win(current_player == 'A' ? player_A : player_B)) {
            print_board();
            printf("플레이어 %c가 승리했습니다.\n", current_player);
            game_finished = 1;
        }
        else if (is_draw()) {
            print_board();
            printf("무승부\n");
            game_finished = 1;
        }
        switch_player();
    }
}

int main() {
    srand(time(0));
    play_game();
    return 0;
}
