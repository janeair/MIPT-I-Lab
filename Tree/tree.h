#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>

typedef struct node
{
    int data;
    struct node *right;
    struct node *left;
    struct node *up;
}
node;
// STRUCT OF NODE OF THE TREE

typedef struct tree_t
{
    node* current;
    int deep;
}
tree_t;
// STRUCT OF THE TREE
// DEEP (INT) - DEEP OF THE CURRENT NODE OF THE TREE

tree_t tree_create (tree_t tree, int source);
// CREATE A TREE WITH A TOP NODE (DATA = SOURCE)

node* addleaf (const node* parent, int source);
// ! PRIVATE METHOD ! (PARENT -> ADD_LEAVES)

void add_leaves (const tree_t* tree, int lft_src, int rgt_src);
// ADDS LEFT LEAF (DATA = LFT_SRC) AND RIGHT LEAF (DATA = RGT_SRC)
// DON'T CHANGES CURRENT POINTER (TREE->CURRENT)

int print_node(node* current);
// ! PRIVATE METHOD ! (PARENT -> PRINT_TREE)

void print_tree (const tree_t* tree);
// PRINTS ALL NODES OF TREE (FROM THE BEGINNING)

void fprint_tree (tree_t* tree, const char* pathout);

void go_left (tree_t* tree);
// MOVES TREE POINTER DEEP-LEFT

void go_right (tree_t* tree);
// MOVES TREE POINTER DEEP-RIGHT

void go_up (tree_t* tree);
// MOVES TREE POINTER UP-TO-PARENT

void go_ontop (tree_t* tree);
// MOVES TREE POINTER UP-TO-TOP

int node_destr (node* current);
// ! PRIVATE METHOD ! (PARENT -> TREE_DESTR)

int node_clear (tree_t* tree);
// TURNS CURRENT NODE TO A LEAF
// DON'T CHANGES CURRENT POINTER (TREE->CURRENT)
// RETURNS :
// 0 - IF GOOD DONE
// 1 - IF THIS NODE IS A LEAF

double tree_pick (const tree_t* tree, char path);
// RETURNS DATA FROM NODE ON THE PATH
// ARGUMENT PATH:
// 'C' = CURRENT NODE
// 'R' = RIGHT NODE
// 'L' = LEFT NODE

void tree_destr (tree_t* tree);
// DELETES ALL NODES FROM TREE AND TREE AT ALL

#endif TREE_H_INCLUDED
