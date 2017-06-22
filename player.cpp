#include "player.hpp"
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

int Player::minimax(Board *board_node, int depth, Side side) 
{   
    Board *new_board;
    int best_value, v;

    if (depth == 0 || !board_node->hasMoves(side)) {
        int player_stones = board_node->count(player_side);
        int opponent_stones = board_node->count(opponent_side);
        return player_stones - opponent_stones;
    }

    vector<Move *> possible_moves;
    Move *m;
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            m = new Move(i, j);
            if (board_node->checkMove(m, player_side))
            {
                possible_moves.push_back(m);
            }
            else
            {
                delete m;
            }
        }
    }

    if (side != player_side) {
        int best_value = -999999;
        for (unsigned int i = 0; i < possible_moves.size(); i++) {
            new_board = board_node->copy();
            new_board->doMove(possible_moves[i], side);
            v = minimax(new_board, depth - 1, opponent_side);
            best_value = max(best_value, v);
        }
    }
    else {
        best_value = 999999;
        for (unsigned int i = 0; i < possible_moves.size(); i++) {
            new_board = board_node->copy();
            new_board->doMove(possible_moves[i], side);
            v = minimax(new_board, depth - 1, opponent_side);
            best_value = max(best_value, v);
        }
    }
    return best_value;
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
    /* Make the opponent's move. */
    if (opponentsMove != nullptr) {
        board.doMove(opponentsMove, opponent_side);
    }

    /* Find all of the possible moves for the player. */
    vector<Move *> possible_moves;
    Move *m;
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

    int result;
    int best_result;
    Board *new_board;
    Move *best_move;

    new_board = board.copy();
    new_board->doMove(possible_moves[0], player_side);
    best_result = minimax(new_board, 2, player_side);
    best_move = possible_moves[0];

    for (unsigned int i = 1; i < possible_moves.size(); i++) {
        new_board = board.copy();
        new_board->doMove(possible_moves[i], player_side);
        result = minimax(new_board, 2, player_side);
        if (result > best_result) {
            best_result = result;
            best_move = possible_moves[i];
        }
    }

    board.doMove(best_move, player_side);

    return best_move;
    
/*
    if ( opponentsMove != nullptr)
    {
        board.doMove( opponentsMove, opponent_side);
    }
    
    Move *m;
    vector<Move*> possible_moves;
    int score = -8;
    int new_score = -9;
	Move * best_move;
    
    
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
    

    if (!board.hasMoves(player_side))
    {
        m = nullptr;
    }
    
    best_move = possible_moves[0];
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
    
    */
    
    /**

    // if (testingMinimax)
    // {

        std::cerr << "test_minimax" << std::endl;
        // Constructing the tree.
        Board *new_board;
        new_board = board.copy();
        DecisionTree tree;

        tree.insert_root(*new_board, nullptr);

        tree.generate_layer(player_side, player_side, opponent_side, 
            tree.get_root());

        for (unsigned int i = 0; i < tree.get_root()->next_moves.size(); i++)
        {   
            tree.generate_layer(opponent_side, player_side, opponent_side,
                                     tree.get_root()->next_moves[i]);
        }
        
        std::cerr << "size of root()->next_moves" << tree.get_root()->next_moves.size() 
                    << std::endl;
        for (unsigned int i = 0; i < tree.get_root()->next_moves.size(); i++)
        {   

            Node * n = tree.get_root()->next_moves[i];
            n->score = n->next_moves[0]->score;
            for (unsigned int j = 0; j < n->next_moves.size(); j++ )
            {
                if(n->next_moves[j]->score < n->score)
                {
                    n->score = n->next_moves[j]->score;
                }
            }
        }

        Node * max = tree.get_root()->next_moves[0];
        for(unsigned int i = 0; i < tree.get_root()->next_moves.size(); i++)
        {
            if(tree.get_root()->next_moves[i]->score > max->score)
            {
                max = tree.get_root()->next_moves[i];
                std::cerr << "i = " << i <<std::endl;
            }
        }
        board.doMove(max->move, player_side);
        return max->move;

    
    */
    
}

int Player::get_score(Move * m)
{
	/*Board *new_board;
	new_board = board.copy();
    new_board->doMove(m, player_side);
    
    // find opponents moves
    vector<Move*> opponents_moves;
    Move * op_move;
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            op_move = new Move(i, j);
            if (new_board->checkMove(op_move, player_side))
            {
                opponents_moves.push_back(op_move);
            }
            else
            {
                delete op_move;
            }
        }
    }
    
    int final_score = 99999;
    
    for(unsigned int i = 0; i < opponents_moves.size(); i++)
	{
		Board * next_board = new_board->copy();
		next_board->doMove( opponents_moves[i], opponent_side);
		
		int score = next_board->count(player_side) 
				- next_board->count(opponent_side);
				
		if ((opponents_moves[i]->getX() == 7 && opponents_moves[i]->getY() == 7) ||
			(opponents_moves[i]->getX() == 0 && opponents_moves[i]->getY() == 0) ||
			(opponents_moves[i]->getX() == 0 && opponents_moves[i]->getY() == 7) ||
			(opponents_moves[i]->getX() == 7 && opponents_moves[i]->getY() == 0)  )
		{
			score *= -3;
		}

		if ((opponents_moves[i]->getX() == 7 && opponents_moves[i]->getY() == 6) ||
			(opponents_moves[i]->getX() == 6 && opponents_moves[i]->getY() == 7) ||
			(opponents_moves[i]->getX() == 0 && opponents_moves[i]->getY() == 1) ||
			(opponents_moves[i]->getX() == 1 && opponents_moves[i]->getY() == 0) ||
			(opponents_moves[i]->getX() == 6 && opponents_moves[i]->getY() == 0) ||
			(opponents_moves[i]->getX() == 7 && opponents_moves[i]->getY() == 1) ||
			(opponents_moves[i]->getX() == 0 && opponents_moves[i]->getY() == 6) ||
			(opponents_moves[i]->getX() == 1 && opponents_moves[i]->getY() == 7)  )
		{
			score *= 3;
		}
		
		if (score < final_score)
		{
			final_score = score;
		}
		delete next_board;
	}
	delete new_board;
	return final_score;*/
}

void Player::set_board(Board *new_board) {
    board = *new_board;
}
