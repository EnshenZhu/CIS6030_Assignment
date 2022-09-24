//
// Created by winni on 2022-09-19.
//
# include <iostream>
# include "./dbComponents.h"

using namespace std;

short Record::getRecordSize() {
    return this->field1.size()+this->field2.size()+this->field3.size();
}

//currentSize=recordContent.size+startPositionOfEachRecord.size*2+miscSize !!!!!
short BlockNode::currentSize() {
    return this->recordContent.size()+startPositionOfEachRecord.size()*2+miscSize;
}

short BlockNode::numsOfRecords() {
    return this->startPositionOfEachRecord.size();
}


#include "dbComponents.h"
