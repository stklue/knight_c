#include "stdio.h"
#include "defs.h"

int main(void) {
    All_Init();


    U64 play_bit_board = 0ULL;
    // printf("Initial Board:\n\n ");
    // print_bit_board(play_bit_board);

    // play_bit_board |= (1ULL << SQ64(D2));
    // printf("D2 Added:\n\n ");
    // print_bit_board(play_bit_board);

    // play_bit_board |= (1ULL << SQ64(G2));
    // printf("G2 Added:\n\n "); 
    // print_bit_board(play_bit_board);
    
    S_BOARD board;
    set_bit(play_bit_board,16);
    print_bit_board(play_bit_board);
    // printf("%d\n", board.hisPly);

    return 0;
} 