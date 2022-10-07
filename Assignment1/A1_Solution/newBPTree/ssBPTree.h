//
// Created by WinnieCMZ on 2022-10-04.
//

#ifndef A1_SOLUTION_NEWBPTREE_H
#define A1_SOLUTION_NEWBPTREE_H
#endif //A1_SOLUTION_NEWBPTREE_H

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>
#include <array>
#include "../DB_lib/dbComponents.h"

using namespace std;

class ssTreeNode {
public:
    const static int m_value = 8;

    friend class ssBPTree;

    string *fieldOne_AsKey;
    int *location_asValue;

    ssTreeNode();

    ssTreeNode **pointer;

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

//    void showBPTree(ssTreeNode*);
//
//    ssTreeNode *getTreeRoot();

    ssTreeNode *searchElm(string target);

    void ramInsertElm(string Key_FieldOneValue, int Value_Location);

    void outsourceInsertElm(string key, string str_f2f3);

    void insertInternalNode(string Key_FieldOneValue, ssTreeNode *cursor, ssTreeNode *child);

    ssTreeNode *findParentNode(ssTreeNode *cursor, ssTreeNode *child);

    void deleteElm();
};

