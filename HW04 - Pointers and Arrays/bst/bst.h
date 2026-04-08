#ifndef BST_H
#define BST_H
#include <stdint.h>

typedef struct bst_node {
    char* value;
    struct bst_node* left_child;
    struct bst_node* right_child;
} bst_node;

typedef struct bst_tree {
    struct bst_node* root;
    uint32_t size;
} bst_tree;

enum str_state {
    A_LESS_B,
    A_GREATER_B,
    EQUAL 
};

enum str_state string_compare (char* a, char* b);

void add_node (bst_tree* tree, char* str);

uint8_t remove_node (bst_tree* tree, char* str);

void dealloc_tree (bst_tree* tree);

#endif