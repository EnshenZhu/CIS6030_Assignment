//
// Created by WinnieCMZ on 2022-10-04.
//

#ifndef A1_SOLUTION_NEWBPTREE_H
#define A1_SOLUTION_NEWBPTREE_H
#endif //A1_SOLUTION_NEWBPTREE_H

#include <vector>
#include <string>
#include "../DB_lib/dbComponents.h"

using namespace std;

class ssTreeNode {

    int m_value = 8;

    vector<string> fieldOne_AsKey;
    vector<string> fieldTwoThree_AsValue;
    vector<ssTreeNode *> child;

    ssTreeNode *nextNewTreeNode;

    short maxKeySize();

    short minKeySize();

    short currentKeySize();

    bool isLeaf = true;

    bool isFull();
};

class ssBPTree {
    void buildTree(string RecordContent);

    void searchElm();

    void insertElm();

    void deleteElm();
};

