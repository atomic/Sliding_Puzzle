#include <iostream>
#include "sliding_puzzle.h"

using namespace std;

int main()
{
    string prompt;
    cout << "enter sequence to solve : ";
    cin >> prompt;
    Sliding_Puzzle puzzle(prompt.c_str());
    puzzle.play();
    cout<<endl;
}

