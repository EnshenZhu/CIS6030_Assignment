//
// Created by winni on 2022-10-04.
//

#ifndef A1_SOLUTION_FORBPTREEBUILD_H
#define A1_SOLUTION_FORBPTREEBUILD_H

#endif //A1_SOLUTION_FORBPTREEBUILD_H

#include "iostream"
#include "../DB_lib/dbComponents.h"
#include "../newBPTree_lib/newBPTree.h"

using namespace std;

int fieldTwoEndIdx_BPbackup(string aString) {
    short count = 3;
    for (short idx = 0; idx < aString.size(); idx++) {
        if (isspace(aString[idx])) {
            count -= 1;
            if (count == 0) return idx;
        }
    }
    return -1;
}

vector<string> splitTheRecordContent_BPbackup(string input) {

    int aEndIndexField2 = fieldTwoEndIdx_BPbackup(input);

    vector<string> result;

    string aField1 = input.substr(0, 10);
    string aField2 = input.substr(10, aEndIndexField2 - 11);
    string aField3 = input.substr(aEndIndexField2 + 1);

    result.push_back(aField1);
    result.push_back(aField2);
    result.push_back(aField3);

    return result;
}

void buildDataFileIntoBPTree(string fileSaveRoute, vector<BlockNode> allBlock) {

    vector<newTreeNode> TreeNodeList;

    int totalBlockNum = 17;
    for (short idxOfBlock = 0; idxOfBlock < totalBlockNum; idxOfBlock++) {
        for (short relativeIdxOfRecord = 0;
             relativeIdxOfRecord < allBlock[idxOfBlock].numsOfRecords(); relativeIdxOfRecord++) {
            string rawRecordStringValue = readACertainRecordInBlock(fileSaveRoute, idxOfBlock, relativeIdxOfRecord);

            // get the split record value
            vector<string> recordSplitResult = splitTheRecordContent_BPbackup(rawRecordStringValue);
            string aFieldOne = recordSplitResult[0];
            string aFieldTwoAndThree = recordSplitResult[1] + recordSplitResult[2];
        }
    }
}