#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
#include <algorithm>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int minimax(Board *board_node, int depth, Side side);
    void set_board(Board *board);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    
private:
	Board board;
	Side opponent_side;
	Side player_side;
	int get_score( Move * m);
};

#endif



