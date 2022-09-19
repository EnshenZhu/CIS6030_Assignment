//
// Created by winni on 2022-09-19.
//
# include "./databaseComponents.h"

Record::Record(string aField1,string aField2,string aField3) {
    field1 = aField1;
    field2 = aField2;
    field3 = aField3;

    endIndexField2=field1.length()+field2.length();
}

#include "databaseComponents.h"
