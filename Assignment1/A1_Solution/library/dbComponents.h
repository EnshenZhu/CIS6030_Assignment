//
// Created by winni on 2022-09-19.
//

#ifndef A1_SOLUTION_DBCOMPONENTS_H
#define A1_SOLUTION_DBCOMPONENTS_H

#include <vector>
using namespace std;

class Record {
public:
    string field1;
    string field2;
    string field3;
    int endIndexField2;
};

class BlockListNode {

public:
    short static const maxCapacity=1024;
    short currentSize;
    BlockListNode *nextBlockNode;
};


#endif //A1_SOLUTION_DBCOMPONENTS_H
