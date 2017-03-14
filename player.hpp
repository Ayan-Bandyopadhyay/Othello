#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
using namespace std;

struct Node
{
    Board board_state;
    int score;
    vector<Node *> next_moves;
    Move *move;
    Node(Board b, Move * m)
    {
		move = m;
        score = -9999999;
        board_state = b;
        next_moves = vector<Node *>();
    }

    /** @brief Inserts an board into the subtree rooted at this node.
    Does not allow duplicate entries.
    @return whether or not the entry was successfully inserted.
    */
    
    bool insert(Board b, Move * m)
    {
        Node * n = new Node(b, m);
        next_moves.push_back(n);
        return true;
    }

    bool generate_next(Side player_side)
    {
        Board *new_board = board_state.copy();

		Move *m;  
		
		for (int i = 0; i < 8; i++) 
		{
			for (int j = 0; j < 8; j++) 
			{
				m = new Move(i, j);
				if (new_board->checkMove(m, player_side))
				{
					
					Board *b = new_board->copy();
					b->doMove( m, player_side);
					Node *node = new Node(*b, m);
					next_moves.push_back(node);
				}
				else
				{
					delete m;
				}
			}
		}
    }
    
    
};

class DecisionTree
{
private:
    Node * root;
public:
	
	
    DecisionTree()
    {
        root = nullptr;
    }

    /** @brief Inserts an board into this tree.

    Does not allow duplicate entries.

    @return whether or not the entry was successfully inserted.

    */
    
    Node * get_root()
    {
		return root;
	}
	
    bool insert_root(Board b, Move * m)
    {
        if (root == nullptr)
        {
            root = new Node(b , m);
        }
    }

    void generate_layer(Side player_side, Node *current)
    {
        if (current->next_moves.size() == 0)
        {
            current->generate_next(player_side);
        }
    }

    void Deleter(Node * current)
    {
        if (current == nullptr)
        {
            return;
        }
        else
        {
            if( current->next_moves.size() == 0)
            {
                delete current;
                return;
            }
            
            vector<Node *> vec = vector<Node *>();
            
            for(unsigned int i = 0 ; i < current->next_moves.size(); i++)
            {
                vec.push_back( current->next_moves[i] );
            }
            
            for(unsigned int i = 0 ; i < vec.size(); i++)
            {
                Deleter(vec[i]);
            }
        }
    }
    ~DecisionTree()
    {
        Deleter(root);
    }
};

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
    



#endif
