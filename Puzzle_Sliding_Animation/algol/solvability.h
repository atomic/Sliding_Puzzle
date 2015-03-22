/**
 * solvability.h
 * Copyright (C) 2015 Tony Lim <atomictheorist@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SOLVABILITY_H
#define SOLVABILITY_H
#include <string>
#include <iostream>

using namespace std;

namespace Algol {

int toInt(const char& ch) {return ch - '0';}

int inversion(const char& c, const string& comb)
{
    if(c == '1' || c == '0') return 0;
    int N = comb.find(c); // ending pos
    int less_count = 0;
    for (int j = 0; j < N; ++j)
        if(toInt(comb[j]) < toInt(comb[N]) && comb[j] != '0') less_count++; // assuming comb is unique from 0-8
    // at pos i, comb[i] should have comb[i] - 1 numbers less than it, 
    return toInt(c) - 1 - less_count;
}

/* 
 * @brief Takes a sequence of number in string and return whether it's solvable
 * @param string 
 */
bool isSolvable(const string& combination) {
    int total_inversion = 0;
    for (auto& i : combination) {
        total_inversion += inversion(i, combination);
    }
    //cout << "debug, total_inversion of " << combination << " : " << total_inversion << endl;
    return total_inversion % 2 == 0 ? true : false;
}

}

#endif /* !SOLVABILITY_H */
