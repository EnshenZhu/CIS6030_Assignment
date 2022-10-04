//
// Created by winni on 2022-09-19.
//
# include <iostream>
# include "./dbComponents.h"

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

short Record::getRecordSize() {
    return this->field1.size() + this->field2.size() + this->field3.size();
}

void Record::destructTheRecordValue(std::string input) {

    this->endIndexField2 = fieldTwoEndIdx(input);

    this->field1 = input.substr(0, 10);
    this->field2 = input.substr(10, this->endIndexField2 - 11);
    this->field3 = input.substr(this->endIndexField2 + 1);
}

//currentKeySize=recordContent.size+endPostionOfEachRecord.size*2+miscSize !!!!!
short BlockNode::currentSize() {
    return this->recordContent.size() + this->endPostionOfEachRecord.size() * 2 + this->miscSize;
}

short BlockNode::numsOfRecords() {
    return this->endPostionOfEachRecord.size();
}

short BlockNode::sizeOfHead() {
    return this->numsOfRecords() * 2 + this->miscSize;
}


#include "dbComponents.h"
