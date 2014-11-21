#include <stdio.h>
#include "tree.h"
#include "tree.c"

int main()
{
    tree_t tr = tree_create(tr, 15);
    add_leaves(&tr, 10, 9);
    go_right(&tr);
    add_leaves(&tr, 18, 32);
    go_right(&tr);
    add_leaves(&tr, 14, 72);
    print_tree(&tr);
    go_ontop(&tr);
    node_clear(&tr);
    print_tree(&tr);
    return 0;
}
