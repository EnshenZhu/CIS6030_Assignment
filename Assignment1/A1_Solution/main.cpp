#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>  // implement sorting
#include <typeinfo>
#include <bitset>
#include <cmath>

#include "util/utility.h"
#include "DB_lib/dbComponents.h"
#include "BplusTree_lib/BplusTree.h"

using namespace std;

int getSizeOfAllData(int numsOfRecords, vector<Record> allRecords) {
    int totalSize = 0;
    for (int idx = 0; idx < numsOfRecords; idx++) {
        totalSize += allRecords[idx].getRecordSize();
    }
    return totalSize;
}

void printShort(short input) {
    bitset<16> mybit(input);
    cout << mybit << endl;
}

void printChar(char input) {
    bitset<8> mybit(input);
    cout << mybit << endl;
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

void writeAllFile(string saveRoute, vector<BlockNode> allBlocks) {
    char singleLine[1024];

    // open the file in the write mode
    ofstream outfile(saveRoute);

    unsigned short thisNumOfRecord = allBlocks[0].numsOfRecords();
    singleLine[0] = thisNumOfRecord;
    outfile << singleLine[0]; // PLACE the thisNumOfRecord INTO the data file

    int singleLineIndexTracker = 1; // all jumpers will be recorded from the second element of the single line.
    for (short jumperIdx = 0; jumperIdx < allBlocks[0].numsOfRecords(); jumperIdx++) {
        unsigned short theRecordJumper = allBlocks[0].endPostionOfEachRecord[jumperIdx]; // subtract the jumper (end position of each record)

        // split each record jumper into two chars
        char low = theRecordJumper;
        theRecordJumper = theRecordJumper >> 8;
        char high = theRecordJumper;

        int plusOne_singleLineIndexTracker = singleLineIndexTracker + 1;

        singleLine[singleLineIndexTracker] = high;
        outfile << singleLine[singleLineIndexTracker];
        singleLine[plusOne_singleLineIndexTracker] = low;
        outfile << singleLine[plusOne_singleLineIndexTracker];

        singleLineIndexTracker += 2;
    }

    for (int contentIdx = 0; contentIdx <= allBlocks[0].recordContent.size(); contentIdx++) {
        singleLine[singleLineIndexTracker] = allBlocks[0].recordContent[contentIdx];
        outfile << singleLine[singleLineIndexTracker];
        singleLineIndexTracker += 1;
    }

    for (int restPart = singleLineIndexTracker; restPart < 1024; restPart++) {
        outfile << 0;
    }
//    bitset<8> mybit(x);
//    cout << mybit << endl;

//unsigned short thisN
//
//    singleLine[0] = x;
//    outfile << singleLine << endl;

    outfile.close();
};


void readAllFile(string saveRoute) {

    char value;

    fstream file(saveRoute, ios::in);
    if (!file) {
        cout << "Error opening file.";
        return;
    }

    // get nums of record
    file.seekg(0L, ios::beg);
    file.get(value);
    bitset<8> thisNumOfRecord_Binary(value);
//  cout << "This block has nums of record: " << thisNumOfRecord_Binary << endl;
    long thisNumOfRecord_Decimal = thisNumOfRecord_Binary.to_ulong();
    cout << "This block has nums of record: " << thisNumOfRecord_Decimal << endl;

    // get each record
    for (int idxOfRecord = 0; idxOfRecord < thisNumOfRecord_Decimal - 1; idxOfRecord++) {
        // get the end position of each record
        file.seekg(8L, ios::cur);
        file.get(value);

        bitset<8> thisEndPositonOfRecord_Binary(value);
        long thisEndPositonOfRecord_Decimal = thisEndPositonOfRecord_Binary.to_ulong();
        cout << thisEndPositonOfRecord_Decimal << "|";
    }


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
    int realAllBlockSize = calculateRealBlockSize(metaBlock);

    // get how many blocks we created
    int totalNumOfBlock = metaBlock.size();

    // get the total size of all data in bytes
    int sizeOfAllBlock = totalNumOfBlock * 1024;

    cout << "This script creates " << totalNumOfBlock << " blocks." << endl;
    cout << "The total size of all blocks are " << sizeOfAllBlock << " bytes." << endl;

    cout << "The space usage rate is " << ((realAllBlockSize + 0.0) / sizeOfAllBlock) * 100 << "%" << endl;

//    cout << metaBlock[0].recordContent << endl;


    // now we are going to store all blocks (with records) into the datafile
    string saveRoute = "../assets/dataFile.txt";
    writeAllFile(saveRoute, metaBlock);
    readAllFile(saveRoute);

    //do validation printing
//    for (int idx = 0; idx < metaBlock[0].numsOfRecords(); idx++) {
//        cout << metaBlock[0].endPostionOfEachRecord[idx] << " ";
//    }

    cout << endl;

    // verify the amount of records
//    int total = 0;
//    for (int idx = 0; idx < metaBlock.size(); idx++) {
//        total += metaBlock[idx].numsOfRecords();
//    }
//    cout << total << endl;

// start testing the tree
    BplusTree allNodes;
    allNodes.insertElm(5);
    allNodes.insertElm(15);
    allNodes.insertElm(25);
    allNodes.insertElm(35);
    allNodes.insertElm(45);
    allNodes.insertElm(55);
    allNodes.insertElm(40);
    allNodes.insertElm(30);
    allNodes.insertElm(20);
//allNodes.display(allNodes.getRoot());

//    allNodes.searchElm(15);


    return 0;
}