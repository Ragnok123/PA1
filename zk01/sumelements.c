#ifndef __TRAINER__
#include <assert.h>
#endif

int findCombinations(int *arr, int len, int sum, int index) {
    // Pokud jsme dosáhli konce pole
    if (index >= len) {
        // Pokud je sum rovno nule, našli jsme platnou kombinaci
        if (sum == 0)
            return 1; // Vracíme 1, protože jsme našli platnou kombinaci
        else
            return 0; // Jinak žádná platná kombinace
    }
    // Počet kombinací, kdy nezahrneme aktuální prvek
    int exclude = findCombinations(arr, len, sum, index + 1);
    // Počet kombinací, kdy zahrneme aktuální prvek a snížíme sum o hodnotu aktuálního prvku
    int include = findCombinations(arr, len, sum - arr[index], index + 1);

    return exclude + include;
}

int sumElements(int *arr, int len, int sum) {
    return findCombinations(arr, len, sum, 0);
}

#ifndef __TRAINER__
int main() {
    int input1[] = { 4, 5, 6, 7, 8, 9, 10, 11 };
    assert(sumElements(input1, sizeof(input1) / sizeof(input1[0]), 11) == 3);

    int input2[] = {1, -1, 1, -1, 0};
    assert(sumElements(input2, sizeof(input2) / sizeof(input2[0]), 0) == 12);
    return 0;
}
#endif