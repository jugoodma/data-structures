/* RB TREE FUNCTION DEFINITIONS
**/

#if !defined(RB_TREE_H)
#define RB_TREE_H

#include "rb-tree-datastructure.h"

void init(Rb_tree *const tree);
int search(Rb_tree *const tree, int data);
int insert(Rb_tree *const tree, int data);
int delete(Rb_tree *const tree, int data);
int size(Rb_tree tree);
int height(Rb_tree tree);
void clear(Rb_tree *const tree);

#endif
