#ifndef TREE_C_INCLUDED
#define TREE_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

tree_t tree_create (tree_t tree, int source)

// CREATE A TREE WITH A TOP NODE (DATA = SOURCE)

{
    tree.current = (node*)calloc(1, sizeof(node));
    tree.current->up = NULL;
    tree.current->right = NULL;
    tree.current->left = NULL;
    tree.current->data = source;
    tree.deep = 0;
    return tree;
}

double tree_pick (const tree_t* tree, char path)

// RETURNS DATA FROM NODE ON THE PATH
// ARGUMENT PATH:
// 'C' = CURRENT NODE
// 'R' = RIGHT NODE
// 'L' = LEFT NODE

{
    assert(tree != 0);
    if (path == 'L' || path == 'l')
        if (tree->current->left != 0)
            return tree->current->left->data;
        else
        {
            printf ("- No Left Node -\n");
            return 0.5;
        }
    if (path == 'R' || path == 'r')
        if (tree->current->right != 0)
            return tree->current->right->data;
        else
        {
            printf ("= No Right Node -\n");
            return 0.5;
        }
    if (path == 'C' || path == 'c')
        if (tree->current != 0)
            return tree->current->data;
        else
        {
            printf ("- Tree is free -\n");
            return 0.5;
        }
    printf ("- Wrong Argument Format -\n");
    return 0.5;
}

node* addleaf (const node* parent, int source)

// ! PRIVATE METHOD ! (PARENT -> ADD_LEAVES)

{
    node* leaf = (node*)calloc(1, sizeof(node));
    assert(leaf != 0);
    leaf->left = 0;
    leaf->right = 0;
    leaf->up = parent;
    leaf->data = source;
    return leaf;
}

void add_leaves (const tree_t* tree, int lft_src, int rgt_src)

// ADDS LEFT LEAF (DATA = LFT_SRC) AND RIGHT LEAF (DATA = RGT_SRC)
// DON'T CHANGES CURRENT POINTER (TREE->CURRENT)

{
    assert(tree != 0);
    if (tree->current->right != 0 || tree->current->left != 0)
    {
        printf("- This Node Isn't a Leaf -\n");
        return;
    }
    tree->current->left = addleaf(tree->current, lft_src);
    tree->current->right = addleaf(tree->current, rgt_src);
}

void go_left (tree_t* tree)

// MOVES TREE POINTER DEEP-LEFT

{
    assert(tree != 0);
    if (tree->current == 0)
    {
        printf("- Wrong Address or Tree didn't exist -\n");
        return;
    }
    if (tree->current->left != 0)
    {
        tree->current = tree->current->left;
        tree->deep++;
    }
    else
        printf("- It's a Leaf -\n");
}

void go_right (tree_t* tree)

// MOVES TREE POINTER DEEP-RIGHT

{
    assert(tree != 0);
    if (tree->current == 0)
    {
        printf("- Wrong Address or Tree didn't exist -\n");
        return;
    }
    if (tree->current->right != 0)
    {
        tree->current = tree->current->right;
        tree->deep++;
    }
    else
        printf("- It's a Leaf -\n");
}

void go_up (tree_t* tree)

// MOVES TREE POINTER UP-TO-PARENT

{
    assert(tree != 0);
    if (tree->current == 0)
    {
        printf("- Wrong Address or Tree didn't exist -\n");
        return;
    }
    if (tree->current->up != 0)
    {
        tree->current = tree->current->up;
        tree->deep--;
    }
    else
        printf("- It's a Top -\n");
}

void go_ontop (tree_t* tree)

// MOVES TREE POINTER UP-TO-TOP

{
    while (tree->current->up != 0)
        go_up(tree);
    if (tree->deep != 0)
    {
        printf("! Something Goes Wrong !\n");
        printf("Tree Deep is %d but must be 0\n", tree->deep);
    }
}

int print_node(node* current)

// ! PRIVATE METHOD ! (PARENT -> PRINT_TREE)

{
    if (current != 0)
        printf("(%d",current->data);
    else
        return 1;
    if (current->left != 0)
    {
        printf(" ");
        print_node(current->left);
    }
    if (current->right != 0)
    {
        printf(" ");
        print_node(current->right);
    }
    printf(")");
    return 0;
}

void print_tree(const tree_t* tree)

// PRINTS ALL NODES OF TREE (FROM THE BEGINNING)

{
    int i;
    int err;
    assert(tree != 0);
    node* temp = tree->current;
    if (temp == 0)
    {
        printf("- Tree Not Found -\n");
        return;
    }
    for (i=0; i<tree->deep; i++)
        temp = temp->up;
    if (temp->up != 0) printf("! Not a full Tree is printed !\n");
    err = print_node(temp);
    if (err == 1)
        printf("- Wrong Address -\n");
    printf("\n");
}

int node_clear (tree_t* tree)

// TURNS CURRENT NODE TO A LEAF
// DON'T CHANGES CURRENT POINTER (TREE->CURRENT)
// RETURNS :
// 0 - IF GOOD DONE
// 1 - IF THIS NODE IS A LEAF

{
    assert(tree != 0);
    if (tree->current->left != 0 && tree->current->right != 0)
    {
        node_destr(tree->current->left);
        node_destr(tree->current->right);
        tree->current->left = 0;
        tree->current->right = 0;
        return 0;
    }
    else
    {
        printf("- It's a Leaf -\n");
        return 1;
    }
}

int node_destr (node* current)

// ! PRIVATE METHOD ! (PARENT -> TREE_DESTR)

{
    if (current->left != 0)
        node_destr(current->left);
    if (current->right != 0)
        node_destr(current->right);
    if (current != 0)
        free(current);
    else
        return 1;
    return 0;
}

void tree_destr (tree_t* tree)

// DELETES ALL NODES FROM TREE AND TREE AT ALL

{
    int i;
    for (i=0; i<tree->deep; i++)
        tree->current = tree->current->up;
    node_destr(tree->current);
    free(tree);
}

#endif TREE_C_INCLUDED
