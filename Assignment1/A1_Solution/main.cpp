#include <iostream>
#include "library/dbComponents.h"
#include <fstream>
#include <cstdlib>

using namespace std;


int fieldTwoEndIdx(string str) {
    int count = 3;
    for (int idx = 0; idx < str.size(); idx++) {
        if (isspace(str[idx])) {
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
        allRecords.push_back(allRecords());
        Record &currentRecord = allRecords.back();
        currentRecord.field1 = textInput.substr(0, 9);
        currentRecord.endIndexField2 = fieldTwoEndIdx(textInput);
        currentRecord.field2 = textInput.substr(10, currentRecord.endIndexField2 - 10);
        currentRecord.field3 = textInput.substr(currentRecord.endIndexField2 + 1);
    }
}

int main() {
    string FileRoute = "../assets/A1_data.txt";
    transferFileToRecord(str
    FileRoute);


//    char word[50];
//    readFILE >> word;
//    while (readFILE.good()) {
//        cout << word << " ";
//        readFILE >> word;
//    }

    cout << "time space" << endl;


//    Record record1("a", "b", "c");
//
//    cout << record1.endIndexField2 << endl;

    return 0;
}