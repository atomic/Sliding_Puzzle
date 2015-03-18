#ifndef ANODE_H
#define ANODE_H

/**
  * Changed filename to anode, instead of Node.h or node.h
  * conflicts with Yekun's node.h file, see #ifndef NODE_H
  */

#include <iostream>
#include <vector>
#include <string>
#include "board.h"
#include "functions.h"

using namespace std;

namespace Alex
{
//  No code written for equal operator (=)
class Node
{
public:
    Node(board brd);
    ~Node();

    bool solve();
    //  solves the board
    //  Post-condition:
    //      _solution now has the moves required to reach a solved board
    //      _steps now has the number of moves required to reach a solved board
    //      allocated memory is freed up

    string solution();
    //  returns the moves required to reach a solved board

    int steps();
    //  returns the number of steps to reach the solution

    void display();
    //  displays _board to console


private:
    board _board;
    string _solution;
    vector<Node*> _nextMoves;
    int _steps;

    string prevMove();
    //  returns _board's previous move as a string

    bool nextMove();
    //  RECURSIVE BOARD SOLVER
    //  Post-condition:
    //      The tree of board combinations has increased by a depth of 1
    //      for all next possible moves

    void Delete(Node& v);
    //  RECURSIVE DELETE
    //  Post-condition:
    //      The tree of board combinations is deleted
    //      and the memory is freed up
};

Node::Node(board brd)
{
    _board = brd;
    _solution = "";
    _steps = 0;
}

Node::~Node()
{
    if (_nextMoves.size() != 0)
        Delete(*this);
}

bool Node::nextMove()
{
    int size = _nextMoves.size();
    //  BASE CASE
    if (size == 0)
    {
        //  CREATES NEXT MOVES FOR CURRENT BOARD
        for (int i = 0; i < MAX_MOVES; i++)
        {
            DIR d = getDir(i);

            if (_board.canMove(d) && d != opposite(_board._prevMove))
            {
                DIR prevMove = _board._prevMove;
                _board.move(d);

                Node* next = new Node(_board);
                _nextMoves.push_back(next);

                if (_board.isSolved())
                {
                    _steps++;
                    _solution += dirToChar(d);
                    _board._prevMove = prevMove;
                    return true;
                }

                _board.move(opposite(d));
                _board._prevMove = prevMove;
            }
        }
    }

    //  RECURSION
    else
    {
        //  CALLS NEXT MOVE FOR ALL BOARDS
        for (int i = 0; i < size; i++)
            if (_nextMoves[i]->nextMove())
            {
                _steps = _nextMoves[i]->steps() + 1;
                _solution = _nextMoves[i]->prevMove() + _nextMoves[i]->_solution;
                return true;
            }
    }

    return false;
}

void Node::Delete(Node& v)
{
    int size = v._nextMoves.size();

    for (int i = 0; i < size; i++)
    {
        if (v._nextMoves[i]->_nextMoves.size() == 0)
        {
            delete v._nextMoves[i];
            v._nextMoves[i] = NULL;
        }
        else
            Delete(*(v._nextMoves[i]));
    }

    v._nextMoves.clear();
}

bool Node::solve()
{
    while(!nextMove());

    //not need
    //display();
    cout << "Solution: " << _solution << endl;
    cout << "Number of steps: " << _steps << endl << endl;

    Delete(*this);
}

string Node::prevMove()
{
    return dirToChar(_board._prevMove);
}

string Node::solution()
{
    return _solution;
}

int Node::steps()
{
    return _steps;
}


void Node::display()
{
    _board.display();
}
    
} /* Alex */

#endif // ANODE_H
