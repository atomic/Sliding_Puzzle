/**
 * main.cpp
 * Copyright (C) 2015 Tony Lim <atomictheorist@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <cstdlib>
#include "solvability.h"

using namespace std;
using namespace Algol;

int main()
{
    //string testStr("123456780");
    //isSolvable(testStr);
    string testStr2("528417306");
    cout << isSolvable(testStr2) << endl;
}
