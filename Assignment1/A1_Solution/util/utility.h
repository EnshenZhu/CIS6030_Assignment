//
// Created by winni on 2022-10-03.
//

#ifndef A1_SOLUTION_UTILITY_H
#define A1_SOLUTION_UTILITY_H

#endif //A1_SOLUTION_UTILITY_H

using namespace std;

// this method has problem
int convertBinaryToDecimal(bitset<8> binaryInput) {
    int dec = 0, i = 0, residual;

    long long binaryInput_misc = binaryInput.to_ullong();
    cout << binaryInput_misc << endl;

    while (binaryInput_misc != 0) {
        residual = binaryInput_misc % 10;
        binaryInput_misc /= 10;
        dec += residual * pow(2, i);
        ++i;
    }
}