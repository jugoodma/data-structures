/* AVL TREE IMPLEMENTATION
 * 
 * Justin Goodman
 **/

/** preprocessor directives **/
#include <stdlib.h>
#include "avl-tree.h"

/** static func defns **/
static int n_height(Node *const n);
static int balance(Node *const n);
static int max(int a, int b);
static Node *insert_rec(Node *n, int data, int g, int *err);
static Node *delete_rec(Node *n, int data, int g, int *err);
static int inorder_successor(Node *n);
static Node *rotateL(Node *n);
static Node *rotateR(Node *n);
static Node *rotateLR(Node *n);
static Node *rotateRL(Node *n);
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
  int result= -1;
  if (n != NULL)
    result= n->height;
  return result;
}

static int balance(Node *const n) {
  /* n should never be NULL */
  return n_height(n->left) - n_height(n->right);
}

static int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

static Node *rotateL(Node *n) {
  /* n should never be NULL */
  Node *t;
  t= n->right;
  n->right= t->left;
  t->left= n;
  n->height= n_height(n->right) + 1;
  return t;
}

static Node *rotateR(Node *n) {
  /* n should never be NULL */
  Node *t;
  t= n->left;
  n->left= t->right;
  t->right= n;
  n->height= n_height(n->left) + 1;
  return t;
}

static Node *rotateLR(Node *n) {
  /* n should never be NULL */
  n->left= rotateL(n->left);
  n= rotateR(n);
  n->height++;
  return n;
}

static Node *rotateRL(Node *n) {
  /* n should never be NULL */
  n->right= rotateR(n->right);
  n= rotateL(n);
  n->height++;
  return n;
}

static int inorder_successor(Node *n) {
  /* n, and n->right, should never be NULL */
  n= n->right;
  while (n->left != NULL)
    n= n->left;
  return n->data;
}

/* void init
 * Does:
 *   initializes a new AVL Tree
 * Takes:
 *   Avl_tree *const tree
 *     the tree we are initializing
 * Returns:
 *   void
 **/

void init(Avl_tree *const tree, int g) {
  if (tree != NULL) {
    tree->size= 0;
    tree->g= 0;
    tree->root= NULL;
  }
}

/* int search
 * Does:
 *   searches the given AVL tree for data
 * Takes:
 *   Avl_tree *const tree
 *     the tree we are searching
 *   int data
 *     the key we want to find
 * Returns:
 *   0 if NULL tree or data not in tree
 *   1 if data is contained in the tree
 **/

int search(Avl_tree *const tree, int data) {
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
 *   inserts the given integer into the AVL tree
 *   maintains O(log_2(n) + g) height via AVL rotations
 * Notes:
 *   we do not add duplicates
 * Takes:
 *   Avl_tree *const tree
 *     the tree that we are inserting data
 *   int data
 *     the data we are inserting
 * Returns:
 *   0 if any pointer was NULL, if any malloc did not work, or
 *     if data was already in the tree
 *   1 if we successfully added data to the tree
 **/

int insert(Avl_tree *const tree, int data) {
  int result= 0;
  /* NULL pointer check */
  if (tree != NULL) {
    result= 1;
    tree->root= insert_rec(tree->root, data, tree->g, &result);
    if (result)
      tree->size++;
  }
  return result;
}

/* insert recursive subroutine */
static Node *insert_rec(Node *n, int data, int g, int *err) {
  /* recursive base-case */
  if (n == NULL) {
    /* create new Node */
    Node *new= malloc(sizeof(Node));
    /* malloc check */
    if (new != NULL) {
      new->data= data;
      new->height= 0;
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
    n->left= insert_rec(n->left, data, g, err);
    if (abs(balance(n)) > g) {
      /* imbalance detected */
      if (data < n->left->data) {
	n= rotateR(n);
      } else {
	n= rotateLR(n);
      }
    }
  } else if (data > n->data) {
    /* go right */
    n->right= insert_rec(n->right, data, g, err);
    if (abs(balance(n)) > g) {
      /* imbalance detected */
      if (data > n->right->data) {
	n= rotateL(n);
      } else {
	n= rotateRL(n);
      }
    }
  } else {
    *err= 0;
    return n;
  }
  /* fix height */
  n->height= max(n_height(n->left), n_height(n->right)) + 1;
  return n;
}

/* int delete
 * Does:
 * 
 * Takes:
 * 
 * Returns:
 *   0 if fail
 *   1 if success
 **/

int delete(Avl_tree *const tree, int data) {
  int result= 0;
  if (tree != NULL && search(tree, data)) {
    tree->root= delete_rec(tree->root, data, tree->g, &result);
    tree->size--;
  }
  return result;
}

/* delete recursive subroutine */
static Node *delete_rec(Node *n, int data, int g, int *err) {
  if (n != NULL) {
    /* top-down search */
    if (data < n->data) {
      n->left= delete_rec(n->left, data, g, err);
    } else if (data > n->data) {
      n->right= delete_rec(n->right, data, g, err);
    } else {
      /* found key */
      *err= 1;
      if (n->right == NULL && n->left == NULL) {
	/* leaf level */
	free(n);
	return NULL;
      } else if (n->right == NULL) {
	/* one child */
	Node *t= n->left;
	free(n);
	return t;
      } else if (n->left == NULL) {
	/* one child */
	Node *t= n->right;
	free(n);
	return t;
      } else {
	/* both children exist */
	n->data= inorder_successor(n);
	n->right= delete_rec(n->right, n->data, g, err);
      }
    }
    /* bottom-up imbalance fix */
    if (balance(n) > g) {
      /* if bal = 0 then take cheaper option */
      if (balance(n->left) < 0) {
	n= rotateLR(n);
      } else {
	n= rotateR(n);
      }
    } else if (balance(n) < -g) {
      /* if bal = 0 then take cheaper option */
      if (balance(n->right) > 0) {
	n= rotateRL(n);
      } else {
	n= rotateL(n);
      }
    }
    /* fix height */
    n->height= max(n_height(n->left), n_height(n->right)) + 1;
  }
  return n;
}

/* int size
 * Does:
 *   gives the number of nodes in the tree
 * Takes:
 *   Avl_tree tree
 *     the tree we are examining
 * Returns:
 *   the number of elements in the tree
 **/
int size(Avl_tree tree) {
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
 *   Avl_tree tree
 *     the tree we are examining
 * Returns:
 *   the height
 **/
int height(Avl_tree tree) {
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
void clear(Avl_tree *const tree) {
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
