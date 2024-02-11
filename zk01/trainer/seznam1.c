#ifndef __TRAINER__
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node * next;
} Node;
#endif

// === Test 1 ===

Node * listCreate () {
    return NULL;
}

// 1
// 2 - 1
Node * listPushFront ( Node * list, int val ) { 
    Node * n = (Node*)malloc(sizeof(Node));
    n->val = val;
    n->next = list;
    return n;
}

int listEmpty ( Node * list ) {
    return list == NULL;
}

int listCount ( Node * list ) {
    int num = 0;
    Node * copy = list;
    while(copy != NULL){
        num++;
        copy = copy->next;
    }
    return num;
}

void listDelete ( Node * list ) {
    while(list != NULL){
        Node * tmp = list;
        list = list->next;
        free(tmp);
    }
}

// === Test 2 ===

int listSum ( Node * list ) {
    if(list == NULL) return 0;
    int sum = 0;
    Node * copy = list;
    while(copy != NULL){
        sum += copy->val;
        copy = copy->next;
    }
    return sum;
}

void listPrint ( Node * list ) {
    if(list == NULL) return;
    Node * copy = list;
    if(copy == NULL){
        return;
    }
    while(copy->next != NULL){
        printf("%i -> ", copy->val);
        copy = copy->next;
    }
    printf("%i", copy->val);
    printf("\n");
}

// === Test 3 ===

Node * listPushBack ( Node * list, int val ) {
    if(list == NULL){
        Node * n = (Node*) malloc(sizeof(Node));
        n->val=val;
        n->next = NULL;
        return n;
    }
    Node * copy = list;
    while( copy->next != NULL){
        copy = copy->next;
    }
    Node * n = (Node*) malloc(sizeof(Node));
    n->val=val;
    n->next = NULL;
    copy->next = n;
    return list;
}

Node * listPopFront ( Node * list ) {
    Node * tmp = list->next;
    free(list);
    return tmp;
}

Node * listPopBack ( Node * list ) {
    Node * tmp = list;
    Node * copy = NULL;
    while(tmp->next->next != NULL){
        tmp = tmp->next; 
    }
    copy = tmp->next; // 1
    tmp->next = NULL;
    free(copy);
    return list;
}

// === Test 4 ===
// 1(on 2) - 2(on 3) - 3(on 4) - 4(on 5) - 5(on 6) - 6(on null)
// pushBack 1
// if(2) ignore
//pushBack 3
Node * listRemove ( Node * list, int val ) {
    Node *tmp = list;
    Node *newNode = NULL;
    while(tmp != NULL){
        if(tmp->val != val){
            newNode = listPushBack(newNode, tmp->val);
        }
        tmp = tmp->next;
    }
    listDelete(list);
    return newNode;
}


// 1(on 2) - 2(on 3) - 3(on 4) - 4(on 5) - 5(on 6) - 6(on null)
// pushFront 1: 1
// pushFront 2: 2 - 1
//
Node * listReverse ( Node * head ) {
    Node * tmp = head;
    Node * newNode = NULL;
    while(tmp != NULL){
        newNode = listPushFront(newNode, tmp->val);
        tmp = tmp->next;
    }
    listDelete(head);
    return newNode;
}

// Spojove seznamy II
//HEAD:  n - n+1 - n+2 - n+3 - n+4 - NULL
//HEAD: n - n+2 - n+4 - NULL
//NEW: n+1 - n+3
Node * listSpliOld ( Node * head ) {
    Node *tmp = head, *newNode = NULL;
    while(tmp != NULL){
        Node *next = tmp->next, *nextNext = tmp->next->next;
        newNode = listPushBack(next, next->val);
        tmp = listRemove(tmp, next->val);
        tmp = nextNext;
    }
    return newNode;
}

Node * listSplit ( Node * head ) {
    int flag = 0;
    Node *copy = head;
    Node *tmp = NULL;
    while(copy != NULL){
        if(flag){
            tmp = listPushBack(tmp, tmp->val);
        }
        tmp = tmp->next;
        flag = flag == 1 ? 0 : 1;
    }
    return tmp;
}

// n+2 - n - n+4 - n+3
// n-1 - n+1

Node * listMerge ( Node * head1, Node * head2 ) {
    Node * newNode = NULL;
    Node *tmp1 = head1, *tmp2 = head2;
    for(; tmp1; tmp1=tmp1->next){}
    while(tmp2 != NULL){
        Node * n = (Node*)malloc(sizeof(Node));
        n->val = tmp2->val;
        n->next = NULL;
        tmp1->next = n;
        tmp2=tmp2->next;
    }
    return head1;
}

Node * listMergeSort ( Node * head ) {
    return head;
}

#ifndef __TRAINER__
int main () {

    return 0;
}
#endif