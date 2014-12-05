#include <stdio.h>
#include "tree.h"
#include "tree.c"

int main()
{
    tree_t tr = tree_create(tr, 15);
    add_leaves(&tr, 10, 9);
    print_tree(&tr);
    return 0;
}
