#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>  // implement sorting
#include <typeinfo>
#include <bitset>
#include <cmath>

#include "util//forBlockANDRecordGeneration.h"
#include "util/forDataFileCRUD.h"
#include "DB_lib/dbComponents.h"
#include "BplusTree_lib/BplusTree.h"
#include "util/forBPTreeBuild.h"

using namespace std;



//void printShort(short input) {
//    bitset<16> mybit(input);
//    cout << mybit << endl;
//}
//
//void printChar(char input) {
//    bitset<8> mybit(input);
//    cout << mybit << endl;
//}



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

    // now we are going to store all blocks (with records) into the datafile
    string saveRoute = "../assets/dataFile.txt";
    writAllFile(saveRoute, metaBlock);

    int quest_blockIdx = 0;
    int quest_relativeRecordIdx = 0;
    readACertainRecordInBlock(saveRoute, quest_blockIdx, quest_relativeRecordIdx);
//     cout << metaBlock[quest_blockIdx].numsOfRecords() << endl;
    cout << endl;

    // do validation printing
    for (int idx = 0; idx < metaBlock[quest_blockIdx].numsOfRecords(); idx++) {
        cout << metaBlock[quest_blockIdx].endPostionOfEachRecord[idx] << " ";
    }

//    buildDataFileIntoBPTree(saveRoute, metaBlock);
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