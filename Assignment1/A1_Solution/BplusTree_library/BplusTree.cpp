//
// Created by winni on 2022-09-25.
//

#include "BplusTree.h"

#include <iostream>
//#include <climits>
//#include <fstream>
//#include <sstream>
#include <cmath>


using namespace std;

TreeNode::TreeNode() {
    key = new int[MAX];
    pointer = new TreeNode *[MAX + 1];
}

BplusTree::BplusTree() {
    root = NULL;
}

// Search the leaf element
void BplusTree::searchElm(int targetElement) {
    if (root == NULL) {
        // if there is no root, the tree does not exist
        cout << "The tree is empty." << endl;
    } else {
        TreeNode *cursor = root; // start search from the root

        while (cursor->isLeaf == false) {
            for (int idx = 0; idx < cursor->size; idx++) {
                if (targetElement < cursor->key[idx]) {
                    cursor = cursor->pointer[idx];
                    break;
                }

                if (idx == cursor->size - 1) {
                    cursor = cursor->pointer[idx + 1];
                    break;
                }
            }
        }

        for (int index = 0; index < cursor->size; index++) {
            if (cursor->key[index] == targetElement) {
                cout << targetElement << " is found at Block " << &cursor << endl;
                return;
            }
        }
        cout << targetElement << " cannot be found inside the tree" << endl;
    }
}

// Find the parent
TreeNode *BplusTree::findParentNode(TreeNode *cursor, TreeNode *child) {
    TreeNode *parent;
    if (cursor->isLeaf || (cursor->pointer[0])->isLeaf) {
        return NULL;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->pointer[i] == child) {
            parent = cursor;
            return parent;
        } else {
            parent = findParentNode(cursor->pointer[i], child);
            if (parent != NULL)
                return parent;
        }
    }
    return parent;
}

// Insert the leaf element
void BplusTree::insertElm(int target) {
    if (root == NULL) {
        root = new TreeNode;
        root->key[0] = target;
        root->isLeaf = true;
        root->size = 1;
    } else {
        TreeNode *cursor = root;
        TreeNode *parent;
        while (cursor->isLeaf == false) {
            parent = cursor;
            for (int idx = 0; idx < cursor->size; idx++) {
                if (target < cursor->key[idx]) {
                    cursor = cursor->pointer[idx];
                    break;
                }
                if (idx == cursor->size - 1) {
                    cursor = cursor->pointer[idx + 1];
                    break;
                }
            }
        }
        if (cursor->size < MAX) {
            int i = 0;
            while (target > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = target;
            cursor->size++;
            cursor->pointer[cursor->size] = cursor->pointer[cursor->size - 1];
            cursor->pointer[cursor->size - 1] = NULL;
        } else {
            TreeNode *newLeaf = new TreeNode;
            int virtualNode[MAX + 1];
            for (int i = 0; i < MAX; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            while (target > virtualNode[i] && i < MAX)
                i++;
            for (int j = MAX + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = target;
            newLeaf->isLeaf = true;
            cursor->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;
            cursor->pointer[cursor->size] = newLeaf;
            newLeaf->pointer[newLeaf->size] = cursor->pointer[MAX];
            cursor->pointer[MAX] = NULL;
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            if (cursor == root) {
                TreeNode *newRoot = new TreeNode;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->pointer[0] = cursor;
                newRoot->pointer[1] = newLeaf;
                newRoot->isLeaf = false;
                newRoot->size = 1;
                root = newRoot;
            } else {
                insertInternalNode(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

// Insert internal nodes
void BplusTree::insertInternalNode(int target, TreeNode *cursor, TreeNode *child) {
    if (cursor->size < MAX) {
        int i = 0;
        while (target > cursor->key[i] && i < cursor->size)
            i++;
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->pointer[j] = cursor->pointer[j - 1];
        }
        cursor->key[i] = target;
        cursor->size++;
        cursor->pointer[i + 1] = child;
    } else {
        TreeNode *newInternal = new TreeNode;
        int virtualKey[MAX + 1];
        TreeNode *virtualPtr[MAX + 2];
        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->key[i];
        }
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->pointer[i];
        }
        int i = 0, j;
        while (target > virtualKey[i] && i < MAX)
            i++;
        for (int j = MAX + 1; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = target;
        for (int j = MAX + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->isLeaf = false;
        cursor->size = (MAX + 1) / 2;
        newInternal->size = MAX - (MAX + 1) / 2;
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->pointer[i] = virtualPtr[j];
        }
        if (cursor == root) {
            TreeNode *newRoot = new TreeNode;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->pointer[0] = cursor;
            newRoot->pointer[1] = newInternal;
            newRoot->isLeaf = false;
            newRoot->size = 1;
            root = newRoot;
        } else {
            insertInternalNode(cursor->key[cursor->size], findParentNode(root, cursor), newInternal);
        }
    }
}