#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    size_t timeDepartment, timeArrival;
    int maxCapacity;
    char *train;
}Train;

int validInput(char *input){
    if(input == NULL){
        return 0;
    }
    if(input[0] == '+'){
        input = input + 2;
        int h1,h11, m1,m11, s1,s11, h2,h22, m2,m22, s2, s22;
        int capacity;
        char string[4097];
        int charactersProcessed = 0;
        if(sscanf(input, " %d:%d:%d %d:%d:%d %d %4096s%n", &h1, &m1, &s1, &h2, &m2, &s2, &capacity, string, &charactersProcessed) != 8){
            return 0;
        }
        
        if(input[charactersProcessed+1] != '\0'){ 
            return 0;
        }
        printf("Data: %d:%d:%d %d:%d:%d %d %s", h1,m1,s1,h2,m2,s2,capacity, string);
        return 1;
    } else if(input[0] == '?'){
        input = input+2;
        int h1,m1,s1;
        int capacity;
        int a = 0;              // limiter
        if(sscanf(input, "%d:%d:%d %d%n", &h1,&m1,&s1,&capacity, &a) != 4 || input[a+1] != '\0'){
            printf("Index: %i\n",a);
            return 0;
        }
        return 1;
    } else {
        return 0;
    }
}

int main(){

    char *buffer = NULL;
    size_t size = 0;

    while(getline(&buffer,&size, stdin) != -1){

        if(!validInput(buffer)){
            free(buffer);
            printf("Nespravny vstup.\n");
            return 1;
        }

        free(buffer);
        buffer = NULL;
        size = 0;
    }

    free(buffer);

    return 0;
}