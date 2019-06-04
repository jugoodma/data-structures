/* AVL TREE DATASTRUCTURE DEFINITION
 **/

/** conditional compilation **/
#ifndef AVL_TREE_DATASTRUCTURE_H
#define AVL_TREE_DATASTRUCTURE_H

/* data
 *   = integer data
 * height
 *   = the height of curr node
 * *left, *right
 *   = the left and right children
 **/
typedef struct node {
  int data;
  int height;
  struct node *left, *right;
} Node;

/* size
 *   = num elements in tree, [0,infty)
 * g
 *   = the imbalance parameter
 * *root
 *   = pointer to root node in tree
 **/
typedef struct avl_tree {
  int size;
  int g;
  Node *root;
} Avl_tree;

#endif
