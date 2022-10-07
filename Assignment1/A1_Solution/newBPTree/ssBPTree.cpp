//
// Created by WinnieCMZ on 2022-10-04.
//

#include "ssBPTree.h"

#include <iostream>

using namespace std;

const static int m_value = 8;

ssTreeNode::ssTreeNode() {

//    for (short idx = 0; idx < m_value; idx++) {
//        fieldOne_AsKey.push_back("");
//    }

    fieldOne_AsKey = new string[m_value];
    location_asValue = new int[m_value];
    pointer = new ssTreeNode *[m_value + 1];
}

ssBPTree::ssBPTree() {
    root = NULL;
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

        for (int idx = 0; idx < cursor->currentKeySize; idx++) {
            if (cursor->fieldOne_AsKey[idx] == targetKey) {
                cout << targetKey << " is found at " << cursor->location_asValue[idx] << endl;
                return cursor;
            }
        }

        cout << targetKey << " cannot be found inside the tree" << endl;

    }
}

// recall that Value_Location is the idxBlock*100+r_idxRecord
void ssBPTree::ramInsertElm(string Key_FieldOneValue, int Value_Location) {
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
            int idx = 0;
            while (Key_FieldOneValue > cursor->fieldOne_AsKey[idx] && idx < cursor->currentKeySize) {
                idx++;
            }
            for (int j = cursor->currentKeySize; j > idx; j--) {
                cursor->fieldOne_AsKey[j] = cursor->fieldOne_AsKey[j - 1];
                cursor->location_asValue[j] = cursor->location_asValue[j - 1];
            }
            cursor->fieldOne_AsKey[idx] = Key_FieldOneValue;
            cursor->location_asValue[idx] = Value_Location;
            cursor->currentKeySize++;
            cursor->pointer[cursor->currentKeySize] = cursor->pointer[cursor->currentKeySize - 1];
            cursor->pointer[cursor->currentKeySize - 1] = NULL;
        } else {
            ssTreeNode *newLeaf = new ssTreeNode;

            string virtualNodeKey[m_value + 1];
            int virtualNodeValue[m_value + 1];

            for (int idx = 0; idx < m_value; idx++) {
                virtualNodeKey[idx] = cursor->fieldOne_AsKey[idx];
                virtualNodeValue[idx] = cursor->location_asValue[idx];
            }
            int idx = 0;
            int jdx;
            while (Key_FieldOneValue > virtualNodeKey[idx] && idx < m_value)
                idx++;
            for (int jdx = m_value + 1; jdx > idx; jdx--) { // m_value+1 to m_value
                virtualNodeKey[jdx] = virtualNodeKey[jdx - 1];
                virtualNodeValue[jdx] = virtualNodeValue[jdx - 1];
            }

            virtualNodeKey[idx] = Key_FieldOneValue;
            virtualNodeValue[idx] = Value_Location;
            newLeaf->isLeaf = true;
            cursor->currentKeySize = (m_value + 1) / 2;
            newLeaf->currentKeySize = m_value + 1 - (m_value + 1) / 2;
            cursor->pointer[cursor->currentKeySize] = newLeaf;
            newLeaf->pointer[newLeaf->currentKeySize] = cursor->pointer[m_value];
            cursor->pointer[m_value] = NULL;
            for (idx = 0; idx < cursor->currentKeySize; idx++) {
                cursor->fieldOne_AsKey[idx] = virtualNodeKey[idx];
                cursor->location_asValue[idx] = virtualNodeValue[idx];
            }
            for (idx = 0, jdx = cursor->currentKeySize; idx < newLeaf->currentKeySize; idx++, jdx++) {
                newLeaf->fieldOne_AsKey[idx] = virtualNodeKey[jdx];
                newLeaf->location_asValue[idx] = virtualNodeValue[jdx];
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
    if (!cursor->isFull()) {
        int idx = 0;
        while (Key_FieldOneValue > cursor->fieldOne_AsKey[idx] && idx < cursor->currentKeySize) {
            idx++;
        }

        // manipulate keys
        for (int jdx = cursor->currentKeySize; jdx > idx; jdx--) {
            cursor->fieldOne_AsKey[jdx] = cursor->fieldOne_AsKey[jdx - 1];
        }

        // manipulate pointers
        for (int jdx = cursor->currentKeySize + 1; jdx > idx; jdx--) {
            cursor->pointer[jdx] = cursor->pointer[jdx - 1];
        }

        cursor->fieldOne_AsKey[idx] = Key_FieldOneValue;
        cursor->currentKeySize++;
        cursor->pointer[idx + 1] = child;
    } else {
        ssTreeNode *newInternalNode = new ssTreeNode;
        ssTreeNode *virtualNodePointer[m_value + 2];
        string virtualNodeKey[m_value + 1];

        for (int idx = 0; idx < m_value; idx++) {
            virtualNodeKey[idx] = cursor->fieldOne_AsKey[idx];
        }

        for (int idx = 0; idx < m_value + 1; idx++) {
            virtualNodePointer[idx] = cursor->pointer[idx];
        }

        int idx = 0, jdx;
        while (Key_FieldOneValue > virtualNodeKey[idx] && idx < m_value) {
            idx++;
        }

        for (int jdx = m_value + 1; jdx > idx; jdx--) {
            virtualNodePointer[jdx] = virtualNodePointer[jdx - 1];
        }

        virtualNodeKey[idx] = Key_FieldOneValue;
        for (int jdx = m_value + 2; jdx > idx + 1; jdx--) {
            virtualNodePointer[jdx] = virtualNodePointer[jdx - 1];
        }

        virtualNodePointer[idx + 1] = child;
        newInternalNode->isLeaf = false;
        cursor->currentKeySize = (m_value + 1) / 2;
        newInternalNode->currentKeySize = m_value - (m_value + 1) / 2;

        for (idx = 0, jdx = cursor->currentKeySize + 1; idx < newInternalNode->currentKeySize; idx++, jdx++) {
            newInternalNode->fieldOne_AsKey[idx] = virtualNodeKey[jdx];
        }
        for (idx = 0, jdx = cursor->currentKeySize + 1; idx < newInternalNode->currentKeySize + 1; idx++, jdx++) {
            newInternalNode->pointer[idx] = virtualNodePointer[jdx];
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
    for (int idx = 0; idx < cursor->currentKeySize + 1; idx++) {
        if (cursor->pointer[idx] == child) {
            parentNode = cursor;
            return parentNode;
        } else {
            parentNode = findParentNode(cursor->pointer[idx], child);
            if (parentNode != NULL) {
                return parentNode;
            }
        }
    }
}

//// Show the tree
//void ssBPTree::showBPTree(ssTreeNode *cursor) {
//    if (cursor != NULL) {
//        for (int idx = 0; idx < cursor->currentKeySize; idx++) {
//            cout << cursor->fieldOne_AsKey[idx] << " ";
//        }
//        cout << "\n";
//        if (cursor->isLeaf != true) {
//            for (int idx = 0; idx < cursor->currentKeySize + 1; idx++) {
//                showBPTree(cursor->pointer[idx]);
//            }
//        }
//    }
//}
//
//// Get the root
//ssTreeNode *ssBPTree::getTreeRoot() {
//    return root;
//}