// include guard: guard against multiple includes
#ifndef DEFS_H 
#define DEFS_H

typedef unsigned long long U64;

#define NAME "Knight 1.0"
#define BRD_SQ_NUM 120 // number of board squars
#define MAXGAMEMOVES 2048

enum {EMPTY, wP, wN, wB, wK, wQ, wR, bP, bN, bB, bK, bQ, bR};
enum {FILE_A,FILE_B, FILE_C, FILE_D, FILE_E, FILE_F,FILE_G, FILE_H, FILE_NONE};
enum {BLACK, WHITE, BOTH};
enum {
    A1 = 21, B1, C1, D1, E1 , F1, G1, H1,
    A2 = 31, B2, C2, D2, E2 , F2, G2, H2,
    A3 = 41, B3, C3, D3, E3 , F3, G3, H3,
    A4 = 51, B4, C4, D4, E4 , F4, G4, H4,
    A5 = 61, B5, C5, D5, E5 , F5, G5, H5,
    A6 = 71, B6, C6, D6, E6 , F6, G6, H6,
    A7 = 81, B7, C7, D7, E7 , F7, G7, H7,
    A8 = 91, B8, C8, D8, E8 , F8, G8, H8, NO_SQ
};
enum {FALSE, TRUE};


enum {WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

typedef struct {
    int move;
    int cast_permission;
    int en_pas;
    int fifty_moves;
    U64 pos_key;
} S_UNDO;

typedef struct {
    int pieces[BRD_SQ_NUM];
    U64 pawns[3];
    int King_Sq[2];
    
    int side;
    int enPas;
    int fifty_move;
    
    int ply;
    int hisPly;

    int castle_permission;
    
    U64 pos_key;
    
    int piece_num[13];
    int big_piece[3];
    int maj_piece[3];
    int min_piece[3];

    S_UNDO history[MAXGAMEMOVES];

} S_BOARD;

#endif