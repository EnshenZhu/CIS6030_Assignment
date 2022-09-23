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
    short endIndexField2;
};

// build a LinkedList for the Block Class
class BlockNode {

public:
    short static const maxCapacity=1024;
    short currentSize;
    BlockNode *nextBlockNode= nullptr; // specify the next pointer for the next block node

    // each block has a vector list to store all pointers
    vector<Record*> pointerOfRecords;
};


#endif //A1_SOLUTION_DBCOMPONENTS_H
