#include <iostream>
#include "library/dbComponents.h"
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {

    string fileRoute = "./assets/A1_data.txt";
    ifstream readFILE;
    readFILE.open(fileRoute);

    if (!readFILE.is_open()) {
        exit(EXIT_FAILURE);
    }

    char word[50];
    readFILE>>word;
    while (readFILE.good()){
        cout<<word<<" ";
        readFILE>>word;
    }


//    Record record1("a", "b", "c");
//
//    cout << record1.endIndexField2 << endl;

    return 0;
}