//
// Created by winni on 2022-10-04.
//

#ifndef A1_SOLUTION_FORBPTREEBUILD_H
#define A1_SOLUTION_FORBPTREEBUILD_H

#endif //A1_SOLUTION_FORBPTREEBUILD_H

#include "../DB_lib/dbComponents.h"
#include "../newBPTree/ssBPTree.h"
#include "forDataFileCRUD.h"
#include "iostream"
#include <vector>

using namespace std;


const static int m_value = 8;

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

int convertBlockRecordIdx_to_anInt(short IdxOfBlock, short relativeIdxOfRecord) {
    return IdxOfBlock * 100 + relativeIdxOfRecord;
}

vector<int> convertAnInt_to_BlockRecordIdx(int inputInt) {
    vector<int> result;
    int blockIdx = floor(inputInt / 100);
    int recordIdx = inputInt - blockIdx * 100;

    result.push_back(blockIdx);
    result.push_back(recordIdx);

    return result;

}

void buildDataFileIntoBPTree(string fileSaveRoute, vector<BlockNode> allBlock, ssBPTree aBPTree) {

    for (int idxOfBlock = 0; idxOfBlock < allBlock.size(); idxOfBlock++) {

        for (int relativeIdxOfRecord = 0;
             relativeIdxOfRecord < allBlock[idxOfBlock].numsOfRecords(); relativeIdxOfRecord++) {
            string rawRecordStringValue = readACertainRecordInBlock(fileSaveRoute, idxOfBlock, relativeIdxOfRecord);

            // get the split record value
            vector<string> recordSplitResult = splitTheRecordContent_BPbackup(rawRecordStringValue);

            string aKey_inFieldOne = recordSplitResult[0];
            string aFieldTwoAndThree = recordSplitResult[1] + recordSplitResult[2];
            int aValue_inLocationInt = convertBlockRecordIdx_to_anInt(idxOfBlock, relativeIdxOfRecord);

            aBPTree.ramInsertElm(aKey_inFieldOne, aValue_inLocationInt);

        }
    }

    cout << "The initial data has been stored into the BP Tree" << endl;
}


//void convertKeyStringTo_NineUnit_Array(string input, char* buffer){
//
//    int start = 0;
//    int end = 9;
//    for (int i = start; i<end; ++i){
//        *(buffer+i) = input[i]; // 拿盆接满水
//    }
//    return;
//}