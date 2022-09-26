//
// Created by winni on 2022-09-25.
//

#include "BplusTree.h"

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <cmath>


using namespace std;

TreeNode::TreeNode() {
    key = new int[MAX];
    pointer = new TreeNode *[MAX + 1];
}

BplusTree::BplusTree() {
    root = NULL;
}

// Search the Element
void BplusTree::searchElm(int targetElement) {
    if (root == NULL) {
        cout << "The tree is empty." << endl;
    } else {
        TreeNode *cursor = root;
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
                cout << targetElement << " is found" << endl;
                return;
            }
        }
        cout << targetElement << " cannot be found inside the tree" << endl;
    }
}

// Insert Operation
void BplusTree::insertElm(int targetValue) {
    if (root == NULL) {
        root = new TreeNode;
        root->key[0] = targetValue;
        root->isLeaf = true;
        root->size = 1;
    } else {
        TreeNode *cursor = root;
        TreeNode *parent;
        while (cursor->isLeaf == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (targetValue < cursor->key[i]) {
                    cursor = cursor->pointer[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->pointer[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < MAX) {
            int i = 0;
            while (targetValue > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = targetValue;
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
            while (targetValue > virtualNode[i] && i < MAX)
                i++;
            for (int j = MAX + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = x;
            newLeaf->IS_LEAF = true;
            cursor->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
            cursor->ptr[MAX] = NULL;
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            if (cursor == root) {
                Node *newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            } else {
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

// Insert Operation
void BPTree::insertInternal(int x, Node *cursor, Node *child) {
    if (cursor->size < MAX) {
        int i = 0;
        while (x > cursor->key[i] && i < cursor->size)
            i++;
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    } else {
        Node *newInternal = new Node;
        int virtualKey[MAX + 1];
        Node *virtualPtr[MAX + 2];
        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->key[i];
        }
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        while (x > virtualKey[i] && i < MAX)
            i++;
        for (int j = MAX + 1; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = x;
        for (int j = MAX + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX + 1) / 2;
        newInternal->size = MAX - (MAX + 1) / 2;
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        if (cursor == root) {
            Node *newRoot = new Node;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        } else {
            insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
        }
    }
}