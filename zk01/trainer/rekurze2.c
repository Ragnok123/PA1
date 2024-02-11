#include <stdio.h>
#include <stdlib.h>

/**
 * 32 = 2^5
*/
void powTwo(int n, int two){
    if(two == 1024){
        printf("NO\n");
        return;
    }
    two *= 2;
    if((float)n / (float)two == 1){
        printf("A: %i, b: %i\n", n, two);
        printf("YES\n");
        return;
    }
    powTwo(n, two);
}

/*
Разложение на множители
Дано натуральное число n>1. Выведите все множители этого числа в порядке неубывания с учетом кратности.\
Алгоритм должен иметь сложность O(logn).

60 = 
    2*30
    2*2*15
    2*2*3*5

*/

int divide(int number, int delitel, int first){
    if(number == 1){
        return 0;
    }
    if(first && number % delitel == 0){
        printf("%d ", delitel);
        first = 0;
        divide(number/delitel, delitel, first);
    } 
    else if(number % delitel == 0){
        printf(" * %i ", delitel);
        divide(number/delitel, delitel, first);
    } 
    else {
        divide(number, delitel+1, first);
    }

    return 1;
}
/*
Вывести нечетные числа последовательности
Дана последовательность натуральных чисел (одно число в строке), завершающаяся числом 0. Выведите все нечетные числа из этой последовательности, сохраняя их порядок.
В этой задаче нельзя использовать глобальные переменные и передавать какие-либо параметры в рекурсивную функцию. Функция получает данные, считывая их с клавиатуры. Функция не возвращает значение, а сразу же выводит результат на экран. Основная программа должна состоять только из вызова этой функции.

*/

int main(){
    divide(438, 2, 1);
    return 0;
}