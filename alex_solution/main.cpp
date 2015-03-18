#include <iostream>
#include <ctime>
#include <cstdlib>
#include "board.h"
#include "Node.h"

using namespace std;

void testMove();
void play();
//  Allows you to play a board
void eatLine();
//  Eats buffer until new line character is reached

int main()
{
    //  WITHOUT SETUP
    srand(time(NULL));
    //board b(3);
    //b.randomize();

    //Node randomNode(b);
    //randomNode.solve();


    //  WITH SETUP
    cout << endl << endl;
    cout << "Enter sequence : " << endl;
    string seq; cin >> seq;

    //Node n(board(3, "876543021"));
    //Node n(board(3, "426871035"));
    Node n(board(3, seq.c_str()));
    n.solve();


    //  AFTER SOLVE FUNCTIONALITY
    //cout << endl << endl;
    //cout << "==========" << endl;
    //cout << "in main" << endl
         //<< "==========" << endl;
    //n.display();
    //cout << "solution: " << n.solution() << endl;
    //cout << "steps: " << n.steps() << endl << endl;
    //cout << "==========" << endl << endl;
    return 0;
}

void play()
{
    int rowSize;
    string initBoard;

    cout << "What is the row size? ";
    cin >> rowSize;
    eatLine();

    cout << endl << endl << "What is the initial board?(ie. 12356780) ";
    getline(cin, initBoard);

    board b(rowSize, initBoard);

    int nextMove;
    char nextMoveChar;
    while (!b.isSolved())
    {
        b.display();

        do
        {
            cout << endl << endl << "Next move(Up = u, Down = d, Left = l, Right = r): ";
            cin >> nextMoveChar;
            eatLine();
        } while (!valid(nextMoveChar));

        nextMove = charToInt(nextMoveChar);

        DIR d = getDir(nextMove);

        if (b.canMove(d))
            b.move(d);
        else
        {
            cout <<  endl << endl << "board can not move in that direction!";
            cout << endl << "Press enter to continue";
            getline(cin, initBoard);
        }
        system("cls");
//        b.display();
    }
}

void eatLine()
{
    char c;
    while (c != '\n')
    {
        cin.get(c);
    }
}
