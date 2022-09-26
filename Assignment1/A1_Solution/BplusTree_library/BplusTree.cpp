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
void BplusTree::searchElm(int x) {
    if (root == NULL) {
        cout << "There is no element inside the tree" << endl;
    } else {
        TreeNode *cursor = root;
        while (cursor->isLeaf == false) {
            for (int idx = 0; idx < cursor->size; idx++) {
                if (x < cursor->key[idx]) {
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
            if (cursor->key[index] == x) {
                cout << "Found\n";
                return;
            }
        }
        cout << "Not found\n";
    }
}
