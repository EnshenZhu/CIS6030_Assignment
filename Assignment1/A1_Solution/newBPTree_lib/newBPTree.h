//
// Created by WinnieCMZ on 2022-10-04.
//

#ifndef A1_SOLUTION_NEWBPTREE_H
#define A1_SOLUTION_NEWBPTREE_H

class newTreeNode {
    friend class newTreeNode;

    newTreeNode();

    int *key;
    int size;

    newTreeNode *(*pointer);
    bool isLeaf;
};

class newBPTree {

};


#endif //A1_SOLUTION_NEWBPTREE_H
