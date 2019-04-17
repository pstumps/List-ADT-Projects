//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101
//PA 4
//List ADT


// Libraries
#include <stdlib.h>
#include <stdio.h>

#include "List.h"


// List and Node structs

typedef struct NodeObj {
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
    Node head;
    Node tail;
    Node curr;
    int length;
    int index;
} ListObj;

//Node constructor and FreeNode
Node newNode(int data){
    Node n = malloc(sizeof(NodeObj));
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return(n);
}

void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

//List constructor and FreeList

List newList(void){
    List L = malloc(sizeof(ListObj));
    L->head = NULL;
    L->tail = NULL;
    L->curr = NULL;
    L->index = -1;
    L->length = 0;
    return (L);
}

void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        
        while(length(*pL) != 0){
            deleteFront(*pL);
        }

        free(*pL);
        *pL = NULL;

    }
    /*while(length(*pL) != 0){
        deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
    if(*pL != NULL && pL != NULL){
        Node t = (*pL)->head;
        while(t != NULL){
            Node n = t;
            t = t->next;
            free(n);
        }
        free(*pL);
        *pL = NULL;
    }*/
}


//Access functions

int length(List L){
    if( L == NULL ){
        printf("Cannot call length on empty or null List.");
        exit(1);
    }
    return(L->length);
}

int index(List L){
    if(L == NULL){
        printf("Cannot call index on NULL list.");
        exit(1);
    }
    Node t = L->head;
    int index = 0;
    while(t != NULL){
        if(t == L->curr){
            return(index);
        }
        index++;
        t = t->next;
    }
    return -1;
}

int front(List L){
    if(L == NULL || L->length == 0){
        printf("List does not exist.");
        exit(1);
    }
    return(L->head->data);
}

int back(List L){
    if(L == NULL || L->length == 0){
        printf("List does not exist.");
        exit(1);
    }
    return(L->tail->data);
}

int get(List L){
    if(L == NULL){
        printf("Cannot call get on NULL list.");
        exit(1);
    }
    if(length(L) == 0){
        printf("Cannot call get on empty list.");
        exit(1);
    }
    if(L->curr == NULL){
        printf("Cannot call get on NULL cursor.");
        exit(1);
    }
    return(L->curr->data);
}

int equals(List A, List B){
    Node cmp = A->head;
    Node th =  B->head;

    int e = (A->length == B->length);

    if(A == NULL || B == NULL){
        printf("Cannot call equals on NULL reference.\n");
        exit(1);
    }

    while( cmp != NULL && e){
        e = (cmp->data == th->data);
        cmp = cmp->next;
        th = th->next;
    }

    return e;

}
//Manipulation procedures

void clear(List L){
    if(L == NULL){
        printf("Cannot clear NULL or empty list.");
        exit(1);
    }
    //if(length(L) == 0){
    //    printf("Cannot clear empty list. (length = 0)");
    //    exit(1);
    //}
    while(L->head != NULL){
        deleteFront(L);
    }
}

void moveFront(List L){
    if(L == NULL){
        printf("Cannot moveFront NULL list.");
        exit(1);
    }
    if(length(L) > 0){
        L->curr = L->head;
    }
}

void moveBack(List L){
    if(L == NULL){
        printf("Cannot moveBack NULL list.");
        exit(1);
    }
    if(length(L) > 0){
        L->curr = L->tail;
    }
}

void movePrev(List L){
    if(L == NULL){
        printf("Cannot call movePrev on NULL list");
        exit(1);
    }
    if(L->curr != NULL && index(L) <= length(L)-1){
        L->curr = L->curr->prev;
        L->index--;
    }
    else if (L->curr != NULL && index(L) == 0){
        L->curr = NULL;
        L->index = -1;
    }
    /*if(index(L) == -1){
        return;
    }
    if(length(L) == 0){
        L->curr = NULL;
    }
    if(index(L) >= 0 && index(L) >= length(L) -1){
        L->curr = L->curr->prev;
    }*/

}

void moveNext(List L){
    if(L == NULL){
        printf("Cannot call moveNext on NULL list");
        exit(1);
    }
    if(L->curr != NULL && index(L) != length(L)-1){
        L->curr = L->curr->next;
        L->index++;
    }
	else if (L->curr != NULL && index(L) == length(L)-1){
    	L->curr = NULL;
        L->index = -1;
	}
}

