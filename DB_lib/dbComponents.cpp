//
// Created by winni on 2022-09-19.
//
# include <iostream>
# include "../DB_lib/dbComponents.h"
#include "../util/veryTrickyMethods.h"


using namespace std;

short Record::getRecordSize() {
    return this->field1.size() + this->field2.size() + this->field3.size();
}

void Record::destructTheRecordValue(string input) {

    this->endIndexField2 = fieldTwoEndIdx(input);

    vector<string> destructionResult = splitTheRecordContent(input);

    this->field1 = destructionResult[0];
    this->field2 = destructionResult[1];
    this->field3 = destructionResult[2];
}

//currentKeySize=recordContent.size+endPositionOfEachRecord.size*2+miscSize !!!!!
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
