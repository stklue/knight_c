#include "defs.h"
#include "stdio.h"

void Reset_Board(S_BOARD *pos)
{
    int index = 0;

    // clear the postions of all the pieces
    for (index = 0; index < BRD_SQ_NUM; index++)
    {
        pos->pieces[index] = OFFBOARD;
    }

    for (index = 0; index < 64; index++)
    {
        pos->pieces[SQ64_TO_SQ120[index]] = EMPTY;
    }

    for (index = 0; index < 2; ++index)
    {
        pos->big_piece[index] = 0;
        pos->maj_piece[index] = 0;
        pos->min_piece[index] = 0;
        // pos->material[index] = 0;
        pos->pawns[index] = 0ULL;
    }

    for (index = 0; index < 3; ++index)
    {
        pos->pawns[index] = 0ULL;
    }

    for (index = 0; index < 13; ++index)
    {
        pos->piece_num[index] = 0;
    }

    pos->King_Sq[WHITE] = pos->King_Sq[BLACK] = NO_SQ;

    pos->side = BOTH;
    pos->enPas = NO_SQ;
    pos->fifty_move = 0;

    pos->ply = 0;
    pos->hisPly = 0;

    pos->castle_permission = 0;

    pos->pos_key = 0ULL;
}