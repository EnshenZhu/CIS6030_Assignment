//
// Created by winni on 2022-09-19.
//

#ifndef A1_SOLUTION_DATABASECOMPONENTS_H
#define A1_SOLUTION_DATABASECOMPONENTS_H

#include <vector>

class Record {
public:
    string field1;
    string field2;
    string field3;
    int endIndexField2;

    Record(string aField1,string aField2,string aField3);
};

class Block {
    vector records;
    Block *nextBlock;
};


#endif //A1_SOLUTION_DATABASECOMPONENTS_H
