#include "stdio.h"
#include "defs.h"
/*
    21 22 - - - - - - 28
    31 32 - - - - - - 38
    41 42 - - - - - - 48
    51 52 - - - - - - 58
    61 62 - - - - - - 68
    71 72 - - - - - - 78
    81 82 - - - - - - 88
    91 92 - - - - - - 98
*/ 
void print_bit_board(U64 bb)
{
    U64 shift_me = 1ULL;

    int rank = 0;
    int file = 0;
    int sq = 0;
    int sq64 = 0;

    printf("\n");

    for (rank = RANK_8; rank >= RANK_1; --rank)
    {
        for (file = FILE_A; file <= FILE_H; ++file)
        {
            // this is a number starting at 21 ending at 98 with out of bounds padding numbers at the edges
            sq = FR2SQ(file, rank); // outputs are values in:  21, .., 28, 31, .., 38 , .., 91, .., 98  
            sq64 = SQ64(sq); // converts 120 board coordinate to 64 board coordinates using the 120 board index  
            // sq64 is a board 64 index not the value of a board 64 index
            if ((shift_me << sq64) & bb)
                printf("X");
            else
                printf("-");
        }

        printf("\n");
    }
    printf("\n\n");
}