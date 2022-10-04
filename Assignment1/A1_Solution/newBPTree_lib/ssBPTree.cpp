//
// Created by WinnieCMZ on 2022-10-04.
//

#include "ssBPTree.h"

using namespace std;

short ssTreeNode::maxKeySize() {
    short maxNumsOfKey = m_value - 1;
    return maxNumsOfKey;
}

short ssTreeNode::minKeySize() {
    short minNumOfKey = m_value / 2 - 1;
    return minNumOfKey;
}

short ssTreeNode::currentKeySize() {
    return this->fieldOne_AsKey.size();
}

bool ssTreeNode::isFull() {
    if (this->currentKeySize() >= this->maxKeySize()) {
        return true;
    } else {
        return false;
    }
}
