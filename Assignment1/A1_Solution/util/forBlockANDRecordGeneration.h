//
// Created by WinnieCMZ on 2022-10-03.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>  // implement sorting
#include <typeinfo>
#include <bitset>
#include <cmath>

#include "../DB_lib/dbComponents.h"

#ifndef A1_SOLUTION_FORBLOCKANDRECORDGENERATION_H
#define A1_SOLUTION_FORBLOCKANDRECORDGENERATION_H

#endif //A1_SOLUTION_FORBLOCKANDRECORDGENERATION_H

using namespace std;

int getSizeOfAllData(int numsOfRecords, vector<Record> allRecords) {
    int totalSize = 0;
    for (int idx = 0; idx < numsOfRecords; idx++) {
        totalSize += allRecords[idx].getRecordSize();
    }
    return totalSize;
}

vector<Record> transferFileToRecord(string theRoute) {
    ifstream readFILE;
    readFILE.open(theRoute);

    if (!readFILE.is_open()) {
        cout << "Error on file reading!" << endl;
        exit(EXIT_FAILURE);
    }

    vector<Record> allRecords; // create a vector of records
    string textInput;

    while (getline(readFILE, textInput)) {
        // Output the text from the file
        allRecords.push_back(Record());
        Record &newRecord = allRecords.back();

        newRecord.destructTheRecordValue(textInput); // convert the textInput into the field1. field2 and field3
    }

    return allRecords;
}

// store records into blocks
vector<BlockNode> storeRecordToBlocks(int numsOfRecords, vector<Record> allRecords) {

    vector<BlockNode> allBlocks; // create a vector of records

    int indexOfBlockNode = 0; // track the index of the Block Node
    int indexOfRecord = 0; // track the index of the Record

    while (indexOfRecord < numsOfRecords) {

        allBlocks.push_back(BlockNode());
        BlockNode &newBlockNode = allBlocks.back();

        int currentNumsOfRecordInTheBlock = 0;
        //        newBlockNode.endPostionOfEachRecord.push_back(
//                0); // a new block will place the record started from the index=0 in the recordContent

        while ((indexOfRecord < numsOfRecords) &&
               (newBlockNode.currentSize() + allRecords[indexOfRecord].getRecordSize() <=
                newBlockNode.maxCapacity)) {  // we add another indexOfRecord <= numsOfRecords to prevent the over leak at the last block

            string contentOfCurrentRecord = allRecords[indexOfRecord].field1 + allRecords[indexOfRecord].field2 +
                                            allRecords[indexOfRecord].field3;
            newBlockNode.recordContent.append(contentOfCurrentRecord); // add a new record to the block

            if (newBlockNode.endPostionOfEachRecord.size() == 0) {
                newBlockNode.endPostionOfEachRecord.push_back(contentOfCurrentRecord.size());
            } else {
                newBlockNode.endPostionOfEachRecord.push_back(contentOfCurrentRecord.size() +
                                                              newBlockNode.endPostionOfEachRecord[
                                                                      currentNumsOfRecordInTheBlock - 1]);
            }

            currentNumsOfRecordInTheBlock = newBlockNode.endPostionOfEachRecord.size(); // temporarily store the current numbers of records inside this block
//            newBlockNode.endPostionOfEachRecord.push_back(
//                    newBlockNode.endPostionOfEachRecord[currentNumsOfRecordInTheBlock - 1] +
//                    contentOfCurrentRecord.size()); // update the endPostionOfEachRecord

            indexOfRecord++; // move to the next record
        }

//        cout << "Block " << indexOfBlockNode << " has " << newBlockNode.numsOfRecords() << " records " << endl;
//        cout << "Block " << indexOfBlockNode << " has the size of " << newBlockNode.currentSize() << endl;
//        cout << "Block " << indexOfBlockNode << " has the list " << int(newBlockNode.endPostionOfEachRecord[1])
//             << endl;

        indexOfBlockNode++; // move to the next node

    }

    // 1) should I do the following?
    // create a new block node

    // while the block is not full after putting into a new record
    // append the pointer of the record to the block

    // Recall that each records inside one block need a

    // 2) But how could me so later insertion and deletion

    return allBlocks;
}

int calculateRealBlockSize(vector<BlockNode> allBlock) {
    int realSize = 0;

    for (short idx = 0; idx <= allBlock.size(); idx++) {
        realSize += allBlock[idx].currentSize();
    }

    return realSize;
}