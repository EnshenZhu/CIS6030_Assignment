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

    // get the size of the current Record
    short getRecordSize();

    void destructTheRecordValue(string input);
};

// build a LinkedList for the Block Class
class BlockNode {

public:
    short static const maxCapacity = 1024;
    short static const miscSize = 2; // default miscellaneous size of a block (=char(numsOfRecord)+char(sizeOfHead))
    short currentSize();

    BlockNode *previousBlockNode = nullptr; // specify the previous pointer for the next block node
    BlockNode *nextBlockNode = nullptr; // specify the next pointer for the next block node

    // each block has a vector list to store all pointers
    // vector<Record *> pointerOfRecords; // 3) should I write like this?

    vector<short> endPostionOfEachRecord; // recall that each <short> element takes two bits
    string recordContent;

    short numsOfRecords(); // to record the number of the record; char(the_value)=1
    short sizeOfHead(); // to record the size of the block head; char(the_value)=1

};


#endif //A1_SOLUTION_DBCOMPONENTS_H
