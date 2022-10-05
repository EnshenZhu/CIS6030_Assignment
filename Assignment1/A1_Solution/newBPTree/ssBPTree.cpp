//
// Created by WinnieCMZ on 2022-10-04.
//

#include "ssBPTree.h"

#include <iostream>

using namespace std;

short ssTreeNode::maxKeySize() {
    short maxNumsOfKey = m_value;
    return maxNumsOfKey;
}

short ssTreeNode::minKeySize() {
    short minNumOfKey = (m_value + 1) / 2;
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
                cout << targetKey << "is found at " << cursor->location_asValue[index] << endl;
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
        root->location_asValue[0] = aLocation;
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
            cursor->fieldOne_AsKey[i] = aFieldOneValue;
            cursor->location_asValue[i] = aLocation;
            cursor->currentKeySize++;
            cursor->pointer[cursor->currentKeySize] = cursor->pointer[cursor->currentKeySize - 1];
            cursor->pointer[cursor->currentKeySize - 1] = NULL;
        } else {
            ssTreeNode *newLeaf = new ssTreeNode;
            string virtualNode[m_value + 1];
            for (int i = 0; i < m_value; i++) {
                virtualNode[i] = cursor->fieldOne_AsKey[i];
            }
            int i = 0, j;
            while (aFieldOneValue > virtualNode[i] && i < m_value) {
                i++;
            }
            for (int j = m_value + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = aFieldOneValue;
            newLeaf->isLeaf = true;
            newLeaf->location_asValue[i] = aLocation; // still in trying
            cursor->currentKeySize = (m_value + 1) / 2;
            newLeaf->currentKeySize = m_value + 1 - (m_value + 1) / 2;
            cursor->pointer[cursor->currentKeySize] = newLeaf;
            newLeaf->pointer[newLeaf->currentKeySize] = cursor->pointer[m_value];
            cursor->pointer[m_value] = NULL;
            for (i = 0; i < cursor->currentKeySize; i++) {
                cursor->fieldOne_AsKey[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->currentKeySize; i < newLeaf->currentKeySize; i++, j++) {
                newLeaf->fieldOne_AsKey[i] = virtualNode[j];
            }
            if (cursor == root) {
                ssTreeNode *newRoot = new ssTreeNode;
                newRoot->fieldOne_AsKey[0] = newLeaf->fieldOne_AsKey[0];
                newRoot->pointer[0] = cursor;
                newRoot->pointer[1] = newLeaf;
                newRoot->isLeaf = false;
                newRoot->currentKeySize = 1;
                root = newRoot;
            } else {
                insertInternalNode(); // still need future work
            }
        }
    }
}