#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NAME_LENGTH 10000
#define NUM_OF_CONTACTS 1000

void generateRandomString(char* str, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length - 1; i++) {
        int index = rand() % (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    str[length - 1] = '\0';
}

void generateRandomContact(int index, char* number, char* name) {
    int numberLength = rand() % 20 + 1;
    sprintf(number, "%0*d", numberLength, index);

    int nameLength = rand() % MAX_NAME_LENGTH + 1;
    generateRandomString(name, nameLength);
}

int main() {
    srand(time(NULL));

    for (int i = 1; i <= NUM_OF_CONTACTS; i++) {
        char number[21];
        char name[MAX_NAME_LENGTH];

        generateRandomContact(i, number, name);

        printf("+ %s %s\n", number, name);
    }

    return 0;
}