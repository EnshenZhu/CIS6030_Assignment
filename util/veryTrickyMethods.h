//
// Created by winni on 2022-10-04.
//

#ifndef A1_SOLUTION_VERYTRICKYMETHODS_H
#define A1_SOLUTION_VERYTRICKYMETHODS_H

#endif //A1_SOLUTION_VERYTRICKYMETHODS_H

#include "iostream"
#include <vector>

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

vector<string> splitTheRecordContent(string input) {

    int aEndIndexField2 = fieldTwoEndIdx(input);

    vector<string> result;

    string aField1 = input.substr(0, 10);
    string aField2 = input.substr(10, aEndIndexField2 - 11);
    string aField3 = input.substr(aEndIndexField2 + 1);

    result.push_back(aField1);
    result.push_back(aField2);
    result.push_back(aField3);

    return result;
}