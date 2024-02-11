#include <stdio.h>
#include <stdlib.h>

/**
 *              
*/

int divideString(int *options, char *string, int count, int maxWhiteSpaces, int currentIndex){

}



int main(){

    char *string = "aBc";
    int count = 3;
    int maxWhiteSpaces = count-1;

    int options = 0;

    divideString(&options, string, count, maxWhiteSpaces, 0);
    // aBc(length 3, max 2, whitespaces 0, index 0) -> a Bc (ano) -> a B c (ne)
    //                                              -> aB c (ano) -> a B c (ne)


    // abcd (1)
    // a bcd  (1)                                           ab cd (1)                             abc d
    // a bc d (0)     a b cd(0)   a b c d (0)               a b cd(0)   ab c d   a b c d          ab c d      a bc d     a b c d

    

    return 0;
}