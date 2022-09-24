//
// Created by winni on 2022-09-19.
//
# include <iostream>
# include "./dbComponents.h"

using namespace std;

short Record::getRecordSize() {
    return this->field1.size()+this->field2.size()+this->field3.size();
}



#include "dbComponents.h"
