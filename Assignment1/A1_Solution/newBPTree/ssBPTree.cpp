//
// Created by WinnieCMZ on 2022-10-04.
//

#include "ssBPTree.h"

#include <iostream>

using namespace std;

short ssTreeNode::maxKeySize() {
    short maxNumsOfKey = m_value - 1;
    return maxNumsOfKey;
}

short ssTreeNode::minKeySize() {
    short minNumOfKey = m_value / 2 - 1;
    return minNumOfKey;
}

//short ssTreeNode::currentKeySize() {
//    return this->fieldOne_AsKey.size();
//}

bool ssTreeNode::isFull() {
    if (this->currentKeySize >= this->maxKeySize()) {
        return true;
    } else {
        return false;
    }
}

ssTreeNode *ssBPTree::searchElm(string targetKey) {
    if (root == NULL) {
        cout << "The tree does not exist" << endl;
    } else {
        ssTreeNode *cursor = root; // start search from the root

        while (cursor->isLeaf == false) {
            for (int idx = 0; idx < cursor->currentKeySize; idx++) {
                if (targetKey < cursor->fieldOne_AsKey[idx]) {
                    cursor = cursor->pointer[idx];
                    break;
                }

                if (idx == cursor->currentKeySize - 1) {
                    cursor = cursor->pointer[idx + 1];
                    break;
                }
            }
        }

        for (int index = 0; index < cursor->currentKeySize; index++) {
            if (cursor->fieldOne_AsKey[index] == targetKey) {
                cout << targetKey << "is found at " << cursor->location[index] << endl;
                return cursor;
            }
        }

        cout << targetKey << " cannot be found inside the tree" << endl;

    }
}

// recall that aLocation is the idxBlock*100+r_idxRecord
void ssBPTree::insertElm(string aFieldOneValue, int aLocation) {
    if (root == NULL) {
        root = new ssTreeNode;
        root->fieldOne_AsKey[0] = aFieldOneValue;
        root->location[0] = aLocation;
        root->isLeaf = true;
        root->currentKeySize = 1;
    } else {
        ssTreeNode *cursor = root;
        ssTreeNode *parent;
        while (cursor->isLeaf == false) {
            parent = cursor;
            for (int idx = 0; idx < cursor->currentKeySize; idx++) {
                if (aFieldOneValue < cursor->fieldOne_AsKey[idx]) {
                    cursor = cursor->pointer[idx];
                    break;
                }

                if (idx == cursor->currentKeySize - 1) {
                    cursor = cursor->pointer[idx + 1];
                    break;
                }
            }
        }

        if (!cursor->isFull()) {
            int i = 0;
            while (aFieldOneValue > cursor->fieldOne_AsKey[i] && i < cursor->currentKeySize) {
                i++;
            }
            for (int j = cursor->currentKeySize; j > i; j--) {
                cursor->fieldOne_AsKey[j] = cursor->fieldOne_AsKey[j - i];
            }
        }
    }
}