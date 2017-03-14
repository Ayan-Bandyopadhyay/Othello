#include "player.hpp"
/**
 * small change to the player.cpp file
 */
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     board = Board();
     player_side = side;
     if ( side == BLACK)
     {
         opponent_side = WHITE;
     }
     else
     {
         opponent_side = BLACK;
     }
     
     
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) 
{
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    if (testingMinimax)
    {
        // Constructing the tree.
        Board *new_board;
        new_board = board.copy();
        DecisionTree tree;
        tree.insert_root(*new_board);

        tree.insert_root(*new_board, nullptr);

		tree.generate_layer(player_side, tree.get_root());
		for(unsigned int i= 0; i < tree.get_root()->next_moves.size(); i++)
		{ 	
			tree.generate_layer(opponent_side, tree.get_root()->next_moves[i]);
		}
        



    }

    else
    {
        if ( opponentsMove != nullptr)
        {
            board.doMove( opponentsMove, opponent_side);
        }
        
        Move *m;
        vector<Move*> possible_moves;
        int score = -88888;
        int new_score = -99999;
        Move *best_move = new Move(1, 1);
        
        
        for (int i = 0; i < 8; i++) 
        {
            for (int j = 0; j < 8; j++) 
            {
                m = new Move(i, j);
                if (board.checkMove(m, player_side))
                {
                    possible_moves.push_back(m);
                }
                else
                {
                    delete m;
                }
            }
        }
        

        /**
        if (!board.hasMoves(player_side))
        {
            m = nullptr;
        }*/
        
        for (unsigned int i = 0; i < possible_moves.size(); i++)
        {
            new_score = Player::get_score( possible_moves[i]);
            if (new_score >= score)
            {
                score = new_score;
                best_move = possible_moves[i];
            }


        }

        board.doMove(best_move, player_side);
        return best_move; 
    }   
}

int Player::alphabeta(Node *node, int level, int alpha, int beta, 
    bool maximizing, Side player_side, Side opponent_side)
{
    int best_value;
    if (node->next_moves.size() == 0)
    {
        return node->board_state.count(player_side, opponent_side);
    }

    if (maximizing)
    {
        best_value = -99999;
        for (unsigned int i = 0; i < node->next_moves.size(); i++)
        {
            best_value = std::max(best_value, 
                Player::alphabeta(node->next_moves[i], level - 1, alpha, beta, 
                    false));
            alpha = std::max(alpha, best_value);

            if (beta <= alpha)
            {
                break;
            }

        }

        return best_value;   
    }

    else
    {
        best_value = 99999;

        for (unsigned int i = 0; i <  node->next_moves.size(); i++)
        {
            best_value = std::min(best_value, alphabeta(node->next_moves[i], 
                level - 1, alpha, beta, true));
            beta = std::min(beta, best_value);
        }

        if (beta <= alpha)
        {
            break;
        }

        return best_value;
    }
}

int Player::get_score( Move * m )
{
	Board *new_board;
	new_board = board.copy();
    new_board->doMove(m, player_side);
    int score = new_board->count(player_side) 
            - new_board->count(opponent_side);
	if ((m->getX() == 7 && m->getY() == 7) ||
		(m->getX() == 0 && m->getY() == 0) ||
		(m->getX() == 0 && m->getY() == 7) ||
		(m->getX() == 7 && m->getY() == 0)  )
	{
		score *= 3;
	}

	if ((m->getX() == 7 && m->getY() == 6) ||
		(m->getX() == 6 && m->getY() == 7) ||
		(m->getX() == 0 && m->getY() == 1) ||
		(m->getX() == 1 && m->getY() == 0) ||
		(m->getX() == 6 && m->getY() == 0) ||
		(m->getX() == 7 && m->getY() == 1) ||
		(m->getX() == 0 && m->getY() == 6) ||
		(m->getX() == 1 && m->getY() == 7)  )
	{
		score *= -3;
	}
	return score;
}
