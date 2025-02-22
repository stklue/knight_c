#include "defs.h"
#include "stdio.h"

/* Parse the fen string and initialize the board state */
int Parse_Fen(char *fen, S_BOARD *pos)
{
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
    ASSERT(fen != NULL);
    ASSERT(pos != NULL);

    int rank = RANK_8; // start here since lower case is black pieces
    int file = FILE_A;

    int piece = 0; // holds the piece if there is one
    int count = 0; // count the number of empty squares
    int i = 0;
    int sq64 = 0;
    int sq120 = 0;

    Reset_Board(pos);

    while ((rank >= RANK_1) && *fen)
    {
        count = 1;
        switch (*fen)
        {
        case 'p':
            piece = bP;
            break;
        case 'r':
            piece = bR;
            break;
        case 'n':
            piece = bN;
            break;
        case 'b':
            piece = bB;
            break;
        case 'q':
            piece = bQ;
            break;
        case 'k':
            piece = bK;
            break;

        case 'P':
            piece = wP;
            break;
        case 'R':
            piece = wR;
            break;
        case 'N':
            piece = wN;
            break;
        case 'B':
            piece = wB;
            break;
        case 'Q':
            piece = wQ;
            break;
        case 'K':
            piece = wK;
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            piece = EMPTY;
            count = *fen - '0';
            break;
        case ' ':
        case '/': // A '/' means move to the next rank
            rank--;
            file = FILE_A;
            fen++;
            continue;
        default:
            printf("FEN error: \n");
            return -1;
        }

        for (i = 0; i < count; i++)
        {
            sq64 = rank * 8 + file;
            sq120 = SQ64_TO_SQ120[sq64];

            if (piece != EMPTY)
            {
                pos->pieces[sq120] = piece;
            }

            file++;
        }

        fen++;
    }

    ASSERT(*fen == 'w' || *fen == 'b');

    pos->side = (*fen == 'w') ? WHITE : BLACK;
    fen += 2;

    for (i = 0; i < 4; i++)
    {
        if (*fen == ' ')
        {
            break;
        }

        switch (*fen)
        {
        case 'K':
            pos->castle_permission |= WKCA;
            break;
        case 'Q':
            pos->castle_permission |= WQCA;
            break;
        case 'k':
            pos->castle_permission |= BKCA;
            break;
        case 'q':
            pos->castle_permission |= BQCA;
            break;

        default:
            break;
        }
        fen++;
    }
    fen++;


    ASSERT(pos->castle_permission >= 0 && pos ->castle_permission <= 15);

    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1'

        ASSERT(file>=FILE_A && file <= FILE_H);
        ASSERT(rank>=RANK_1 && rank <= RANK_8);


        pos->enPas = FR2SQ(file, rank);
    }


    pos ->pos_key = GeneratePosKey(pos);


    // Update_List_Material(pos);


    return 0;
}

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