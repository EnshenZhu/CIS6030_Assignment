//
// Created by winni on 2022-10-04.
//

#ifndef A1_SOLUTION_VERYTRICKYMETHODS_H
#define A1_SOLUTION_VERYTRICKYMETHODS_H

#endif //A1_SOLUTION_VERYTRICKYMETHODS_H

#include "iostream"

using namespace std;

int fieldTwoEndIdx(string aString) {
    short count = 3;
    for (short idx = 0; idx < aString.size(); idx++) {
        if (isspace(aString[idx])) {
            count -= 1;
            if (count == 0) return idx;
        }
    }
    return -1;
}