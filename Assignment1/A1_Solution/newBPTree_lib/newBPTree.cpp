//
// Created by WinnieCMZ on 2022-10-04.
//

#include "newBPTree.h"

using namespace std;

short newTreeNode::maxKeySize() {
    short maxNumsOfKey = m_value - 1;
    return maxNumsOfKey;
}

short newTreeNode::minKeySize() {
    short minNumOfKey = m_value / 2 - 1;
    return minNumOfKey;
}

short newTreeNode::currentKeySize() {
    return this->fieldOne_AsKey.size();
}

bool newTreeNode::isFull() {
    if (this->currentKeySize() >= this->maxKeySize()) {
        return true;
    } else {
        return false;
    }
}
