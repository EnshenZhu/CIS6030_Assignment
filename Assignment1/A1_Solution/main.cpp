#include <iostream>
#include "dblibrary/dbComponents.h"
#include <fstream>
#include <cstdlib>
#include <algorithm>  // implement sorting

using namespace std;

int getSizeOfAllData(int numsOfRecords, vector<Record> allRecords) {
    int totalSize = 0;
    for (int idx = 0; idx < numsOfRecords; idx++) {
        totalSize += allRecords[idx].getRecordSize();
    }
    return totalSize;
}

int fieldTwoEndIdx(string aString) {
    int count = 3;
    for (int idx = 0; idx < aString.size(); idx++) {
        if (isspace(aString[idx])) {
            count -= 1;
            if (count == 0) return idx;
        }
    }
    return -1;
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

        newRecord.endIndexField2 = fieldTwoEndIdx(textInput);

        newRecord.field1 = textInput.substr(0, 9);
        newRecord.field2 = textInput.substr(10, newRecord.endIndexField2 - 10);
        newRecord.field3 = textInput.substr(newRecord.endIndexField2 + 1);
    }

    return allRecords;
}

// start from here!!!
vector<BlockNode> storeRecordToBlocks(int numsOfRecords, vector<Record> allRecords) {

    vector<BlockNode> allBlocks; // create a vector of records

    int indexOfBlockNode = 0; // track the index of the Block Node
    int indexOfRecord = 0; // track the index of the Record
    short newRecordMiscSize = 2; // this is the extra default size when adding a new record into a block

    while (indexOfRecord <= numsOfRecords) {

        allBlocks.push_back(BlockNode());
        BlockNode &newBlockNode = allBlocks.back();
        newBlockNode.startPositionOfEachRecord.push_back(
                0); // a new block will place the record started from the index=0 in the recordContent

        while ((indexOfRecord <= numsOfRecords) &&
               (newBlockNode.currentSize() + allRecords[indexOfRecord].getRecordSize() + newRecordMiscSize <=
                newBlockNode.maxCapacity)) {  // we add another indexOfRecord <= numsOfRecords to prevent the over leak at the last block

            string contentOfCurrentRecord = allRecords[indexOfRecord].field1 + allRecords[indexOfRecord].field2 +
                                            allRecords[indexOfRecord].field3;
            newBlockNode.recordContent.append(contentOfCurrentRecord); // add a new record to the block

            int currentNumsOfRecordInTheBlock = newBlockNode.startPositionOfEachRecord.size(); // temporarily store the current numbers of records inside this block
            newBlockNode.startPositionOfEachRecord.push_back(
                    newBlockNode.startPositionOfEachRecord[currentNumsOfRecordInTheBlock - 1] +
                    contentOfCurrentRecord.size()); // update the startPositionOfEachRecord

            indexOfRecord += 1; // move to the next record

        }

//        cout << "Block " << indexOfBlockNode << " has " << newBlockNode.numsOfRecords() << " records " << endl;
//        cout << "Block " << indexOfBlockNode << " has the size of " << newBlockNode.currentSize() << endl;
//        cout << "Block " << indexOfBlockNode << " has the list " << int(newBlockNode.startPositionOfEachRecord[1])
//             << endl;

        indexOfBlockNode += 1; // move to the next node

    }


    // 1) should I do the following?
    // create a new block node

    // while the block is not full after putting into a new record
    // append the pointer of the record to the block

    // Recall that each records inside one block need a

    // 2) But how could me so later insertion and deletion

    return allBlocks;
}

int main() {
    // config the raw input data location
    string FileRoute = "../assets/A1_data.txt";
    vector<Record> metaRecord = transferFileToRecord(FileRoute);

    // sorting all records base on their field 1
    sort(metaRecord.begin(),
         metaRecord.end(),
         [](const Record &lhs, const Record &rhs) {
             return lhs.field1 < rhs.field1;
         });

    // get how many records in total that need to be store into blocks
    int totalNumOfRecords = metaRecord.size();

    //get the total size of all data in bytes
    int sizeOfAllRecord = getSizeOfAllData(totalNumOfRecords, metaRecord);

//    cout << metaRecord[7].field1 << endl;
//    cout << metaRecord[7].field2 << endl;
//    cout << metaRecord[7].field3 << endl;
//
//    cout << metaRecord[0].getRecordSize() << endl;

    cout << "This script creates " << totalNumOfRecords << " records." << endl;
    cout << "The total size of all records are " << sizeOfAllRecord << " bytes." << endl;

    vector<BlockNode> metaBlock = storeRecordToBlocks(totalNumOfRecords, metaRecord);

//    vector<int> metaBlock={1,1,1};

    // get how many blocks we created
    int totalNumOfBlock = metaBlock.size();

    //get the total size of all data in bytes
    int sizeOfAllBlock = totalNumOfBlock * 1024;

    cout << "This script creates " << totalNumOfBlock << " blocks." << endl;
    cout << "The total size of all blocks are " << sizeOfAllBlock << " bytes." << endl;

    cout << "The space usage rate is " << (sizeOfAllRecord + 0.0) / sizeOfAllBlock << endl;

    for (int idx = 0; idx < metaBlock[0].numsOfRecords(); idx++) {
        cout << metaBlock[0].startPositionOfEachRecord[idx] << " ";
    }
    cout << endl;

    cout << metaBlock[0].recordContent[0] << endl;

    return 0;
}