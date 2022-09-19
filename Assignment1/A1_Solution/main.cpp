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

vector<Record> transferFileToRecord() {
    string fileRoute = "../assets/A1_data.txt";
    ifstream readFILE;
    readFILE.open(fileRoute);

    if (!readFILE.is_open()) {
        cout << "Error on file reading!" << endl;
        exit(EXIT_FAILURE);
    }

    vector<Record> allRecords;

    char word[50];
    readFILE >> word;
    cout << word << endl;
}

int main() {
    transferFileToRecord();


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