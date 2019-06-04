/* RB TREE IMPLEMENTATION
 * 
 * Left-leaning rb-tree (red links must go left)
 *
 * Justin Goodman
 **/

/** preprocessor directives **/
#include <stdlib.h>
#include "rb-tree.h"

/** static func defns **/
static int n_height(Node *const n);
static int max(int a, int b);
static Node *insert_rec(Node *n, int data, int *err);
static Node *delete_rec(Node *n, int data, int *err);
/* static int inorder_successor(Node *n); */
static Node *rotateL(Node *n);
static Node *rotateR(Node *n);
static void flipColors(Node *n);
static int isRed(Node *n);
static void clear_rec(Node *n);

/** functions **/

/* NOTES:
 * assume all memory allocations succeed
 *
 * I'm rusty in C,
 *   int const *ptr; // ptr is a pointer to constant int
 *   int *const ptr; // ptr is a constant pointer to int
 **/

static int n_height(Node *const n) {
  int result = -1;
  if (n != NULL)
    result= n->height;
  return result;
}

static int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

static Node *rotateL(Node *n) {
  /* n should never be NULL */
  Node *t= n->right;
  n->right= t->left;
  t->left= n;
  t->left->color= RED;
  n->height= n_height(n->right) + 1; /* TODO: check this */
  return t;
}

static Node *rotateR(Node *n) {
  /* n should never be NULL */
  Node *t= n->left;
  n->left= t->right;
  t->right= n;
  t->right->color= RED;
  n->height = n_height(n->left) + 1; /* TODO: check this */
  return t;
}

static void flipColors(Node *n) {
  /* n should be BLACK, and have two RED children */
  n->left->color= BLACK;
  n->right->color= BLACK;
  n->color= RED;
}

static int isRed(Node *n) {
  if (n == NULL)
    return 0;
  return n->color;
}

/*
static int inorder_successor(Node *n) {
  // n, and n->right, should never be NULL  /
  n= n->right;
  while (n->left != NULL)
    n= n->left;
  return n->data;
}
*/

/* void init
 * Does:
 *   initializes a new RB Tree
 * Takes:
 *   Rb_tree *const tree
 *     the tree we are initializing
 * Returns:
 *   void
 **/

void init(Rb_tree *const tree) {
  if (tree != NULL) {
    tree->size= 0;
    tree->root= NULL;
  }
}

/* int search
 * Does:
 *   searches the given RB tree for data
 *   (standard binary search)
 * Takes:
 *   Rb_tree *const tree
 *     the tree we are searching
 *   int data
 *     the key we want to find
 * Returns:
 *   0 if NULL tree or data not in tree
 *   1 if data is contained in the tree
 **/

int search(Rb_tree *const tree, int data) {
  int result= 0;
  if (tree != NULL) {
    Node *n= tree->root;
    while (n != NULL && result == 0) {
      if (data < n->data)
	n= n->left;
      else if (data > n->data)
	n= n->right;
      else
	result= 1;
    }
  }
  return result;
}

/* int insert
 * Does:
 *   inserts the given integer into the RB tree
 *   maintains O(2 * log_2(n)) height via RB rotations
 * Notes:
 *   we do not add duplicates
 * Takes:
 *   Rb_tree *const tree
 *     the tree that we are inserting data
 *   int data
 *     the data we are inserting
 * Returns:
 *   0 if any pointer was NULL, if any malloc did not work, or
 *     if data was already in the tree
 *   1 if we successfully added data to the tree
 **/

int insert(Rb_tree *const tree, int data) {
  int result= 0;
  /* NULL pointer check */
  if (tree != NULL) {
    result= 1;
    tree->root= insert_rec(tree->root, data, &result);
    if (result) {
      tree->size++;
      tree->root->color= BLACK;
    }
  }
  return result;
}

/* insert recursive subroutine */
static Node *insert_rec(Node *n, int data, int *err) {
  /* recursive base-case */
  if (n == NULL) {
    /* create new Node */
    Node *new= malloc(sizeof(Node));
    /* malloc check */
    if (new != NULL) {
      new->data= data;
      new->height= 0;
      new->color= RED;
      new->left= NULL;
      new->right= NULL;
    } else {
      /* set the error to 0 */
      *err= 0;
    }
    return new;
  }
  /* recursive step */
  if (data < n->data) {
    /* go left */
    n->left= insert_rec(n->left, data, err);
  } else if (data > n->data) {
    /* go right */
    n->right= insert_rec(n->right, data, err);
  } else {
    /* don't insert a duplicate */
    *err= 0;
    return n;
  }
  /* re-balance tree */
  if (isRed(n->right) && !isRed(n->left))
    n= rotateL(n);
  if (isRed(n->left) && isRed(n->left->left))
    n= rotateR(n);
  if (isRed(n->left) && isRed(n->right))
    flipColors(n);
  n->height= max(n_height(n->left), n_height(n->right)) + 1;
  return n;
}

/* int delete (NOT IMPLEMENTED)
 * Does:
 * 
 * Takes:
 * 
 * Returns:
 *   0 if fail
 *   1 if success
 **/

int delete(Rb_tree *const tree, int data) {
  int result= 0;
  if (tree != NULL && search(tree, data)) {
    tree->root= delete_rec(tree->root, data, &result);
    /* tree->size--; */
  }
  return result;
}

/* delete recursive subroutine */
static Node *delete_rec(Node *n, int data, int *err) {
  *err= 0;
  return n;
}

/* int size
 * Does:
 *   gives the number of nodes in the tree
 * Takes:
 *   Rb_tree tree
 *     the tree we are examining
 * Returns:
 *   the number of elements in the tree
 **/
int size(Rb_tree tree) {
  return tree.size;
}

/* int height
 * Does:
 *   finds the height of the given tree
 *   this is a simple lookup since all heights are stored
 *   in the nodes
 * Notes:
 *   Height is recursively defined as
 *   H(NULL) = -1
 *   H(T) = max(H(T_L), H(T_R)) + 1
 * Takes:
 *   Rb_tree tree
 *     the tree we are examining
 * Returns:
 *   the height
 **/
int height(Rb_tree tree) {
  return n_height(tree.root);
}

/* void clear
 * Does:
 * 
 * Takes:
 * 
 * Returns:
 *   void
 **/
void clear(Rb_tree *const tree) {
  /* go thru tree nodes and free all */
  if (tree != NULL) {
    clear_rec(tree->root);
    tree->size= 0;
    tree->root= NULL;
  }
}

static void clear_rec(Node *n) {
  if (n != NULL) {
    if (n->left != NULL)
      clear_rec(n->left);
    if (n->right != NULL)
      clear_rec(n->right);
    free(n);
  }
}
