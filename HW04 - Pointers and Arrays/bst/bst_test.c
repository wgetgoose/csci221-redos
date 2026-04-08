#include "bst.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main () {
    bst_tree* test_tree = malloc(sizeof(bst_tree));
    char* test_tree_value = "test";
    add_node(test_tree, test_tree_value);
    // test: check root node created and size
    printf("New tree with root value | %s | and size %d\n",test_tree->root->value, test_tree->size);
    // test: removing root node
    remove_node(test_tree, "k");
    printf("Removed root node, size is %d\n", test_tree->size);
    // let's get serious and add some nodes
    char* test_tree_k = "k";
    char* test_tree_h = "h";
    char* test_tree_n = "n";
    add_node(test_tree, test_tree_k);
    add_node(test_tree, test_tree_h);
    add_node(test_tree, test_tree_n);
    printf("k as root, h left of k, n right of k. check below\n");
    printf("1: %s | 2: %s | 3: %s\n", test_tree->root->value, 
                                    test_tree->root->left_child->value,
                                    test_tree->root->right_child->value);
    char* test_tree_a = "a";
    char* test_tree_j = "j";
    add_node(test_tree, test_tree_a);
    add_node(test_tree, test_tree_j);
    printf("A should be LC of H: %s --> %s\n", test_tree->root->left_child->value,
                                            test_tree->root->left_child->left_child->value);
    // test removal with left and right children
    remove_node(test_tree, "h");
    printf("A should be LC of root: %s --> %s\n", test_tree->root->value,
                                                test_tree->root->left_child->value);
    printf("J should be RC of A: %s --> %s\n", test_tree->root->left_child->value,
                                            test_tree->root->left_child->right_child->value);
    // let's add H back to test deallocation
    add_node(test_tree, test_tree_h);
    dealloc_tree(test_tree);
}