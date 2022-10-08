#include <algorithm> // implement sorting
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <typeinfo>

#include "DB_lib/dbComponents.h"
#include "util/forBPTreeBuild.h"
#include "util/forBlockANDRecordGeneration.h"

using namespace std;

int main() {

  //    ofstream myfile;
  //    myfile.open("example.txt");
  //    myfile << "Writing this to a file.\n" << endl;
  //    myfile.close();
  //
  //    fstream newFile;
  //    newFile.open("example.txt");
  //    char value;
  //    newFile.seekg(0, ios::beg);
  //    newFile.get(value);
  //
  //    cout << value << endl;

  // config the raw input data location_asValue
  string FileRoute = "../assets/A1_data.txt";
  vector<Record> metaRecord = transferFileToRecord(FileRoute);

  // sorting all records base on their field 1
  sort(metaRecord.begin(), metaRecord.end(),
       [](const Record &lhs, const Record &rhs) {
         return lhs.field1 < rhs.field1;
       });

  // get how many records in total that need to be store into blocks
  int totalNumOfRecords = metaRecord.size();

  // get the total size of all data in bytes
  int sizeOfAllRecord = getSizeOfAllData(totalNumOfRecords, metaRecord);

  cout << "This script creates " << totalNumOfRecords << " records." << endl;
  cout << "The total size of all records are " << sizeOfAllRecord << " bytes."
       << endl;

  vector<BlockNode> metaBlock =
      storeRecordToBlocks(totalNumOfRecords, metaRecord);
  int realAllBlockSize = calculateRealBlockSize(metaBlock);

  // get how many blocks we created
  int totalNumOfBlock = metaBlock.size();

  // get the total size of all data in bytes
  int sizeOfAllBlock = totalNumOfBlock * 1024;

  cout << "This script creates " << totalNumOfBlock << " blocks." << endl;
  cout << "The total size of all blocks are " << sizeOfAllBlock << " bytes."
       << endl;

  cout << "The space usage rate is "
       << ((realAllBlockSize + 0.0) / sizeOfAllBlock) * 100 << "%" << endl;

  // now we are going to store all blocks (with records) into the datafile
  string saveRoute = "../assets/dataFile.txt";

  //    cout << "17 has the total size " << metaBlock[17].currentSize() << endl;
  //    cout << "17 has the head size " << metaBlock[17].sizeOfHead() << endl;
  //    cout << "17 has the content size " << metaBlock[17].recordContent.size()
  //    << endl; writeAllFile(saveRoute, metaBlock);

  //    int quest_blockIdx = 0;
  //    int quest_relativeRecordIdx = 2;
  //    cout <<
  //    metaBlock[quest_blockIdx].endPostionOfEachRecord[quest_relativeRecordIdx
  //    - 1] << endl; cout <<
  //    metaBlock[quest_blockIdx].endPostionOfEachRecord[quest_relativeRecordIdx]
  //    << endl; string astring = readACertainRecordInBlock(saveRoute,
  //    quest_blockIdx, quest_relativeRecordIdx); cout << astring << endl; cout
  //    << endl;

  ssBPTree allNodes;
  //    buildDataFileIntoBPTree(saveRoute, metaBlock, allNodes);

  //    int global_int = 40;
  //
  //    for (int idx = 0; idx < global_int; idx++) {
  //        string superString = "s" + to_string(idx) + "s";
  //        allNodes.ramInsertElm(superString, idx);

  //    }
  //
  //    for (int idx = 0; idx < global_int; idx++) {
  //        string superString = "s" + to_string(idx) + "s";
  //        allNodes.searchElm(superString);
  //    }

  return 0;
}