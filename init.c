#include "defs.h"

int SQ120_TO_SQ64[BRD_SQ_NUM]; 
int SQ64_TO_SQ120[64];

U64 set_mask[64];
U64 clear_mask[64];



void Init_Bit_Masks() {
    int index = 0;

    for (index = 0; index < 64; index++) {
        set_mask[index] = 0ULL;        
        clear_mask[index] = 0ULL;        
    }

    for (index = 0; index < 64; index++) {
        set_mask[index] |= 1ULL << index;        
        clear_mask[index] = ~set_mask[index];        
    }
}

void Init_Sq120_To_64 () {
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;


    /* Initialize boards */
    for (index = 0; index < BRD_SQ_NUM; ++index) {
        SQ120_TO_SQ64[index] = 65; // set to an invalid sq num
    }

    for (index = 0; index < 64; ++index) {
        SQ64_TO_SQ120[index] = 120; // set to an invalid sq num
    }


    // Initilizing both boards indices to their ids
    // Board 64: 0 - 63
    // Board 120: 0 - 119

    for (rank = RANK_1; rank <= RANK_8; ++rank) {
        for (file = FILE_A; file <= FILE_H; ++ file) {
            sq = FR2SQ(file, rank);
            SQ64_TO_SQ120[sq64] = sq; // -> [21, 22, 23, 24, 25, 26, 27, 28, 31, 32, 33, ... , 38, ..., 91, .., 98 ]
            SQ120_TO_SQ64[sq] = sq64; // -> [0: 65, ..., (index: 21) = 0, 22: 1, 23: 2, 3, 4, 5, 6, 28: 7]
            sq64++;
        }
    }
}

void All_Init() {
    Init_Sq120_To_64();
    Init_Bit_Masks();
}


/* 
    SQ64_TO_SQ120 Array (64 elements)
      0   1   2   3   4   5   6   7
      -   -   -   -   -   -   -   -
    | 21, 22, 23, 24, 25, 26, 27, 28, 
    | 31, 22, 23, 24, 25, 26, 37, 38, 
    | 41, 22, 23, 24, 25, 26, 47, 48, 
    | 51, 22, 23, 24, 25, 26, 57, 58, 
    | 61, 22, 23, 24, 25, 26, 67, 68, 
    | 71, 22, 23, 24, 25, 26, 27, 78, 
    | 81, 22, 23, 24, 25, 26, 27, 88, 
    | 91, 92, 93, 94, 95, 96, 97, 98, 
    
    SQ120_TO_SQ64 Array (120 elements)
    


*/ 