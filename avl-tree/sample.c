/* AVL TREE SAMPLE RUN
 **/

/** preprocessor directives **/
#include <stdio.h>
#include "avl-tree.h"

int main() {
  Avl_tree tree;

  /* classic AVL tree (g = 1) */
  init(&tree, 1);
  
  insert(&tree, 5);
  printf("After inserting 5 the tree height = %u and size = %u\n", height(tree), size(tree));
  return 0;
}
