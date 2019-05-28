#ifndef __print_jst_node
#define __print_jst_node

#include <cstdio>
#include "../partition.h"

void print_node_elements(JST::Node* node, int BASE) {
    if (node == nullptr)
        return;
    if (BASE == 1) {
        printf("%d ", node->minval);
        return;
    }
    print_node_elements(node->t0, BASE / 2);
    print_node_elements(node->t1, BASE / 2);
}


void print_tree(JST::Node* node, int BASE) {
    if (node == nullptr) {
        printf("() ");
        return;
    }
    if (BASE == 1) {
        printf("%d ", node->minval);
        return;
    }
    printf("{ ");
    print_tree(node->t0, BASE / 2);
    print_tree(node->t1, BASE / 2);
    printf("} ");
}
#endif