//
// Created by winni on 2022-10-03.
//

#include "../DB_lib/dbComponents.h"

#ifndef A1_SOLUTION_UTILITY_H
#define A1_SOLUTION_UTILITY_H

#endif //A1_SOLUTION_UTILITY_H

using namespace std;

// this method has problem
//int convertBinaryToDecimal(bitset<8> binaryInput) {
//    int dec = 0, i = 0, residual;
//
//    long long binaryInput_misc = binaryInput.to_ullong();
//    cout << binaryInput_misc << endl;
//
//    while (binaryInput_misc != 0) {
//        residual = binaryInput_misc % 10;
//        binaryInput_misc /= 10;
//        dec += residual * pow(2, i);
//        ++i;
//    }
//}

// bitset concatenation
template<size_t Num1, size_t Num2>
bitset<Num1 + Num2> concat(const bitset<Num1> &b1, const bitset<Num2> &b2) {
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    return bitset<Num1 + Num2>(s1 + s2);
}

void writeOneLineFile(string saveRoute, vector<BlockNode> allBlocks) {
    char singleLine[1024];

    // open the file in the write mode
    ofstream outfile(saveRoute);

    // Block Part 1: nums of records
    // PLACE the thisNumOfRecord INTO the data file
    unsigned short thisNumOfRecord = allBlocks[0].numsOfRecords();
    singleLine[0] = thisNumOfRecord;
    outfile << singleLine[0];

    // Block Part 2: vector list of end positions of each record
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


    // Block Part 3: size of the block head
    unsigned short thisSizeOfHead = allBlocks[0].sizeOfHead();
    singleLine[singleLineIndexTracker] = thisNumOfRecord;
    outfile << singleLine[singleLineIndexTracker];
    singleLineIndexTracker += 1;

    // Block Part 4: very long string of record contents
    for (int contentIdx = 0; contentIdx <= allBlocks[0].recordContent.size(); contentIdx++) {
        singleLine[singleLineIndexTracker] = allBlocks[0].recordContent[contentIdx];
        outfile << singleLine[singleLineIndexTracker];
        singleLineIndexTracker += 1;
    }

    for (int restPart = singleLineIndexTracker; restPart < 1024; restPart++) {
        outfile << 0;
    }

    outfile.close();
};

void writAllFile(string saveRoute, vector<BlockNode> allBlocks) {

    // open the file in the write mode
    ofstream outfile(saveRoute);

    for (int idxOfAllBlocks = 0; idxOfAllBlocks < allBlocks.size(); idxOfAllBlocks++) {

        char singleLine[1024];

        // Block Part 1: nums of records
        // PLACE the thisNumOfRecord INTO the data file
        unsigned short thisNumOfRecord = allBlocks[0].numsOfRecords();
        singleLine[0] = thisNumOfRecord;
        outfile << singleLine[0];

        // Block Part 2: vector list of end positions of each record
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


        // Block Part 3: size of the block head
        unsigned short thisSizeOfHead = allBlocks[0].sizeOfHead();
        singleLine[singleLineIndexTracker] = thisNumOfRecord;
        outfile << singleLine[singleLineIndexTracker];
        singleLineIndexTracker += 1;

        // Block Part 4: very long string of record contents
        for (int contentIdx = 0; contentIdx <= allBlocks[0].recordContent.size(); contentIdx++) {
            singleLine[singleLineIndexTracker] = allBlocks[0].recordContent[contentIdx];
            outfile << singleLine[singleLineIndexTracker];
            singleLineIndexTracker += 1;
        }

        for (int restPart = singleLineIndexTracker; restPart < 1024; restPart++) {
            outfile << 0;
        }

    }

    outfile.close();
};


// this function is just a half work, we are going to use it directly in future
void readAllFile(string saveRoute) {

    char value;

    fstream file(saveRoute, ios::in);
    if (!file) {
        cout << "Error opening file.";
        return;
    }

    // get nums of record
    file.seekg(0, ios::beg);
    file.get(value);
    bitset<8> thisNumOfRecord_Binary(value);
//  cout << "This block has nums of record: " << thisNumOfRecord_Binary << endl;
    long thisNumOfRecord_Decimal = thisNumOfRecord_Binary.to_ulong();
    cout << "This block has nums of record: " << thisNumOfRecord_Decimal << endl;

    // get each record end positions
    for (int idxOfRecord = 0; idxOfRecord < thisNumOfRecord_Decimal; idxOfRecord++) {

        // get the end position of each record
        file.seekg(0, ios::cur);
        file.get(value);
        bitset<8> left_thisEndPositonOfRecord_Binary(value);

        file.seekg(0, ios::cur);
        file.get(value);
        bitset<8> right_thisEndPositonOfRecord_Binary(value);

        bitset<16> fullSingleRecordJumper = concat(left_thisEndPositonOfRecord_Binary,
                                                   right_thisEndPositonOfRecord_Binary);

        //    cout << fullSingleRecordJumper << endl;

        long thisEndPositonOfRecord_Decimal = fullSingleRecordJumper.to_ulong();
        cout << thisEndPositonOfRecord_Decimal << "|";
    }
    cout << endl;
}

void readACertainRecordInBlock(string saveRoute, int indexOfBlock, int indexOfRecordInBlock) {
    char value;

    fstream file(saveRoute, ios::in);
    if (!file) {
        cout << "Error opening file.";
        return;
    }



}