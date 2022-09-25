//
// Created by winni on 2022-09-25.
//

#ifndef A1_SOLUTION_BPLUSTREE_H
#define A1_SOLUTION_BPLUSTREE_H

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// config the maximum of nodes to be 8 <m>, and minimum to be 4 <m/2>
// config the maximum of keys to be 7 <m-1> and minimum to be 3 <m/2-1>
short MAX = 8;

// config the tree node
class TreeNode {

public:
    TreeNode();

    int *key, size;
    TreeNode **pointer;

    bool is_leaf;

    friend class BplusTree;

};

// config the B plus Tree
class BplusTree {
public:
    BplusTree();

    TreeNode *getRoot();

    TreeNode *root;

    TreeNode *findParentNode(TreeNode *, TreeNode *);

    void insertInternalNode(int, TreeNode *, TreeNode *);

    void searchElm(int targetValue);

    void insertElm(int targetValue);

    void showElm(int targetValue);

};


#endif //A1_SOLUTION_BPLUSTREE_H
