//
// Created by winni on 2022-10-04.
//

#ifndef A1_SOLUTION_FORBPTREEBUILD_H
#define A1_SOLUTION_FORBPTREEBUILD_H

#endif //A1_SOLUTION_FORBPTREEBUILD_H

# include "iostream"
#include "../DB_lib/dbComponents.h"
#include "../newBPTree_lib/newBPTree.h"
//#include "veryTrickyMethods.h"

using namespace std;

void buildDataFileIntoBPTree(string fileSaveRoute, vector<BlockNode> allBlock) {

    vector<newTreeNode> TreeNodeList;

    int totalBlockNum = 17;
    for (short idxOfBlock = 0; idxOfBlock < totalBlockNum; idxOfBlock++) {
        for (short relativeIdxOfRecord = 0;
             relativeIdxOfRecord < allBlock[idxOfBlock].numsOfRecords(); relativeIdxOfRecord++) {
            string rawRecordStringValue = readACertainRecordInBlock(fileSaveRoute, idxOfBlock, relativeIdxOfRecord);

            cout << rawRecordStringValue << endl;
            cout << endl;

//            vector<string> recordSplitResult = splitTheRecordContent(rawRecordStringValue);
        }
    }
}