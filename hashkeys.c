// hashkeys.c
#include "stdio.h"
#include "defs.h"

U64 GeneratePosKey(const S_BOARD *pos)
{

    int sq = 0;
    U64 finalKey = 0;
    int piece = EMPTY;

    // pieces -> result of this is a unique position for the pieces on the board
    for (sq = 0; sq < BRD_SQ_NUM; ++sq)
    {
        piece = pos->pieces[sq];
        if (piece != NO_SQ && piece != EMPTY && piece != OFFBOARD)
        {
            ASSERT(piece >= wP && piece <= bK); // at this point we only takes squares with pieces on them
            finalKey ^= piece_keys[piece][sq];
            // finalKey ^= pice_keys[1 = wP][8 = a2] = 1203 or
            // finalKey ^= pice_keys[12 = bK][60 = e8] = 21312
            // the finalKey = 1203 ^ 21312 = X .If these two were the only peices on the board 
            // then X will be the unique hash value respresenting the board or their positions. 
            // This final key is the XOR of all the pieces on the board (valid squares only)
            // resulting in a unique respresentation for the pieces on the board
        }
    }
    // included as it's part of the game state
    if (pos->side == WHITE)
    {
        finalKey ^= side_key;
    }

    // included as it's part of the game state
    if (pos->enPas != NO_SQ)
    {
        ASSERT(pos->enPas >= 0 && pos->enPas < BRD_SQ_NUM);
        ASSERT(SqOnBoard(pos->enPas));
        ASSERT(RanksBrd[pos->enPas] == RANK_3 || RanksBrd[pos->enPas] == RANK_6);
        finalKey ^= piece_keys[EMPTY][pos->enPas]; // piece_keys[0][16 = a3]
    }

    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    finalKey ^= castle_keys[pos->castle_permission];

    return finalKey;
}
