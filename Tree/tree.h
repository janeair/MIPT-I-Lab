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

typedef struct tree_t
{
    node* current;
    int deep;
}
tree_t;

tree_t tree_create (tree_t tree, int source);
node* addleaf (const node* parent, int source);
void add_leaves (const tree_t* tree, int lft_src, int rgt_src);
int print_node(node* current);
void print_tree (const tree_t* tree);
void fprint_tree (tree_t* tree, const char* pathout);
void go_left (tree_t* tree);
void go_right (tree_t* tree);
void go_up (tree_t* tree);
void go_ontop (tree_t* tree);
int node_destr (node* current);
int node_clear (tree_t* tree);
void tree_destr (tree_t* tree);
double tree_pick (const tree_t* tree, char path);

#endif TREE_H_INCLUDED
