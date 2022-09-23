#include <iostream>
#include "dblibrary/dbComponents.h"
#include <fstream>
#include <cstdlib>
#include <algorithm>  // implement sorting

using namespace std;


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

    cout << metaRecord[7].field1 << endl;
    cout << metaRecord[7].field2 << endl;
    cout << metaRecord[7].field3 << endl;



//    vector<BlockNode> metaBlock;



//    char word[50];
//    readFILE >> word;
//    while (readFILE.good()) {
//        cout << word << " ";
//        readFILE >> word;
//    }


//    Record record1("a", "b", "c");
//
//    cout << record1.endIndexField2 << endl;

    return 0;
}