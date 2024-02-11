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
Node * listSplit ( Node * head ) {
    Node *newNode = NULL;
    if(head == NULL) return NULL;
    int i = 1;
    Node *tmp = head;
    while(tmp != NULL){
        if(i % 2 == 0){
            newNode = listPushBack(newNode, tmp->val);
        }
        i++;
        tmp = tmp->next;
    }
    Node *tmp2 = head;
    while(tmp2!=NULL){
        if(tmp2->next == NULL){
            break;
        }
        Node * del = tmp2->next;
        tmp2->next = tmp2->next->next;
        tmp2 = tmp2->next;
        free(del);
    }
    return newNode;
}

// n - n+2
// n+1 - n+3

Node * listMerge ( Node * head1, Node * head2 ) {
    Node * sortedNode = NULL, * tmp = NULL;
    if(head1 == NULL && head2 == NULL){
        return NULL;
    } else if(head1 == NULL && head2 != NULL){
        return head2;
    } else if(head1 != NULL && head2 == NULL){
        return head1;
    }

    if(head1->val <= head2->val){
        sortedNode = head1;
        head1 = head1->next;
    } else if(head1->val > head2->val){
        sortedNode = head2;
        head2 = head2->next;
    }

    tmp = sortedNode;
    tmp->next = NULL;

    while(1){
        if(head1 == NULL){
            tmp->next = head2;
            break;
        } else if(head2 == NULL){
            tmp->next = head1;
            break;
        } else {
            if(head1->val <= head2->val){
                tmp->next = head1;
                head1 = head1->next;
                tmp = tmp->next;
            } else if(head1->val > head2->val){
                tmp->next = head2;
                head2 = head2->next;
                tmp = tmp->next;
            }
        }
    }

    return sortedNode;
}

Node * listMergeSort ( Node * head ) {
    if(head == NULL) return NULL;
    int length = listCount(head);
    if(length == 1){
        return head;
    }
    int pivot = length/2;                       // 2 4 5     3 4 5
    Node *head1 = head, *head2 = head;
    for(int i = 0; i < pivot-1; i++){
        head2 = head2->next;                    //    3 4 5 (3 is first)
    }
    Node *tmp = head2->next;        // 3
    head2->next = NULL;             // 2 4 5 -> NULL
    head2 = tmp;                    // 3 4 5 -> NULL

    head1 = listMergeSort(head1);
    head2 = listMergeSort(head2);
    head = listMerge(head1, head2);

    return head;
}

#ifndef __TRAINER__
int main () {
 /*   
    // Test 1
    Node * head = listCreate();
    assert ( listEmpty (head) );
    assert ( listCount (head) == 0 );
    for ( int i = 1; i <= 10; ++i )
        head = listPushFront ( head, i );
    assert ( !listEmpty (head) );
    assert ( listCount (head) == 10 );
    listDelete ( head );

    // Test 2
    head = listCreate();
    assert ( listSum (head) == 0 );
    for ( int i = 1; i <= 10; ++i )
        head = listPushFront ( head, i );
    assert ( !listEmpty (head) );
    listPrint (head); // 10 -> 9 -> 8 -> 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1
    assert ( listSum (head) == 55 );
    listDelete ( head );

     // Test 3
    head = listCreate();
    for ( int i = 1; i <= 10; ++i )
        head = listPushBack ( head, i );
    listPrint (head); // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
    assert ( listCount (head) == 10 );
    assert ( listSum (head) == 55 );

    for ( int i = 1; i <= 5; ++i )
        head = listPopFront ( head );
    listPrint (head); // 6 -> 7 -> 8 -> 9 -> 10
    assert ( listCount (head) == 5 );
    assert ( listSum (head) == 40 );

    for ( int i = 10; i >= 8; --i )
        head = listPopBack ( head );
    listPrint (head); // 6 -> 7
    assert ( listCount (head) == 2 );
    assert ( listSum (head) == 13 );

    for ( int i = 4; i <= 7; ++i )
        head = listPushBack ( head, i );
    listPrint (head); // 6 -> 7 -> 4 -> 5 -> 6 -> 7
    assert ( listCount (head) == 6 );
    assert ( listSum (head) == 35 );

     // Test 4
    head = listReverse ( head );
    listPrint (head); // 7 -> 6 -> 5 -> 4 -> 7 -> 6
    assert ( listCount (head) == 6 );
    assert ( listSum (head) == 35 );

    head = listRemove ( head, 4 );
    listPrint (head); // 7 -> 6 -> 5 -> 7 -> 6
    assert ( listCount (head) == 5 );
    assert ( listSum (head) == 31 );

    head = listRemove ( head, 7 );
    listPrint (head); // 6 -> 5 -> 6
    assert ( listCount (head) == 3 );
    assert ( listSum (head) == 17 );

    head = listRemove ( head, 6 );
    listPrint (head); // 5
    assert ( listCount (head) == 1 );
    assert ( listSum (head) == 5 );

    head = listRemove ( head, 9 );
    assert ( listCount (head) == 1 );
    assert ( listSum (head) == 5 );

    head = listRemove ( head, 5 );
    listPrint (head); // nic
    assert ( listCount (head) == 0 );
    assert ( listEmpty (head) );

    listDelete ( head ); 

    // Spojak II
    Node * list = listCreate();
    for ( int i = 1; i < 10; ++i )
        list = listPushFront ( list, i ); // 9 8 7 6 5 4 3 2 1

    // Test 1
    listPrint(list);
    Node * half = listSplit (list);
    listPrint (list); // 9 7 5 3 1
    listPrint (half); // 8 6 4 2
    listDelete (list);
    listDelete (half);

     // Test 2
    list = listCreate();
    half = listCreate();
    
    for ( int i = 0; i <= 5; ++i ) {
        list = listPushBack ( list, i * 2 ); // 2 4 6 8 10
        half = listPushBack ( half, i * 2 + 1 ); // 1 3 5 7 9
    }
    listPrint (list);
    listPrint (half);
    
    Node * merged = listMerge (half, list);
    listPrint (merged); // 1 2 3 4 5 6 7 8 9 10
    listDelete (merged);
*/

    // Test 3
    Node * list = listCreate();
    for ( int i = 1; i < 10; ++i )
        list = listPushFront ( list, i );
    // list is now 9 8 7 6 5 4 3 2 1
    listPrint(list);

    Node * sorted = listMergeSort (list);
    listPrint (sorted); // 1 2 3 4 5 6 7 8 9
    listDelete (sorted); 
    return 0;
}
#endif