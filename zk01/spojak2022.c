#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct TItem {
    char * word;
    struct TItem * next;
    struct TItem * prevWord;
    struct TItem * nextWord;
} TITEM;


void deleteList (TITEM * l)
{
    while ( l )
    {
        TITEM * tmp = l -> next;
        free ( l->word );
        free ( l );
        l = tmp;
    }
}



//================================================================

TITEM * addWord(TITEM * node, char * word){
    if(node == NULL){
        node = (TITEM*) malloc(sizeof(TITEM));
        node->next = NULL;
        node->word = word;
        node->nextWord = NULL;
        node->prevWord = NULL;
        return node;
    }
    TITEM *tmp = node;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    TITEM *newNode = (TITEM*) malloc(sizeof(TITEM));
    newNode->word = word;
    newNode->next = NULL;
    newNode->prevWord = NULL;
    newNode->nextWord = NULL;
    tmp->next = newNode;

    return node;
}

void printTree(TITEM *item){
    while(item->next != NULL){
        printf("%s -> ", item->word);
        item = item->next;
    }
    printf("%s", item->word);
}

TITEM * StringToList ( const char * string){
    if(string == NULL) return NULL;
    int index = 0;
    TITEM *newNode = NULL;
    char *word = NULL;
    int wordIndex = 0;
    int wordCapacity = 0;
    while(string[index] != '\0'){
        if((string[index] >= 'a' && string[index] <= 'z') || ((string[index] >= 'A' && string[index] <= 'Z'))){
            if(wordCapacity == 0){
                wordCapacity = 16;
                word = (char*)malloc(wordCapacity * sizeof(char));
            } else if(wordIndex == wordCapacity){
                wordCapacity *= 2;
                word = (char*)realloc(word, wordCapacity*sizeof(char));
            }
            word[wordIndex++] = string[index];
        } else {
            if(word != NULL){
                word[wordIndex] = '\0';
                newNode = addWord(newNode, word);
                word = NULL;
                wordCapacity = 0;
                wordIndex = 0; 
            }
        }
        index++;
    }
    if((string[index-1] >= 'a' && string[index-1] <= 'z') || ((string[index-1] >= 'A' && string[index-1] <= 'Z'))){
        if(word != NULL){
            word[wordIndex] = '\0';
            newNode = addWord(newNode, word);
            word = NULL;
            wordCapacity = 0;
            wordIndex = 0; 
        }
    }
    //printTree(newNode);

    TITEM *tmp = newNode;
    while(tmp!=NULL){
        TITEM *next = tmp;
        while(next != NULL){
            if(strcmp(tmp->word, next->word) == 0 && tmp != next){
                tmp->nextWord = next;
                next->prevWord = tmp;
                break;
            }
            next = next->next;
        }
        tmp=tmp->next;
    }

    return newNode;
}

//================================================================

int main() {

    TITEM * a;
    char test1[] = "Na louce rostou rostou kvetiny Na";
    a = StringToList ( test1 );

    assert ( strcmp ( "Na", a->word ) == 0 );
    assert ( strcmp ( "louce", a->next->word ) == 0 );
    assert ( strcmp ( "rostou", a->next->next->word ) == 0 );
    assert ( strcmp ( a->next->next->word, a->next->next->next->word ) == 0 );
    assert ( strcmp ( "kvetiny", a->next->next->next->next->word ) == 0 );
    assert ( strcmp ( a->word, a->next->next->next->next->next->word ) == 0 );
    assert ( a->next->next->next->next->next->next == NULL );

    assert ( a->next->next->next->next->next == a->nextWord );
    assert ( a->prevWord == NULL );
    assert ( a->next->next->next->next->next->nextWord == NULL );
    assert ( a->next->next->next->next->next->prevWord == a );
    assert ( a->next->next->nextWord == a->next->next->next );
    assert ( a->next->next == a->next->next->next->prevWord );
    assert ( ( a->next->nextWord == NULL ) && ( a->next->prevWord == NULL ) );
    assert ( ( a->next->next->next->next->nextWord == NULL ) && ( a->next->next->next->next->prevWord == NULL ) );

    deleteList ( a );

    char test2[] = "        Na1louce,rostou/(_)\\rostou+kvetiny  Na  [0][1][2]";
    a = StringToList ( test2 );

    assert ( strcmp ( "Na", a->word ) == 0 );
    assert ( strcmp ( "louce", a->next->word ) == 0 );
    assert ( strcmp ( "rostou", a->next->next->word ) == 0 );
    assert ( strcmp ( a->next->next->word, a->next->next->next->word ) == 0 );
    assert ( strcmp ( "kvetiny", a->next->next->next->next->word ) == 0 );
    assert ( strcmp ( a->word, a->next->next->next->next->next->word ) == 0 );
    assert ( a->next->next->next->next->next->next == NULL );

    assert ( a->next->next->next->next->next == a->nextWord );
    assert ( a->prevWord == NULL );
    assert ( a->next->next->next->next->next->nextWord == NULL );
    assert ( a->next->next->next->next->next->prevWord == a );
    assert ( a->next->next->nextWord == a->next->next->next );
    assert ( a->next->next == a->next->next->next->prevWord );
    assert ( ( a->next->nextWord == NULL ) && ( a->next->prevWord == NULL ) );
    assert ( ( a->next->next->next->next->nextWord == NULL ) && ( a->next->next->next->next->prevWord == NULL ) );

    deleteList ( a );

    char test3[] = "DIFF diff";
    a = StringToList ( test3 );

    assert ( strcmp ( "DIFF", a->word ) == 0 );
    assert ( strcmp ( "diff", a->next->word ) == 0 );
    assert ( a->next->next == NULL );

    assert ( ( a->nextWord == NULL ) && ( a->prevWord == NULL ) );
    assert ( ( a->next->nextWord == NULL ) && ( a->next->prevWord == NULL ) );

    deleteList ( a );

    char test4[] = "assert assert assert";
    a = StringToList ( test4 );

    assert ( ( strcmp ( "assert", a->word ) == 0 )
             && ( strcmp ( "assert", a->next->word ) == 0 )
             && ( strcmp ( "assert", a->next->next->word ) == 0 ) );

    assert ( a->nextWord == a->next );
    assert ( a->prevWord == NULL );
    assert ( a->next->nextWord == a->next->next );
    assert ( a->next->prevWord == a );
    assert ( a->next->next->nextWord == NULL );
    assert ( a->next->next->prevWord == a->nextWord );

    deleteList ( a );

    return 0;
}