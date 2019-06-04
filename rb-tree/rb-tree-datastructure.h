/* RB TREE DATASTRUCTURE DEFINITION
 **/

/** conditional compilation **/
#ifndef RB_TREE_DATASTRUCTURE_H
#define RB_TREE_DATASTRUCTURE_H

typedef enum color {
  BLACK= 0,
  RED
} Color;

/* data
 *   = integer data
 * height
 *   = the height of curr node
 * color
 *   = red/black (1/0)
 * *left, *right
 *   = the left and right children
 **/
typedef struct node {
  int data;
  int height;
  Color color;
  struct node *left, *right;
} Node;

/* size
 *   = num elements in tree, [0,infty)
 * *root
 *   = pointer to root node in tree
 **/
typedef struct rb_tree {
  int size;
  Node *root;
} Rb_tree;

#endif
