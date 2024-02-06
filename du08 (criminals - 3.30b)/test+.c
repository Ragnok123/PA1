#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCriminal
{
  struct TCriminal  * m_Next;
  char              * m_Name;
  struct TCriminal ** m_Contacts;
  size_t              m_Cnt;
  size_t              m_Capacity;
} TCRIMINAL;

#endif /* __PROGTEST__ */

int currentPool = 100;
TCRIMINAL **Pool = NULL;

int getListSize(TCRIMINAL *list) {
    TCRIMINAL *current = list;
    int size = 0;
    while (current) {
        current = current->m_Next;
        size++;
    }
    return size;
}

TCRIMINAL *createRecord(const char *name, TCRIMINAL *next){
    TCRIMINAL *newCriminal = (TCRIMINAL *)malloc(sizeof(TCRIMINAL));
    newCriminal->m_Next = next;
    newCriminal->m_Name = strdup(name);
    newCriminal->m_Contacts = NULL;
    newCriminal->m_Cnt = 0;
    newCriminal->m_Capacity = 0;
    return newCriminal;
}

void addContact(TCRIMINAL *dst, TCRIMINAL *contact){
    if(dst->m_Cnt >= dst->m_Capacity) {
        dst->m_Capacity = (dst->m_Capacity == 0) ? 2 : dst->m_Capacity * 2;
        dst->m_Contacts = (TCRIMINAL **)realloc(dst->m_Contacts, dst->m_Capacity * sizeof(TCRIMINAL *));
    }
    dst->m_Contacts[dst->m_Cnt++] = contact;
}

void freeList(TCRIMINAL *src){
    TCRIMINAL *temp;
    while(src != NULL){
        temp = src;
        src = src->m_Next;
        free(temp->m_Name);
        free(temp->m_Contacts);
        free(temp);
    }
}

TCRIMINAL *cloneList(TCRIMINAL *list){
    if (!list) return NULL;
    TCRIMINAL *newList = NULL;
    TCRIMINAL *current = NULL;
    Pool = (TCRIMINAL **) malloc(currentPool * sizeof(TCRIMINAL*));
    TCRIMINAL *tempPool;
    int index = 0;
    for(tempPool = list; tempPool != NULL; tempPool = tempPool->m_Next) {
        TCRIMINAL *copy = createRecord(tempPool->m_Name, NULL);
        if (current){
             current->m_Next = copy;
        } else{
             newList = copy;
        }
        current = copy;
        if(tempPool->m_Cnt > 0) {
            copy->m_Contacts = (TCRIMINAL **)malloc(tempPool->m_Cnt * sizeof(TCRIMINAL *));
            if (!copy->m_Contacts) {
                freeList(newList);
                return NULL;
            }
            copy->m_Capacity = tempPool->m_Cnt;
            copy->m_Cnt = tempPool->m_Cnt;
        }
        if(index >= currentPool){
            currentPool *= 2;
            Pool = (TCRIMINAL **)realloc(Pool, currentPool * sizeof(TCRIMINAL*));
        }
        Pool[index++] = copy;
    }
    index = 0;
    tempPool = NULL;
    for(tempPool = list; tempPool != NULL; tempPool = tempPool->m_Next, index++) {
        for(size_t i = 0; i < tempPool->m_Cnt; ++i) {
            int contactClone = 0;
            for(TCRIMINAL *search = list; search != NULL; search = search->m_Next, contactClone++) {
                if(search == tempPool->m_Contacts[i]) {
                    Pool[index]->m_Contacts[i] = Pool[contactClone];
                    break;
                }
            }
        }
    }
    tempPool = NULL;
    free(Pool);
    return newList;
}

#ifndef __PROGTEST__

void printList(TCRIMINAL *list, int num) {
    TCRIMINAL *current = list;
    printf("List %i\n", num);
    printf("Size: %i\n", getListSize(list));
    while (current) {
        printf("Name: %s\n", current->m_Name);
        for (size_t i = 0; i < current->m_Cnt; i++) {
            printf("  Contact: %s\n", current->m_Contacts[i]->m_Name);
        }
        printf("\n");
        current = current->m_Next;
    }
}

int main(int argc, char* argv [] ){
  TCRIMINAL * a, *b;
  char tmp[100];

  assert ( sizeof ( TCRIMINAL ) == 3 * sizeof ( void * ) + 2 * sizeof ( size_t ) );
  a = nullptr;
  a = createRecord ( "Peter", a );
  a = createRecord ( "John", a );
  a = createRecord ( "Joe", a );
  a = createRecord ( "Maria", a );
  addContact ( a, a -> m_Next );
  addContact ( a -> m_Next -> m_Next, a -> m_Next -> m_Next -> m_Next );
  addContact ( a -> m_Next -> m_Next -> m_Next, a -> m_Next );
  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Cnt == 1
           && a -> m_Contacts[0] == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Cnt == 0 );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  b = cloneList ( a );
  printList(a, 1);
  strcpy ( tmp, "Moe" );
  a = createRecord ( tmp, a );
  strcpy ( tmp, "Victoria" );
  a = createRecord ( tmp, a );
  strcpy ( tmp, "Peter" );
  a = createRecord ( tmp, a );
  addContact ( b -> m_Next -> m_Next -> m_Next, b -> m_Next -> m_Next );
  assert ( a
           && ! strcmp ( a -> m_Name, "Peter" )
           && a -> m_Cnt == 0 );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Victoria" )
           && a -> m_Next -> m_Cnt == 0 );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "Moe" )
           && a -> m_Next -> m_Next -> m_Cnt == 0 );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
           && a -> m_Next -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Cnt == 0 );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  printList(b, 2);
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Cnt == 1
           && b -> m_Contacts[0] == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Cnt == 0 );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Cnt == 1
           && b -> m_Next -> m_Next -> m_Contacts[0] == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Cnt == 2
           && b -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == b -> m_Next
           && b -> m_Next -> m_Next -> m_Next -> m_Contacts[1] == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  freeList ( a );
  addContact ( b -> m_Next, b -> m_Next );
  a = cloneList ( b );
  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Cnt == 1
           && a -> m_Contacts[0] == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Contacts[0] == a -> m_Next );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Cnt == 2
           && a -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next
           && a -> m_Next -> m_Next -> m_Next -> m_Contacts[1] == a -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Cnt == 1
           && b -> m_Contacts[0] == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Cnt == 1
           && b -> m_Next -> m_Contacts[0] == b -> m_Next );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Cnt == 1
           && b -> m_Next -> m_Next -> m_Contacts[0] == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Cnt == 2
           && b -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == b -> m_Next
           && b -> m_Next -> m_Next -> m_Next -> m_Contacts[1] == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  freeList ( b );
  freeList ( a );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
