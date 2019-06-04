/* AVL TREE SAMPLE RUN
 **/

/** preprocessor directives **/
#include <stdio.h>
#include "rb-tree.h"

int main() {
  Rb_tree tree;
  
  init(&tree);
  
  insert(&tree, 5);
  printf("After inserting 5 the tree height = %u and size = %u\n", height(tree), size(tree));
  return 0;
}
