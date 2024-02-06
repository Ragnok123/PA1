#include <stdio.h>
#include <math.h>

int main (void) {

    double a = 0;
    double b = 0;
    double result = 0;
    char operation, equality;

    printf("Zadejte vzorec:\n");
    if(scanf(" %lf %c %lf %c", &a, &operation, &b, &equality) != 4 || (equality != '=') ) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    switch (operation) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0) {
                printf("Nespravny vstup.\n");
                return 1;
            } else {
                result = truncl(a/b);
            }
            break;
        default:
            printf("Nespravny vstup.\n");
            return 1;
    }

    printf("%lg\n", result);

    return 0;
}