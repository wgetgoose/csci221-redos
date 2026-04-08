#include "bst.h"
#include <stdint.h>
#include <stdlib.h>

// only needed for debug print statements
#include <stdio.h>

enum str_state string_compare (char* a, char* b) {
    enum str_state retval = EQUAL;
    uint32_t i = 0;
    // infinite loop badness
    while (1) {
        // if user has passed two equal strings,
        // return. prevents infinite loop
        if ((a[i] == b[i]) && (a[i] == '\0')) {
            retval = EQUAL;
            return retval;
        }
        if (a[i] > b[i]) {
            retval = A_GREATER_B;
            return retval;
        } else if (a[i] < b[i]) {
            retval = A_LESS_B;
            return retval;
        // else a[i] == b[i] and we move to the next character
        } else {
            i++;
            continue;
        }
    }
    return retval;
}

// helper function. malloc new node
bst_node* node_init (char* str) {
    bst_node* retval = malloc(sizeof(bst_node));
    // gotta get the string size for a malloc deep copy
    uint32_t i = 0;
    while (str[i] != '\0') {
        i++; 
    }
    // because loop does not run for str[i] == '\0'
    // we add one to account for nul char
    i += 1;
    retval->value = malloc(sizeof(char) * i);
    for (uint32_t j = 0; j <= i; j++) {
        retval->value[j] = str[j];
    }
    retval->left_child = NULL;
    retval->right_child = NULL;
    return retval;
}

// because the homework specifies that 
// we pass a tree to the add_node function,
// we need this recursive function
// to actually do the work
void traverse_tree_add (bst_tree* tree, bst_node* root, bst_node* new_node) {
    // null checks
    if ((tree == NULL) || (new_node == NULL)) {
        return;
    }
    // case: new tree!
    // root == NULL in this case, so not checked above
    if (tree->root == NULL) {
        tree->root = new_node;
        tree->size = 1;
        return;
    }
    enum str_state comparison = string_compare(root->value, new_node->value);
    switch (comparison)
    {
    case A_LESS_B:
        // root < string, so we look at right side
        if (root->right_child == NULL) {
            root->right_child = new_node;
            tree->size += 1;
            return;
        } else {
            traverse_tree_add(tree, root->right_child, new_node);
        }
        break;
    case A_GREATER_B:
        // root > string, so we look at left side
        if (root->left_child == NULL) {
            root->left_child = new_node;
            tree->size += 1;
            return;
        } else {
            traverse_tree_add(tree, root->left_child, new_node);
        }
        break;
    case EQUAL:
        // REDO: In the case that string already exists,
        // free and return.
        free(new_node->value);
        free(new_node);
        return;
        break;
    default:
        break;
    }
}

void add_node (bst_tree* tree, char* str) {
    // REDO: Add check for null string
    if (str == NULL) {
        return;
    }
    // REDO: Check for null tree
    if (tree == NULL) {
        return;
    }
    bst_node* new_node = node_init(str);
    traverse_tree_add(tree, tree->root, new_node);
    return;
}

// i'm sorry grader,
// bst's are hard
// --------------
// return 1 if node removed
// return 0 if not
uint8_t traverse_tree_remove (bst_node* root_parent, bst_node* root, char* str) {
    // case: removing root and root has no children
    if ((root_parent == NULL) && (root->left_child == NULL) && (root->right_child == NULL)) {
        free(root);
        return 1;
    }
    enum str_state comparison = string_compare(root->value, str);
    uint8_t retval = 0;
    switch (comparison)
    {
        case A_GREATER_B:
            // case: node not in tree and root->value > str
            if (root->left_child == NULL) {
                retval = 0;
                break;
            } else {
                // case: keep looking to the left 
                return traverse_tree_remove(root, root->left_child, str);
            }
            break;
        case A_LESS_B:
            // case: node not in tree and root->value < str
            if (root->right_child == NULL) {
                retval = 0;
                break;
            } else {
                // case: keep looking to the right
                return traverse_tree_remove(root, root->right_child, str);               
            }
            break;
        case EQUAL:
            // case 1: node to be removed has
            // no children
            if ((root->left_child == NULL) && (root->right_child == NULL)) {
                // removing left child of the parent
                if (root_parent->left_child == root) {
                    root_parent->left_child = NULL;
                    free(root);
                    retval = 1;
                    break;
                }
                // could use an "else" here, but this code is clearer
                // removing right child of the parent
                if (root_parent->right_child == root) {
                    root_parent->right_child = NULL;
                    free(root);
                    retval = 1;
                    break;
                }
            }
            // case 2: node to be removed has right children, but no left children
            if ((root->left_child == NULL) && (root->right_child != NULL)) {
                // shifting right node of root to left node of root_parent
                if (root_parent->left_child == root) {
                    root_parent->left_child = root->right_child;
                    free(root);
                    retval = 1;
                    break;
                }
                if (root_parent->right_child == root) {
                    root_parent->right_child = root->right_child;
                    free(root);
                    retval = 1;
                    break;
                }
            }
            // case 3: node to be removed has left children AND possibly right children
            // we are going to append the right child of root to the leftmost child
            // of the left child of the node we are deleting
            bst_node* leftmost_child = root->left_child;
            while (leftmost_child->left_child != NULL) {
                leftmost_child = leftmost_child->left_child;
            }
            leftmost_child->right_child = root->right_child;
            if (root_parent->left_child == root) {
                root_parent->left_child = root->left_child;
            } else if (root_parent->right_child == root) {
                root_parent->right_child = root->left_child;
            }
            free(root);
            retval = 1;
    }
    return retval;
}

uint8_t remove_node (bst_tree* tree, char* str) {
    // REDO: Check for null tree and string
    if (tree == NULL) {
        return 0;
    }
    if (str == NULL) {
        return 0;
    }
    // passing NULL is bad but it's how this function works and the assignment is due
    // in less than 4 hours so
    uint8_t result = traverse_tree_remove(NULL, tree->root, str);
    if (result == 1) {
        tree->size = (tree->size) - 1;
        // REDO: If we removed the root node
        if (tree->size == 0) {
            tree->root = NULL;
        }
        return 1;
    } else {
        return 0;
    }
}

void traverse_tree_dealloc(bst_node* root_parent, bst_node* root) {
    if (root->left_child != NULL) {
        traverse_tree_dealloc(root, root->left_child);
    } 
    if (root->right_child != NULL) {
        traverse_tree_dealloc(root, root->right_child);
    }
    if (root_parent == NULL) {
        // case: deallocating root node
        // DEBUG PRINT
        // printf("Deallocating root node with value %s\n", root->value); 
        free(root);
        return;
    }
    if (root_parent->left_child == root) {
        root_parent->left_child = NULL;
        // DEBUG PRINT
        // printf("Deallocating left child of %s, which is %s\n", root_parent->value, root->value);
        
        // REDO: Free string as well as node
        free(root->value);
        free(root);
        return;
    }
    if (root_parent->right_child == root) {
        // DEBUG PRINT
        // printf("Deallocating right child of %s, which is %s\n", root_parent->value, root->value);
        root_parent->right_child = NULL;
        //REDO: Free string as well as node
        free(root->value);
        free(root);
        return;
    }
}
void dealloc_tree(bst_tree* tree) {
    // REDO: Check if tree is null
    if (tree == NULL) {
        return;
    }
    traverse_tree_dealloc(NULL, tree->root);
    free(tree);
    return;
}