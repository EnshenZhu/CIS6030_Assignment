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
void BplusTree::searchElm(int target) {
    if (root == NULL) {
        // if there is no root, the tree does not exist
        cout << "The tree is empty." << endl;
    } else {
        TreeNode *cursor = root; // start search from the root

        while (cursor->isLeaf == false) {
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

        for (int index = 0; index < cursor->size; index++) {
            if (cursor->key[index] == target) {
                cout << target << " is found " << endl;
                return;
            }
        }
        cout << target << " cannot be found inside the tree" << endl;
    }
}

// Find the parent
TreeNode *BplusTree::findParentNode(TreeNode *cursor, TreeNode *child) {
    TreeNode *parentNode;
    if (cursor->isLeaf || (cursor->pointer[0])->isLeaf) {
        return NULL;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->pointer[i] == child) {
            parentNode = cursor;
            return parentNode;
        } else {
            parentNode = findParentNode(cursor->pointer[i], child);
            if (parentNode != NULL)
                return parentNode;
        }
    }
    return parentNode;
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

//void BplusTree::remove(int x) {
//    if (root == NULL) {
//        cout << "Tree empty\n";
//    } else {
//        Node *cursor = root;
//        Node *parent;
//        int leftSibling, rightSibling;
//        while (cursor->IS_LEAF == false) {
//            for (int i = 0; i < cursor->size; i++) {
//                parent = cursor;
//                leftSibling = i - 1;
//                rightSibling = i + 1;
//                if (x < cursor->key[i]) {
//                    cursor = cursor->ptr[i];
//                    break;
//                }
//                if (i == cursor->size - 1) {
//                    leftSibling = i;
//                    rightSibling = i + 2;
//                    cursor = cursor->ptr[i + 1];
//                    break;
//                }
//            }
//        }
//        bool found = false;
//        int pos;
//        for (pos = 0; pos < cursor->size; pos++) {
//            if (cursor->key[pos] == x) {
//                found = true;
//                break;
//            }
//        }
//        if (!found) {
//            cout << "Not found\n";
//            return;
//        }
//        for (int i = pos; i < cursor->size; i++) {
//            cursor->key[i] = cursor->key[i + 1];
//        }
//        cursor->size--;
//        if (cursor == root) {
//            for (int i = 0; i < MAX + 1; i++) {
//                cursor->ptr[i] = NULL;
//            }
//            if (cursor->size == 0) {
//                cout << "Tree died\n";
//                delete[] cursor->key;
//                delete[] cursor->ptr;
//                delete cursor;
//                root = NULL;
//            }
//            return;
//        }
//        cursor->ptr[cursor->size] = cursor->ptr[cursor->size + 1];
//        cursor->ptr[cursor->size + 1] = NULL;
//        if (cursor->size >= (MAX + 1) / 2) {
//            return;
//        }
//        if (leftSibling >= 0) {
//            Node *leftNode = parent->ptr[leftSibling];
//            if (leftNode->size >= (MAX + 1) / 2 + 1) {
//                for (int i = cursor->size; i > 0; i--) {
//                    cursor->key[i] = cursor->key[i - 1];
//                }
//                cursor->size++;
//                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
//                cursor->ptr[cursor->size - 1] = NULL;
//                cursor->key[0] = leftNode->key[leftNode->size - 1];
//                leftNode->size--;
//                leftNode->ptr[leftNode->size] = cursor;
//                leftNode->ptr[leftNode->size + 1] = NULL;
//                parent->key[leftSibling] = cursor->key[0];
//                return;
//            }
//        }
//        if (rightSibling <= parent->size) {
//            Node *rightNode = parent->ptr[rightSibling];
//            if (rightNode->size >= (MAX + 1) / 2 + 1) {
//                cursor->size++;
//                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
//                cursor->ptr[cursor->size - 1] = NULL;
//                cursor->key[cursor->size - 1] = rightNode->key[0];
//                rightNode->size--;
//                rightNode->ptr[rightNode->size] = rightNode->ptr[rightNode->size + 1];
//                rightNode->ptr[rightNode->size + 1] = NULL;
//                for (int i = 0; i < rightNode->size; i++) {
//                    rightNode->key[i] = rightNode->key[i + 1];
//                }
//                parent->key[rightSibling - 1] = rightNode->key[0];
//                return;
//            }
//        }
//        if (leftSibling >= 0) {
//            Node *leftNode = parent->ptr[leftSibling];
//            for (int i = leftNode->size, j = 0; j < cursor->size; i++, j++) {
//                leftNode->key[i] = cursor->key[j];
//            }
//            leftNode->ptr[leftNode->size] = NULL;
//            leftNode->size += cursor->size;
//            leftNode->ptr[leftNode->size] = cursor->ptr[cursor->size];
//            removeInternal(parent->key[leftSibling], parent, cursor);
//            delete[] cursor->key;
//            delete[] cursor->ptr;
//            delete cursor;
//        } else if (rightSibling <= parent->size) {
//            Node *rightNode = parent->ptr[rightSibling];
//            for (int i = cursor->size, j = 0; j < rightNode->size; i++, j++) {
//                cursor->key[i] = rightNode->key[j];
//            }
//            cursor->ptr[cursor->size] = NULL;
//            cursor->size += rightNode->size;
//            cursor->ptr[cursor->size] = rightNode->ptr[rightNode->size];
//            cout << "Merging two leaf nodes\n";
//            removeInternal(parent->key[rightSibling - 1], parent, rightNode);
//            delete[] rightNode->key;
//            delete[] rightNode->ptr;
//            delete rightNode;
//        }
//    }
//}
//void BPTree::removeInternal(int x, Node *cursor, Node *child) {
//    if (cursor == root) {
//        if (cursor->size == 1) {
//            if (cursor->ptr[1] == child) {
//                delete[] child->key;
//                delete[] child->ptr;
//                delete child;
//                root = cursor->ptr[0];
//                delete[] cursor->key;
//                delete[] cursor->ptr;
//                delete cursor;
//                cout << "Changed root node\n";
//                return;
//            } else if (cursor->ptr[0] == child) {
//                delete[] child->key;
//                delete[] child->ptr;
//                delete child;
//                root = cursor->ptr[1];
//                delete[] cursor->key;
//                delete[] cursor->ptr;
//                delete cursor;
//                cout << "Changed root node\n";
//                return;
//            }
//        }
//    }
//    int pos;
//    for (pos = 0; pos < cursor->size; pos++) {
//        if (cursor->key[pos] == x) {
//            break;
//        }
//    }
//    for (int i = pos; i < cursor->size; i++) {
//        cursor->key[i] = cursor->key[i + 1];
//    }
//    for (pos = 0; pos < cursor->size + 1; pos++) {
//        if (cursor->ptr[pos] == child) {
//            break;
//        }
//    }
//    for (int i = pos; i < cursor->size + 1; i++) {
//        cursor->ptr[i] = cursor->ptr[i + 1];
//    }
//    cursor->size--;
//    if (cursor->size >= (MAX + 1) / 2 - 1) {
//        return;
//    }
//    if (cursor == root)
//        return;
//    Node *parent = findParent(root, cursor);
//    int leftSibling, rightSibling;
//    for (pos = 0; pos < parent->size + 1; pos++) {
//        if (parent->ptr[pos] == cursor) {
//            leftSibling = pos - 1;
//            rightSibling = pos + 1;
//            break;
//        }
//    }
//    if (leftSibling >= 0) {
//        Node *leftNode = parent->ptr[leftSibling];
//        if (leftNode->size >= (MAX + 1) / 2) {
//            for (int i = cursor->size; i > 0; i--) {
//                cursor->key[i] = cursor->key[i - 1];
//            }
//            cursor->key[0] = parent->key[leftSibling];
//            parent->key[leftSibling] = leftNode->key[leftNode->size - 1];
//            for (int i = cursor->size + 1; i > 0; i--) {
//                cursor->ptr[i] = cursor->ptr[i - 1];
//            }
//            cursor->ptr[0] = leftNode->ptr[leftNode->size];
//            cursor->size++;
//            leftNode->size--;
//            return;
//        }
//    }
//    if (rightSibling <= parent->size) {
//        Node *rightNode = parent->ptr[rightSibling];
//        if (rightNode->size >= (MAX + 1) / 2) {
//            cursor->key[cursor->size] = parent->key[pos];
//            parent->key[pos] = rightNode->key[0];
//            for (int i = 0; i < rightNode->size - 1; i++) {
//                rightNode->key[i] = rightNode->key[i + 1];
//            }
//            cursor->ptr[cursor->size + 1] = rightNode->ptr[0];
//            for (int i = 0; i < rightNode->size; ++i) {
//                rightNode->ptr[i] = rightNode->ptr[i + 1];
//            }
//            cursor->size++;
//            rightNode->size--;
//            return;
//        }
//    }
//    if (leftSibling >= 0) {
//        Node *leftNode = parent->ptr[leftSibling];
//        leftNode->key[leftNode->size] = parent->key[leftSibling];
//        for (int i = leftNode->size + 1, j = 0; j < cursor->size; j++) {
//            leftNode->key[i] = cursor->key[j];
//        }
//        for (int i = leftNode->size + 1, j = 0; j < cursor->size + 1; j++) {
//            leftNode->ptr[i] = cursor->ptr[j];
//            cursor->ptr[j] = NULL;
//        }
//        leftNode->size += cursor->size + 1;
//        cursor->size = 0;
//        removeInternal(parent->key[leftSibling], parent, cursor);
//    } else if (rightSibling <= parent->size) {
//        Node *rightNode = parent->ptr[rightSibling];
//        cursor->key[cursor->size] = parent->key[rightSibling - 1];
//        for (int i = cursor->size + 1, j = 0; j < rightNode->size; j++) {
//            cursor->key[i] = rightNode->key[j];
//        }
//        for (int i = cursor->size + 1, j = 0; j < rightNode->size + 1; j++) {
//            cursor->ptr[i] = rightNode->ptr[j];
//            rightNode->ptr[j] = NULL;
//        }
//        cursor->size += rightNode->size + 1;
//        rightNode->size = 0;
//        removeInternal(parent->key[rightSibling - 1], parent, rightNode);
//    }
//}