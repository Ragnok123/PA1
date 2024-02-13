#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem
{
    struct TItem * m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;
 
TITEM * createItem ( int mul, int pow, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Mul = mul;
    n -> m_Pow = pow;
    n -> m_Next = next;
    return n;
}
 
void deleteList (TITEM * l)
{
    while (l)
    {
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

void printTree(TITEM *a){
    while(a->m_Next!=NULL){
        printf("%ix^%i + ", a->m_Mul, a->m_Pow);
        a = a->m_Next;
    }
    printf("%ix^%i\n", a->m_Mul, a->m_Pow);
}

int powExists(int targetPow, TITEM *item){
    while(item != NULL){
        if(item->m_Pow == targetPow){
            return 1;
        } else {
            item = item->m_Next;
        }
    }
    return 0;
}

TITEM * getSmallest(TITEM * a, TITEM * b){
    if(a->m_Pow < b->m_Pow) {
        return a;
    } else if(a->m_Pow > b->m_Pow){
        return b;
    }
    return NULL;
}
 
TITEM * addPoly ( TITEM * a , TITEM * b )
{
    TITEM *cloneA = a, *cloneB = b, *newNode = NULL;
    if(cloneA == NULL || cloneB == NULL) return NULL;
    while(cloneA->m_Next != NULL){
        if(cloneA->m_Pow < cloneA->m_Next->m_Pow){
            cloneA = cloneA->m_Next;
        } else {
            return NULL;
        }
    }
    while(cloneB->m_Next != NULL){
        if(cloneB->m_Pow < cloneB->m_Next->m_Pow){
            cloneB = cloneB->m_Next;
        } else {
            return NULL;
        }
    }
    cloneA = a;
    cloneB = b;
//   printf("Kek 1\n");
    int inLoop = 1;
    while(inLoop){
//                printf("Kek 2\n");
        if(cloneA != NULL && cloneB != NULL){
//                    printf("EV 1\n");
            TITEM * smaller = getSmallest(cloneA, cloneB);
        if(smaller == NULL){
            int newPow = cloneA->m_Pow;
            int newNum = cloneA->m_Mul + cloneB->m_Mul;
            newNode = createItem(newNum, newPow, newNode);
            cloneA = cloneA->m_Next;
            cloneB = cloneB->m_Next;
//            printTree(newNode);
        } else {
            if(smaller->m_Pow == cloneA->m_Pow){
                newNode = createItem(cloneA->m_Mul, cloneA->m_Pow, newNode);
                cloneA = cloneA->m_Next;
//                printTree(newNode);
            } else {
                newNode = createItem(cloneB->m_Mul, cloneB->m_Pow, newNode);
                cloneB = cloneB->m_Next;
//                printTree(newNode);
            }
        }
        } else if(cloneA != NULL && cloneB == NULL){
//                    printf("EV 2\n");
            newNode = createItem(cloneA->m_Mul, cloneA->m_Pow, newNode);
            cloneA = cloneA->m_Next;
//            printTree(newNode);
        } else if(cloneA == NULL && cloneB != NULL){
//                    printf("EV 3\n");
            newNode = createItem(cloneB->m_Mul, cloneB->m_Pow, newNode);
            cloneB = cloneB->m_Next;
//            printTree(newNode);
        } else {
//                    printf("EV 4\n");
            inLoop = 0;
        }
    }
    return newNode;

}
 
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TITEM * a, * b;
    TITEM * res;
 
    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
        printTree(a);
    printTree(b);
    printTree(res);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res ); 
 /*
    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,2,createItem (2,3,createItem(1,0,NULL))));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,1,NULL));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
 
    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
    b = createItem (0,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
 
    a = createItem (3,0,createItem (2,1,createItem (5,3,NULL)));
    b = createItem (-7,0,createItem (-2,1,createItem (-5,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == -4 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
 
    a = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    b = createItem (-3,1,createItem (2,2,createItem (-4,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 0 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res ); */
 
    return 0;
}
#endif /* __PROGTEST__ */