/*
* Name: AJ Wong
* CruzID: 1652596
* Class: CMPS 101
* Date: 29 May 2019
* Desc: Header file for List ADT
* File Name: List.h
*/

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// List
// Exported reference type
typedef struct ListObj* List;

// newList()
// constructor for the List type
List newList(void);

// freeList()
// destructor for the List type
void freeList(List* pL);

// Returns the number of elements in this List.
int length(List L);

// If cursor is defined, returns the index of the cursor element, otherwise returns -1.
int index(List L);

// Returns front element.
// Pre: length() > 0
int front(List L);

// Returns back element.
// Pre: length() > 0
int back(List L);

// Returns cursor element.
// Pre: length() > 0, index() >= 0
int get(List L);

// Returns true if and only if List A and List B are the same integer sequence.
// The states of the cursors in the two Lists are not used in determining equality.
int equals(List A, List B);

// Resets this List to its original empty state.
void clear(List L);

// If List is non-empty, places the cursor under the front element, otherwise does nothing.
void moveFront(List L);

// If List is non-empty, places the cursor under the back element, otherwise does nothing.
void moveBack(List L);

// If cursor is defined and not at front, moves cursor one step toward front of this List.
// If cursor is defined and at front, cursor becomes undefined.
// If cursor is undefined, does nothing.
void movePrev(List L);

// If cursor is defined and not at back, moves cursor one step toward back of this List.
// If cursor is defined and at back, cursor becomes undefined.
// If cursor is undefined, does nothing.
void moveNext(List L);

// Insert new element into this List.
// If List is non-empty, inserstion takes place before front element.
void prepend(List L, int data);

// Insert new element into this List.
// If List is non-empty, inserstion takes place after back element.
void append(List L, int data);

// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int data);

// Insert new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, int data);

// Deletes the front element.
// Pre: length() > 0
void deleteFront(List L);

// Deletes the back element.
// Pre: length() > 0
void deleteBack(List L);

// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L);

// Overrides Object's toString method.
// Returns a String representation of this List consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L);

// Returns a new List representing the same integer sequence as this List.
// The cursor in the new List is undefined, regardless of the state of the cursor in this List.
// This List is unchanged.
List copyList(List L);

// Returns a new List which is the concatenation of List A followed by List B.
// The cursor in the new List is undefined, regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B);

#endif
