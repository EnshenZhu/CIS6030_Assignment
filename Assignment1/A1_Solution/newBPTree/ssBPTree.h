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

int m_value = 8;

class ssTreeNode {
public:

    friend class ssBPTree;

    ssTreeNode();

    vector<string> fieldOne_AsKey;
    vector<int> location_asValue;
    vector<ssTreeNode *> child;

    ssTreeNode *nextNewTreeNode;

    ssTreeNode *(*pointer);

    short maxKeySize();

    short minKeySize();

    short currentKeySize;

    bool isLeaf = true;

    bool isFull();
};

class ssBPTree {
public:
    ssBPTree();

    ssTreeNode *root;

    void buildTree(string RecordContent);

    ssTreeNode* searchElm(string);

    void insertElm(string,int);
    void insertInternalNode();

    void deleteElm();
};

