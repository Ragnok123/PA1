#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    double prumer;
} Student;

typedef struct{
    size_t size, capacity;
    Student *data;
} Array;
Array ARRAY;

void array_init(){
    ARRAY.size = 0;
    ARRAY.capacity = 16;
    ARRAY.data = (Student*) malloc(ARRAY.capacity * sizeof(Student));
}

void array_push(Array * arr, int id, double prumer){
    if(arr->size >= arr->capacity){
        arr->capacity *= 2;
        arr->data = (Student*) realloc(arr->data, arr->capacity * sizeof(Student));
    }
    Student st;
    st.id = id;
    st.prumer = prumer;
    arr->data[arr->size] = st;
    arr->size++;
}

Student array_search(Array arr, int id){
    Student search;
    search.id = -1;
    for(int i = 0; i < (int) arr.size; i++){
        if(arr.data[i].id == id){
            search.id = arr.data[i].id;
            search.prumer = arr.data[i].prumer;
            return search;
        }
    }
    return search;
}


int main(){
    array_init();
    printf("Zadejte studenty:\n");
    int id;
    double prumer;
    int inLoop = 1;
    char termination[2];
    while(inLoop){
        if(ARRAY.size > 1000000){
            printf("Nespravny vstup.\n");
            return 1;
        }
        if(scanf(" %i %lf ", &id, &prumer) == 2){
            array_push(&ARRAY, id, prumer);
        } else if(scanf("%1s", termination) == 1){
            if (termination[0] == '?') {
                inLoop = 0;
            } else if(termination[0] != ' ' || termination[0] != '\n' || termination[0] != EOF){
                printf("Nespravny vstup.\n");
                return 1;
            }
        } else {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    printf("Zadejte dotazy:\n");
    char* buffer;
    size_t capacity = 0;
    while(getline(&buffer, &capacity, stdin) != -1){
        int searchId;
        if(scanf(" %i ", &searchId) == 1){
            Student student = array_search(ARRAY, searchId);
            if(student.id != -1){
                printf("Student c. %i ma prumer %.2lf\n", searchId, student.prumer);
            } else {
                printf("Student c. %i nenalezen.\n", searchId);
            }
        } else {
            printf("Nespravny vstup.\n");
            free(buffer);
            return 1;
        }
    }
    free(buffer);
    return 0;
}