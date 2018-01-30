#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define TOP_LEFT_CORNER 0
#define TOP_EDGE 1
#define TOP_RIGHT_CORNER 2
#define LEFT_EDGE 3
#define MIDDLE 4
#define RIGHT_EDGE 5
#define BOT_LEFT_CORNER 6
#define BOT_EDGE 7
#define BOT_RIGHT_CORNER 8

#define CROSS -1
#define CIRCLE 1

char **x, **o, **e;

void init_print_board()
{
    x = malloc(3*sizeof(char*));
    o = malloc(3*sizeof(char*));
    e = malloc(3*sizeof(char*));

    for (int i = 0; i < 3; i++) {
        x[i] = malloc (5*sizeof(char));
        o[i] = malloc (5*sizeof(char));
        e[i] = malloc (5*sizeof(char));
    }

    strcpy(x[0], " \\ / ");
    strcpy(x[1], "  x  ");
    strcpy(x[2], " / \\ ");
    strcpy(o[0], " ooo ");
    strcpy(o[1], "ooooo");
    strcpy(o[2], " ooo ");
    for (int i = 0; i < 3; i++) {
        strcpy(e[i], "     ");
    }
}

void uinit_print_board()
{
    for (int i = 0; i < 3; i++) {
        free(x[i]);
        free(o[i]);
        free(e[i]);
    }
    free(x);
    free(o);
    free(e);
}

void print_board (int *board)
{
    char **str_p0, **str_p1, **str_p2;

    for (int i = 0; i < 10; i++) printf("\n\n\n\n\n");

    for (int i = 0; i < 3; i++) {
        str_p1 = e;
        str_p2 = e;
        str_p0 = e;

        if (board[i*3] == CROSS) {
            str_p0 = x;
        }
        else if (board[i*3] == CIRCLE) {
            str_p0 = o;
        }

        if (board[i*3+1] == CROSS) {
            str_p1 = x;
        }
        else if (board[i*3+1] == CIRCLE) {
            str_p1 = o;
        }

        if (board[i*3+2] == CROSS) {
            str_p2 = x;
        }
        else if (board[i*3+2] == CIRCLE) {
            str_p2 = o;
        }

        if (i) printf("-------+-------+-------\n");
        printf(" %s | %s | %s \n", str_p0[0], str_p1[0], str_p2[0]);
        printf(" %s | %s | %s \n", str_p0[1], str_p1[1], str_p2[1]);
        printf(" %s | %s | %s \n", str_p0[2], str_p1[2], str_p2[2]);
    }

    printf("\n123\n456\n789\n");
}

int is_win(int *b)
{
    //ROWS
    if (b[0] != 0 && b[0] == b[1] && b[0] == b[2])
        return b[0];
    if (b[3] != 0 && b[3] == b[4] && b[3] == b[5])
        return b[3];
    if (b[6] != 0 && b[6] == b[7] && b[6] == b[8])
        return b[6];

    //COLS
    if (b[0] != 0 && b[0] == b[3] && b[0] == b[6])
        return b[0];
    if (b[1] != 0 && b[1] == b[4] && b[1] == b[7])
        return b[1];
    if (b[2] != 0 && b[2] == b[5] && b[2] == b[8])
        return b[2];

    //DIAGS
    if (b[0] != 0 && b[0] == b[4] && b[0] == b[8])
        return b[0];
    if (b[6] != 0 && b[6] == b[4] && b[6] == b[2])
        return b[6];

    return 0;
}

void p2_mode()
{
    int board[9] = {0,0,0,0,0,0,0,0,0};
    int turn = CROSS, move_count = 0, val, winner;
    char buf[8];

    while (!(winner = is_win(board)) && move_count < 9) {

        print_board(board);
        if (turn == CROSS) printf("\nCrosses, your turn (1-9): ");
        else if (turn == CIRCLE) printf("\nCircles, your turn (1-9): ");
        else { printf("\nshit's fucked\n"); exit(1);}

        do {
        RETRY:
            fgets(buf, 8, stdin);
            val = atoi(buf);

            if (val < 1 || val > 9)
                goto RETRY;

        } while (board[val-1] != 0);

        board[val-1] = turn;
        turn *= -1;
        move_count++;
    }

    print_board(board);
    if (winner) {
        if (winner == CROSS) printf("\nCrosses Win!\n");
        else printf("\nCircles Win!\n");
    }
}

void cpu_mode() 
{

}

int main() {

    int difficulty = 0;
    init_print_board();

    if (!difficulty) {
        p2_mode();
    }
    else {
        cpu_mode(difficulty);
    }

    uinit_print_board();
	return 0;
}
