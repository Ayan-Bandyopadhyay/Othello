#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    
private:
	Board board;
	Side opponent_side;
	Side player_side;
	int get_score( Move * m);
	
};
    
	/** @brief Inserts an integer into the subtree rooted at this node.

    Does not allow duplicate entries.

    @return whether or not the entry was successfully inserted.

    */
    bool insert(Board b)
    {
		next_moves.push_back( Node(b));

    }
};
#endif
