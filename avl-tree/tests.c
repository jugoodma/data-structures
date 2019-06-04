/* AVL TREE TESTS
 **/

/** preprocessor directives **/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl-tree.h"
#include "memory-checking.h"

int main() {
  Avl_tree tree;
#if !defined(ENABLE_VALGRIND)
  setup_memory_checking();
#endif
  init(&tree, 1);
  /* exit(2); */
  clear(&tree);
#if !defined(ENABLE_VALGRIND)
  check_heap();
#endif
  assert(size(tree) == 0);
  assert(height(tree) == -1);

  printf("All assertions were wildly successful!\n");
  return 0;
}
