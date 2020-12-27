
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
}  ListObj;

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return N;
}
// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

List newList(void) {
    List L = NULL;
    L = malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->index = -1;
    L->length = 0;
    return (L);
}

void freeList(List* pL) {
    if( pL!=NULL && *pL!=NULL) {
        while(length(*pL) > 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;

    }
} 

int length(List L) { // Returns the number of elements in L.
    if(L == NULL) {
        printf("List Error: calling length() on NULL list reference\n");
        exit(1);
    }
    else {
        return L->length;
    }
}

int isEmpty(List L){
    if( L == NULL){
        printf("List error: isEmpty() called on NULL list reference\n");
        exit(1);
    }
    else{
        return(L->length==0);
    }
}


int index(List L) { // Returns index of cursor element if defined, -1 otherwise.
    if(L == NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }
    else if(L->cursor == NULL){
        return -1;
    }
    else{
        return L->index;    
    }
}

int front(List L) { // Returns front element of L. Pre: length()>0
    if(L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    else if(length(L) <= 0) {
        printf("List Error: calling front() on empty list\n");
        exit(1);
    }
    else {
        return L->front->data;
    }
}

int back(List L) { // Returns back element of L. Pre: length()>0
    if(L == NULL) {
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    else if(length(L) <= 0) {
        printf("List Error: calling back() on empty list\n");
        exit(1);
    }
    else{
        return L->back->data;
    }
}

int get(List L) { // Returns cursor element of L. Pre: length()>0, index()>=0
    if(L == NULL) {
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    else if(length(L) <= 0) {
        printf("List Error: calling get() on empty list\n");
        exit(1);
    }
    else if (L->cursor == NULL){
        printf("List Error: calling get() on NULL cursor\n");
        exit(1);
    }
    else {
        return L->cursor->data;
    }

}//equals method is utilized from stack.c example
int equals(List A, List B) { // Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise.
    if(A == NULL || B == NULL) {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
    }
    else{
        int eq = ( A->length == B->length );
        Node N = A->front;
        Node M = B->front;
        while( eq && N!=NULL){
            eq = (N->data==M->data);
            N = N->next;
            M = M->next;
        }
        return eq;
    }
}

// Manipulation procedures ------------------------------------------------
void clear(List L) { // Resets L to its original empty state.
    if(L == NULL) {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    else {
        while(L->length > 0) {
            deleteFront(L);
        }
        L->front = L->cursor = L->back = NULL;
        L->index = -1;
        L->length = 0;
    }
}

void moveFront(List L) { // If L is non-empty, sets cursor under the front element, otherwise does nothing.
    if(L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    else{
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L) {  // If L is non-empty, sets cursor under the back element, otherwise does nothing.
    if(L == NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    else{
        if(L->length > 0) {
            L->cursor = L->back;
            L->index = (L->length -1);
        }
    }
}

 // If cursor is defined and not at front, move cursor onestep toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L) {
    if(L == NULL) {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    else if((L->cursor != NULL) &&(L->cursor != L->front)) {
        L->cursor = L->cursor->prev;
        L->index--;
    }
    else if(L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
    }
}

// If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L){
    if(L == NULL) {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    else if((L->cursor != NULL) && (L->cursor != L->back)) {
        L->cursor = L->cursor->next;
        L->index++;
    }
    else if(L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int data) {
    if(L == NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    else if (L->front == NULL || L->length <= 0) {
        Node N = newNode(data);
        L->front = L->back = N;
        L->cursor = L->front;
        L->length++; 
    }
    else{ 
        Node N = newNode(data);
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
        L->index++;
        L->length++;
    }
}

// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int data) {
    if(L == NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    else if(L->back == NULL || L->length <= 0) { //if list is greater than one
        Node N = newNode(data);
        L->front = L->back = N;
        L->cursor = L->back;
        L->length++;
    }
    else{ 
        Node N =newNode(data);
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
        N->next = NULL;
        L->length++;
    }
}

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling apend() on a NULL List reference\n");
        exit(1);
    }
    else if (L->cursor == NULL) {
        printf("List Error: cannot insertBefore()  if cursor is undefined\n");
    }
    else{
        Node N = newNode(data);
        N->next = L->cursor;
        if(L->cursor->prev != NULL) {
            N->prev = L->cursor->prev;
            L->cursor->prev->next = N;
        }
        L->cursor->prev = N;
        if(N->prev == NULL) {
            L->front = N;
        }
        L->index++;
        L->length++;
    }
    
}

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling apend() on a NULL List reference\n");
        exit(1);
    }
    else if (L->cursor == NULL) {
        printf("List Error: cannot insertAfter()  if cursor is undefined\n");
    } else if (L->cursor == L->back) {
        append(L, data);
    } else {
        Node N = newNode(data);
        N->prev = L->cursor;
        N->next = L->cursor->next;
        L->cursor->next->prev = N;
        L->cursor->next = N;
        L->length++;
    }
}

void deleteFront(List L) { // Delete the front element. Pre: length()>0
    if(L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if(L->length < 1){
        printf("List Error: Calling deleteFront() on empty List");
        exit(1);
    }

    if(L->length == 1) {
        Node N = L->front;
        freeNode(&N);
        L->cursor = L->front = L->back = NULL;
        L->index = -1;
        L->length--;
    }
    else {
        Node N = L->front;
        L->front = N->next;
        N->next = NULL;
        L->front->prev = NULL;
        if(L->cursor != NULL){
            L->index--;
        }
        freeNode(&N);
        L->length--;
    }
}

void deleteBack(List L){ // Delete the back element. Pre: length()>0
    if(L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if(L->length < 1){
        printf("List Error: Calling deleteBack() on empty List");
        exit(1);
    }
    else if(L->length == 1){
        Node N = L->back;
        freeNode(&N);
        L->cursor = L->front = L->back = NULL;
        L->index = -1;
        L->length--;
    }
    else{
        Node N = L->back;
        L->back = N->prev;
        L->back->next = NULL;
        N->prev = NULL;
        if(L->index == L->length -1){
            L->index = -1;
        }
        freeNode(&N);
        L->length--;
    }

}

void delete(List L){ // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
    if(L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    else if(L->length < 1){
        printf("List Error: Calling deleteBack() on empty List");
        exit(1);
    }
    else if(L->cursor == L->back){
        deleteBack(L);
    }
    else if(L->cursor == L->front){
        deleteFront(L);
    }
    else{
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&L->cursor);
        L->length--;
    }

}

// printList()
// prints contents to a file
void printList(FILE* out, List L) {
    if(L == NULL) {
        printf("List error: printList() called on NULL List reference\n");
        exit(1);
    }
    else {
        Node N = L->front;
        while(N != NULL){
            fprintf(out, "%d", N->data);
            fprintf(out, " ");
            N = N->next;
        }
    }
}

// copyList()
// makes a copty of the List
List copyList(List L) {
    List list = newList();
    Node N = L->front;
    while(N != NULL){
        append(list, N->data);
        N = N->next;
    }
    return list;
}
