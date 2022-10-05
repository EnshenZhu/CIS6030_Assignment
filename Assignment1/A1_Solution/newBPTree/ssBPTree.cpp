//
// Created by WinnieCMZ on 2022-10-04.
//

#include "ssBPTree.h"

#include <iostream>

using namespace std;

int m_value = 8;

ssTreeNode::ssTreeNode() {
    fieldOne_AsKey = new string[m_value];
    location_asValue = new int[m_value];
    pointer = new ssTreeNode *[m_value + 1];
}

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
                cout << targetKey << " is found at " << cursor->location_asValue[index] << endl;
                return cursor;
            }
        }

        cout << targetKey << " cannot be found inside the tree" << endl;

    }
}

// recall that Value_Location is the idxBlock*100+r_idxRecord
void ssBPTree::insertElm(string Key_FieldOneValue, int Value_Location) {
    if (root == NULL) {
        root = new ssTreeNode;
        root->fieldOne_AsKey[0] = Key_FieldOneValue;
        root->location_asValue[0] = Value_Location;
        root->isLeaf = true;
        root->currentKeySize = 1;
    } else {
        ssTreeNode *cursor = root;
        ssTreeNode *parent;
        while (cursor->isLeaf == false) {
            parent = cursor;
            for (int idx = 0; idx < cursor->currentKeySize; idx++) {
                if (Key_FieldOneValue < cursor->fieldOne_AsKey[idx]) {
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
            while (Key_FieldOneValue > cursor->fieldOne_AsKey[i] && i < cursor->currentKeySize) {
                i++;
            }
            for (int j = cursor->currentKeySize; j > i; j--) {
                cursor->fieldOne_AsKey[j] = cursor->fieldOne_AsKey[j - i];
                cursor->location_asValue[j] = cursor->location_asValue[j - 1];
            }
            cursor->fieldOne_AsKey[i] = Key_FieldOneValue;
            cursor->location_asValue[i] = Value_Location;
            cursor->currentKeySize++;
            cursor->pointer[cursor->currentKeySize] = cursor->pointer[cursor->currentKeySize - 1];
            cursor->pointer[cursor->currentKeySize - 1] = NULL;
        } else {
            ssTreeNode *newLeaf = new ssTreeNode;

            string virtualNodeKey[m_value + 1];
            int virtualNodeValue[m_value + 1];

            for (int i = 0; i < m_value; i++) {
                virtualNodeKey[i] = cursor->fieldOne_AsKey[i];
                virtualNodeValue[i] = cursor->location_asValue[i];
            }
            int i = 0, j;
            while (Key_FieldOneValue > virtualNodeKey[i] && i < m_value) {
                i++;
            }
            for (int j = m_value + 1; j > i; j--) {
                virtualNodeKey[j] = virtualNodeKey[j - 1]; // bug here
                virtualNodeValue[j] = virtualNodeValue[j - 1];
            }
            virtualNodeKey[i] = Key_FieldOneValue;
            virtualNodeValue[i] = Value_Location;
            newLeaf->isLeaf = true;
            cursor->currentKeySize = (m_value + 1) / 2;
            newLeaf->currentKeySize = m_value + 1 - (m_value + 1) / 2;
            cursor->pointer[cursor->currentKeySize] = newLeaf;
            newLeaf->pointer[newLeaf->currentKeySize] = cursor->pointer[m_value];
            cursor->pointer[m_value] = NULL;
            for (i = 0; i < cursor->currentKeySize; i++) {
                cursor->fieldOne_AsKey[i] = virtualNodeKey[i];
                cursor->location_asValue[i] = virtualNodeValue[i];
            }
            for (i = 0, j = cursor->currentKeySize; i < newLeaf->currentKeySize; i++, j++) {
                newLeaf->fieldOne_AsKey[i] = virtualNodeKey[j];
                newLeaf->location_asValue[i] = virtualNodeValue[j];
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
                insertInternalNode(newLeaf->fieldOne_AsKey[0], parent, newLeaf); // still need future work
            }
        }
    }
}

// insert internal nodes
void ssBPTree::insertInternalNode(string Key_FieldOneValue, ssTreeNode *cursor, ssTreeNode *child) {
    if (cursor->currentKeySize < m_value) {
        int i = 0;
        while (Key_FieldOneValue > cursor->fieldOne_AsKey[i] && i < cursor->currentKeySize) {
            i++;
        }

        // manipulate keys
        for (int j = cursor->currentKeySize; j > i; j--) {
            cursor->fieldOne_AsKey[j] = cursor->fieldOne_AsKey[j - 1];
        }

        // manipulate pointers
        for (int j = cursor->currentKeySize + 1; j > i; j--) {
            cursor->pointer[j] = cursor->pointer[j - 1];
        }

        cursor->fieldOne_AsKey[i] = Key_FieldOneValue;
        cursor->currentKeySize++;
        cursor->pointer[i + 1] = child;
    } else {
        ssTreeNode *newInternalNode = new ssTreeNode;
        ssTreeNode *virtualNodePointer[m_value + 2];
        string virtualNodeKey[m_value + 1];

        for (int i = 0; i < m_value; i++) {
            virtualNodeKey[i] = cursor->fieldOne_AsKey[i];
        }

        for (int i = 0; i < m_value + 1; i++) {
            virtualNodePointer[i] = cursor->pointer[i];
        }

        int i = 0, j;
        while (Key_FieldOneValue > virtualNodeKey[i] && i < m_value) {
            i++;
        }

        for (int j = m_value + 1; j > i; j--) {
            virtualNodePointer[j] = virtualNodePointer[j - 1];
        }

        virtualNodeKey[i] = Key_FieldOneValue;
        for (int j = m_value + 2; j > i + 1; j--) {
            virtualNodePointer[j] = virtualNodePointer[j - 1];
        }

        virtualNodePointer[i + 1] = child;
        newInternalNode->isLeaf = false;
        cursor->currentKeySize = (m_value + 1) / 2;
        newInternalNode->currentKeySize = m_value - (m_value + 1) / 2;

        for (i = 0, j = cursor->currentKeySize + 1; i < newInternalNode->currentKeySize; i++, j++) {
            newInternalNode->fieldOne_AsKey[i] = virtualNodeKey[j];
        }
        for (i = 0, j = cursor->currentKeySize + 1; i < newInternalNode->currentKeySize + 1; i++, j++) {
            newInternalNode->pointer[i] = virtualNodePointer[j];
        }
        if (cursor == root) {
            ssTreeNode *newRoot = new ssTreeNode;
            newRoot->fieldOne_AsKey[0] = cursor->fieldOne_AsKey[cursor->currentKeySize];
            newRoot->pointer[0] = cursor;
            newRoot->pointer[1] = newInternalNode;
            newRoot->isLeaf = false;
            newRoot->currentKeySize = 1;
            root = newRoot;
        } else {
            insertInternalNode(cursor->fieldOne_AsKey[cursor->currentKeySize], findParentNode(root, cursor),
                               newInternalNode);
        }
    }
}

// find parent node
ssTreeNode *ssBPTree::findParentNode(ssTreeNode *cursor, ssTreeNode *child) {
    ssTreeNode *parentNode;
    if (cursor->isLeaf || (cursor->pointer[0])->isLeaf) {
        return NULL;
    }
    for (int i = 0; i < cursor->currentKeySize + 1; i++) {
        if (cursor->pointer[i] == child) {
            parentNode = cursor;
            return parentNode;
        } else {
            parentNode = findParentNode(cursor->pointer[i], child);
            if (parentNode != NULL) {
                return parentNode;
            }
        }
    }
}