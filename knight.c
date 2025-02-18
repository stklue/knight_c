#include "stdio.h"
#include "defs.h"

int main(void) {
    All_Init();


    U64 play_bit_board = 0ULL;
    printf("Initial Board:\n\n ");
    print_bit_board(play_bit_board);

    play_bit_board |= (1ULL << SQ64(D2));
    printf("D2 Added:\n\n ");
    print_bit_board(play_bit_board);

    play_bit_board |= (1ULL << SQ64(G2));
    printf("G2 Added:\n\n "); 
    print_bit_board(play_bit_board);
    
    return 0;
} 