//
// Created by winni on 2022-10-03.
//

#ifndef A1_SOLUTION_UTILITY_H
#define A1_SOLUTION_UTILITY_H

#endif //A1_SOLUTION_UTILITY_H


int convertBinaryToDecimal(long long binaryInput){
    int dec = 0, i = 0, residual;

    while (binaryInput!=0) {
        residual = binaryInput % 10;
        binaryInput /= 10;
        dec += residual * pow(2, i);
        ++i;
}
