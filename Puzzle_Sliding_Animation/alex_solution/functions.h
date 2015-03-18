#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

using namespace std;

namespace Alex {

//  HELPER FUNCTIONS
enum DIR {UP, DOWN, LEFT, RIGHT, NO_DIR};

const int MAX_MOVES = 4;

//  returns type DIR from type int
DIR getDir(int dir)
{
    DIR d = static_cast<DIR> (dir);

    return d;
}

//  returns opposite direction of dir
DIR opposite(DIR dir)
{
    switch (dir)
    {
    case UP:
        return DOWN;
    case DOWN:
        return UP;
    case LEFT:
        return RIGHT;
    case RIGHT:
        return LEFT;
    default:
        return NO_DIR;
    }
}

//  returns string equivalent of dir
string dirToChar(DIR dir)
{
    switch (dir)
    {
    case UP:
        return "U";
    case DOWN:
        return "D";
    case LEFT:
        return "L";
    case RIGHT:
        return "R";
    default:
        return "!ERROR!";
    }
}

//  swap two integers with each other
void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

bool valid(char dir)
{
    switch (dir)
    {
    case 'U':
    case 'u':
    case 'D':
    case 'd':
    case 'L':
    case 'l':
    case 'R':
    case 'r':
        return true;
    default:
        return false;
    }
}

int charToInt(char dir)
{
    switch (dir)
    {
    case 'U':
    case 'u':
        return UP;
        //return static_case<int>(UP);
    case 'D':
    case 'd':
        return DOWN;
        //return static_case<int>(DOWN);
    case 'L':
    case 'l':
        return LEFT;
        //return static_case<int>(LEFT);
    case 'R':
    case 'r':
        return RIGHT;
        //return static_case<int>(RIGHT);
    default:
        return NO_DIR;
    }
}

}

#endif // FUNCTIONS_H
