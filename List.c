/*
* Name: AJ Wong
* CruzID: 1652596
* Class: CMPS 101
* Date: 29 May 2019
* Desc: Implementation file for List ADT
* File Name: List.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"

// NodeObj
typedef struct NodeObj {
   int data;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor of the Node type
Node newNode(int d) {
   Node N = malloc(sizeof(NodeObj));
   assert(N != NULL);
   N->data = d;
   N->prev = NULL;
   N->next = NULL;
   return N;
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if (pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

// ListObj
typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int cursorIndex;
  int length;
} ListObj;

// newList()
// constructor for the List type
List newList(void) {
  List L = malloc(sizeof(ListObj));
  assert(L != NULL);
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->cursorIndex = -1;
  L->length = 0;
  return L;
}

// freeList()
// destructor for the List type
void freeList(List* pL) {
  clear(*pL);
  if (pL != NULL && *pL != NULL) {
     free(*pL);
     *pL = NULL;
  }
}

int find(List L, int index) {
  Node N = L->front;
  for (int i = 0; i < index; i++) {
    N = N->next;
  }
  return N->data;
}

// Returns the number of elements in this List.
int length(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: length() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->length;
}

// If cursor is defined, returns the index of the cursor element, otherwise returns -1.
int index(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: index() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->cursorIndex;
}

// Returns front element.
// Pre: length() > 0
int front(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: front() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(!(L->length > 0)) {
    fprintf(stderr, "List Error: front() called on empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->front->data;
}

// Returns back element.
// Pre: length() > 0
int back(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: back() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(!(L->length > 0)) {
    fprintf(stderr, "List Error: back() called on empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->back->data;
}

// Returns cursor element.
// Pre: length() > 0, index() >= 0
int get(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: get() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(!(L->length > 0)) {
    fprintf(stderr, "List Error: get() called on empty List\n");
    exit(EXIT_FAILURE);
  }
  if(!(L->cursorIndex >= 0)) {
    fprintf(stderr, "List Error: get() called on List with undefined cursor\n");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

// Returns true if and only if List A and List B are the same integer sequence.
// The states of the cursors in the two Lists are not used in determining equality.
// Returns 0 if false and 1 if true.
int equals(List A, List B) {
  if(A == NULL) {
    fprintf(stderr, "List Error: equals() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(B == NULL) {
    fprintf(stderr, "List Error: equals() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  int eq = 1;
  Node n1 = A->front;
  Node n2 = B->front;
  if (A->length != B->length) {
    eq = 0;
  }
  while (eq && (n1 != NULL && n2 != NULL)) {
    if (n1->data != n2->data) {
      eq = 0;
    }
    n1 = n1->next;
    n2 = n2->next;
  }
  return eq;
}

// Resets this List to its original empty state.
void clear(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: clear() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  while (L->length > 0) {
    deleteBack(L);
  }
}

// If List is non-empty, places the cursor under the front element, otherwise does nothing.
void moveFront(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: moveFront() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length > 0) {
    L->cursor = L->front;
    L->cursorIndex = 0;
  }
}

// If List is non-empty, places the cursor under the back element, otherwise does nothing.
void moveBack(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: moveBack() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length > 0) {
    L->cursor = L->back;
    L->cursorIndex = L->length - 1;
  }
}

// If cursor is defined and not at front, moves cursor one step toward front of this List.
// If cursor is defined and at front, cursor becomes undefined.
// If cursor is undefined, does nothing.
void movePrev(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: movePrev() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursorIndex != -1) { // If cursor is defined
    L->cursorIndex--;
    L->cursor = L->cursor->prev;
  }
}

// If cursor is defined and not at back, moves cursor one step toward back of this List.
// If cursor is defined and at back, cursor becomes undefined.
// If cursor is undefined, does nothing.
void moveNext(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: moveNext() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursorIndex != -1) {
      if (L->cursorIndex == L->length - 1) {  // If cursor is at the back of List
        L->cursorIndex = -1;
        L->cursor = NULL;
      }
      else {
        L->cursorIndex++;
        L->cursor = L->cursor->next;
      }
    }
}

// Insert new element into this List.
// If List is non-empty, inserstion takes place before front element.
void prepend(List L, int data) {
  if(L == NULL) {
    fprintf(stderr, "List Error: prepend() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length > 0) {
    Node N = newNode(data);
    N->next = L->front;
    L->front->prev = N;
    L->front = N;
  }
  else {
    L->front = newNode(data);
    L->back = L->front;
  }
  L->length++;
  L->cursorIndex++;
}

// Insert new element into this List.
// If List is non-empty, inserstion takes place after back element.
void append(List L, int data) {
  if(L == NULL) {
    fprintf(stderr, "List Error: append() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length > 0) {
    Node N = newNode(data);
    N->prev = L->back;
    L->back->next = N;
    L->back = N;
  }
  else {
    L->back = newNode(data);
    L->front = L->back;
  }
  L->length++;
}

// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int data) {
  if(L == NULL) {
    fprintf(stderr, "List Error: insertBefore() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (!(L->length > 0)) {
    fprintf(stderr, "List Error: insertBefore() called on empty List");
    exit(EXIT_FAILURE);
  }
  if (!(L->cursorIndex >= 0)) {
    fprintf(stderr, "List Error: insertBefore() called on List with undefined cursor");
    exit(EXIT_FAILURE);
  }
  if (L->cursorIndex == 0) { // If cursor is at the front of List
    prepend(L, data);
  }
  else {
    Node N = newNode(data);
    N->prev = L->cursor->prev;
    N->next = L->cursor;
    L->cursor->prev->next = N;
    L->cursor->prev = N;
    L->length++;
    L->cursorIndex++;
  }
}

// Insert new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, int data) {
  if(L == NULL) {
    fprintf(stderr, "List Error: insertAfter() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (!(L->length > 0)) {
    fprintf(stderr, "List Error: insertAfter() called on empty List");
    exit(EXIT_FAILURE);
  }
  if (!(L->cursorIndex >= 0)) {
    fprintf(stderr, "List Error: insertAfter() called on List with undefined cursor");
    exit(EXIT_FAILURE);
  }
  if (L->cursorIndex == L->length - 1) { // If cursor is at the back of List
    append(L, data);
  }
  else {
    Node N = newNode(data);
    N->prev = L->cursor;
    N->next = L->cursor->next;
    L->cursor->next->prev = N;
    L->cursor->next= N;
    L->length++;
  }
}

// Deletes the front element.
// Pre: length() > 0
void deleteFront(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: deleteFront() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (!(L->length > 0)) {
    fprintf(stderr, "List Error: deleteFront() called on empty List");
  }
  if (L->length == 1) {
    Node N = L->front;
    L->front = NULL;
    L->back = NULL;
    L->cursorIndex = -1;
    L->cursor = NULL;
    freeNode(&N);
    N = NULL;
    L->length--;
  }
  else {
    Node N = L->front;
    L->front = L->front->next;
    L->front->prev = NULL;
    freeNode(&N);
    N = NULL;
    L->length--;
    L->cursorIndex--;
  }
}

// Deletes the back element.
// Pre: length() > 0
void deleteBack(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: deleteBack() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (!(L->length > 0)) {
    fprintf(stderr, "List Error: deleteBack() called on empty List");
    exit(EXIT_FAILURE);
  }
  if (L->length == 1) {
    Node N = L->front;
    L->front = NULL;
    L->back = NULL;
    L->cursorIndex = -1;
    L->cursor = NULL;
    freeNode(&N);
    N = NULL;
    L->length--;
  }
  else {
    Node N = L->back;
    L->back = L->back->prev;
    L->back->next = NULL;
    freeNode(&N);
    N = NULL;
    L->length--;
    if (L->length == L->cursorIndex) {
      L->cursor = NULL;
      L->cursorIndex = -1;
    }
  }
}

// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: delete() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (!(L->length > 0)) {
    fprintf(stderr, "List Error: delete() called on empty List");
    exit(EXIT_FAILURE);
  }
  if (!(L->cursorIndex >= 0)) {
    fprintf(stderr, "List Error: delete() called on List with undefined cursor");
    exit(EXIT_FAILURE);
  }
  if (L->cursorIndex == L->length - 1) {
    deleteBack(L);
  }
  else if (L->cursorIndex == 0) {
    deleteFront(L);
  }
  else {
    Node N = L->cursor;
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    L->length--;
    L->cursorIndex = -1;
    L->cursor = NULL;
    freeNode(&N);
    N = NULL;
  }
}

// Overrides Object's toString method.
// Returns a String representation of this List consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: printList() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (!(L->length == 0)) {
    for (Node N = L->front ; N != NULL; N = N->next) {
      fprintf(out, "%d ", N->data);
    }
  }
}

// Returns a new List representing the same integer sequence as this List.
// The cursor in the new List is undefined, regardless of the state of the cursor in this List.
// This List is unchanged.
List copyList(List L) {
  if(L == NULL) {
    fprintf(stderr, "List Error: copyList() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  List A = newList();
  int i;
  for (i = 0; i < L->length; i++) {
    append(A, find(L, i));
  }
  return A;
}

// Returns a new List which is the concatenation of List A followed by List B.
// The cursor in the new List is undefined, regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
  if(A == NULL) {
    fprintf(stderr, "List Error: concatList() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(B == NULL) {
    fprintf(stderr, "List Error: concatList() called on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  List C = newList();
  int i;
  for (i = 0; i < A->length; i++) {
    append(C, find(A, i));
  }
  for (i = 0; i < B->length; i++) {
    append(C, find(B, i));
  }
  return C;
}
