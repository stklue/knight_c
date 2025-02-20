#include "stdio.h"
#include "defs.h"

const int bit_table[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8};

int pop_bit(U64 *bb)
{
    U64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return bit_table[(fold * 0x783a9b23) >> 26];
}

int count_bits(U64 b)
{
    int r;
    for (r = 0; b; r++, b &= b - 1)
        ;
    return r;
}

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
            sq64 = SQ64(sq);        // converts 120 board coordinate to 64 board coordinates using the 120 board index
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