void prepend(List L, int data){
    if(L == NULL){
        printf("Cannot prepend NULL list");
        exit(1);
    }
    Node N = newNode(data);
    if (L->length == 0){
        L->tail = N;
        L->head = N;
        L->length++;
    }
    else{
        //N->next = L->head;
        L->head->prev = N;
        N->next = L->head;
        L->head = N;
        L->index++;
        L->length++;
    }
}

void append(List L, int data){
    if(L == NULL){
        printf("Cannot append NULL list");
        exit(1);
    }
    Node N = newNode(data);
    if(L->length == 0){
        L->tail = N;
        L->head = N;
        L->length++;
    }
    else{
        //N->prev = L->tail;
        L->tail->next = N;
        N->prev = L->tail;
        L->tail = N;
        L->length++;
    }
}

void insertBefore(List L, int data){
    // BUG: Calling when L->curr == NULL.
    if(L->curr == NULL){
        printf("Cannot call insertBefore on NULL cursor.");
        exit(1);
    }
    Node N = newNode(data);
    if(L->curr == L->head){
        L->head->prev = N;
        N->next = L->head;
        L->head = N;
    }
    else{
        N->prev = L->curr->prev;
        L->curr->prev->next = N;
        N->next = L->curr;
        L->curr->prev = N;
    }
    L->length++;
    /*if(index(L) == 0){
        prepend(L, data);
        return;
    }
    N->prev = L->curr->prev;
    N->next = L->curr;
    L->curr->prev->next = N;
    L->curr->prev = N;
    L->length++;*/
}

void insertAfter(List L, int data){
    // BUG: Calling when L->curr == NULL.
    if(L->curr == NULL){
        printf("Cannot call insertAfter on NULL cursor.");
        exit(1);
    }
    Node N = newNode(data);
    if(L->curr == L->tail){
        L->tail->next = N;
        N->prev = L->tail;
        L->tail = N;
    }
    else{
        N->prev = L->curr;
        N->next = L->curr->next;
        L->curr->next->prev = N;
        L->curr->next = N;
    }
    L->length++;
    /*if(index(L) == length(L)){
        append(L, data);
        return;
    }
    N->prev = L->curr;
    N->next = L->curr->next;
    L->curr->next->prev = N;
    L->curr->next = N;
    L->length++;*/
}

void deleteFront(List L){
    if(L == NULL){
        printf("Cannot call deleteFront on NULL list.");
        exit(1);
    }
    if(L->length <= 0){
        printf("Cannot call deleteFront on empty list.");
        exit(1);
    }

    Node N = L->head;

    if(L->length > 1){
        L->head = L->head->next;
        freeNode(&N);
        L->index--;

    }
    else{
        L->head = NULL;
        freeNode(&N);
        L->index--;
        
    }
    L->length--;
    
}

void deleteBack(List L){
    if(L == NULL){
        printf("Cannot call deleteBack on NULL list.");
        exit(1);
    }
    if(length(L) <= 0){
        printf("Cannot call deleteBack on empty list.");
        exit(1);
    }

    Node N = L->tail;

    if(L->curr == L->tail){
        L->curr = L->curr->prev;
        freeNode(&N);
        L->index--;
    }
    if (L->length > 1) {
        L->tail = L->tail->prev;
        L->tail->next = NULL;
        freeNode(&N);
        L->length--;
    } 
    if(L->length == 1) {
        L->head = NULL;
        L->tail = NULL;
        L->curr = NULL;
        freeNode(&N);
        L->length--;
        L->index = -1;
    }

}

void delete(List L){
    if(L == NULL){
        printf("Cannot call delete on NULL list.");
        exit(1);
    }
    if(length(L) == 0){
        printf("Cannot call delete on empty list.");
        exit(1);
    }
    Node N = L->curr;

    if(N == L->tail){
        deleteBack(L);
    }
    else if(N == L->head){
        deleteFront(L);
    }
    else{
        L->curr->prev->next = L->curr->next;
        L->curr->next->prev = L->curr->prev;
        //L->curr->next = NULL;
        //L->curr->prev = NULL;
        freeNode(&N);
        L->curr = NULL;    
        L->length--;
        L->index = -1;
    }
}

//Other Functions

void printList(FILE* out, List L){
   if(L == NULL){
       printf("Cannot call printList on NULL list");
       exit(1);
   }
   for(Node N = L->head; N != NULL; N = N->next){
       fprintf(out, "%d ", N->data);
   }
}

List copyList(List L){
    List l = newList();
    for (Node N = L->head; N != NULL; N = N->next){
        append(l, N->data);
    }
    return (l);
}