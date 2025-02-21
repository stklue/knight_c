// hashkeys.c
#include "stdio.h"
#include "defs.h"

U64 GeneratePosKey(const S_BOARD *pos) {

	int sq = 0;
	U64 finalKey = 0;
	int piece = EMPTY;
	
	// pieces
	for(sq = 0; sq < BRD_SQ_NUM; ++sq) {
		piece = pos->pieces[sq];
		if(piece!=NO_SQ && piece!=EMPTY && piece != OFFBOARD) {
			ASSERT(piece>=wP && piece<=bK);
			finalKey ^= piece_keys[piece][sq];
		}		
	}
	
	if(pos->side == WHITE) {
		finalKey ^= side_key;
	}
		
	if(pos->enPas != NO_SQ) {
		ASSERT(pos->enPas>=0 && pos->enPas<BRD_SQ_NUM);
		ASSERT(SqOnBoard(pos->enPas));
		ASSERT(RanksBrd[pos->enPas] == RANK_3 || RanksBrd[pos->enPas] == RANK_6);
		finalKey ^= piece_keys[EMPTY][pos->enPas];
	}
	
	ASSERT(pos->castlePerm>=0 && pos->castlePerm<=15);
	
	finalKey ^= castle_keys[pos->castle_permission];
	
	return finalKey;
}
