//
// Created by winni on 2022-09-25.
//

#ifndef A1_SOLUTION_BPLUSTREE_H
#define A1_SOLUTION_BPLUSTREE_H


#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

// config the maximum of pointers to be 8 <m>, and minimum to be 4 <m/2>
// config the maximum of keys to be 7 <m-1> and minimum to be 3 <m/2-1>
const static int MAX = 8;

// config the tree node
class TreeNode {

public:
    friend class BplusTree;

    TreeNode();

    int *key;
    int size;

    TreeNode *(*pointer);
    bool isLeaf;

};

// config the B plus Tree
class BplusTree {
public:
    BplusTree();

    TreeNode *getRoot();

    TreeNode *root;

    TreeNode *findParentNode(TreeNode *cursor, TreeNode *child);

    TreeNode *findChildNode(TreeNode *cursor);

    void showElm(int targetValue);

    void searchElm(int targetElement);

    void insertElm(int target);

    void insertInternalNode(int target, TreeNode *cursor, TreeNode *child);

};


#endif //A1_SOLUTION_BPLUSTREE_H
