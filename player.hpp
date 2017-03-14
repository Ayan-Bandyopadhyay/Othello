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

struct Node
{
	Board board_state;
	int score;
	vector<Node> next_moves;
	Node(Board b)
	{
		score = -9999999;
		board_state = b;
		next_moves = vector<Node *>();
	}

	/** @brief Inserts an board into the subtree rooted at this node.
	Does not allow duplicate entries.
	@return whether or not the entry was successfully inserted.
	*/
	bool insert(Board b)
	{
		next_moves.push_back( Node(b));
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
    bool insert(Board b)
    {
		if (root == nullptr)
		{
			root = new Node(b);
		}
        return root->insert(val);
    }

     /** @brief Finds an integer in this tree.

    @return whether or not the entry exists in this tree.

    */
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
			
			for(int i = 0 ; i < current->next_moves.size(); i++)
			{
				vec.push_back( current->next_moves.size() );
			}
			
			for(int i = 0 ; i < vec.size(); i++)
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
#endif
