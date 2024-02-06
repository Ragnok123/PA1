#include <stdio.h>
#include <cstdlib>

#define MAX_TOKENS 100
#define MODE_LEFT 1
#define MODE_RIGHT 2
#define MODE_LEFT_2 3
#define MODE_RIGHT_2 4
#define MODE_LEFT_RIGHT 5

int tokens[MAX_TOKENS];
int count = 0;

int solveBroken(int arr[], int left, int right, int takeTwo, int takeTwoB);

int Max(int a, int b) {
    return (a > b) ? a : b;
}

int Min(int a, int b) {
    return (a > b) ? b : a;
}

int Max5(int a, int b, int c, int d, int e) {
    return Max(Max(Max(Max(a, b), c), d), e);
}

int Min5(int a, int b, int c, int d, int e) {
    return Min(Min(Min(Min(a, b), c), d), e);
}

int totalTokens(int kek[], int count){
    int totalSum = 0;
    for(int i = 0; i < count; i++){
        totalSum += kek[i];
    }
    return totalSum;
}

int minimax(int player, int array[], int left, int right, int totalScore, int takeTwo, int takeTwoB, int optimalMove) {
    if(left > right) return totalScore;
    int bestOption;
    if(player == 0) {
        int option1 = minimax(1, array, left + 1, right, totalScore + array[left], 1, takeTwoB, optimalMove);
        int option2 = minimax(1, array, left, right - 1, totalScore + array[right], 1,  takeTwoB, optimalMove);
        if(takeTwo && (right-left) >= 1){
            int option3 = minimax(1, array, left+2, right, totalScore + array[left] + array[left+1], 0, takeTwoB, optimalMove);
            int option4 = minimax(1, array, left, right-2, totalScore + array[right] + array[right-1], 0, takeTwoB, optimalMove);
            int option5 = minimax(1, array, left+1, right-1, totalScore + array[left] + array[right], 0, takeTwoB, optimalMove);
            bestOption = Max5(option1, option2, option3, option4, option5);
            if(bestOption == option1){
                optimalMove = MODE_LEFT;
            } else if(bestOption == option2){
                optimalMove = MODE_RIGHT;
            } else if(bestOption == option3){
                optimalMove = MODE_LEFT_2;
            } else if(bestOption == option4){
                optimalMove = MODE_RIGHT_2;
            } else if(bestOption == option5){
                optimalMove = MODE_LEFT_RIGHT;
            }
            return bestOption;
        }
        bestOption = Max(option1, option2);
        if(bestOption == option1){
            optimalMove = MODE_LEFT;
        } else if(bestOption == option2){
            optimalMove = MODE_RIGHT;
        }
        return bestOption;
    } else{
        int option1 = minimax(0, array, left + 1, right, totalScore, takeTwo, 1, optimalMove);
        int option2 = minimax(0, array, left, right - 1, totalScore, takeTwo,  1, optimalMove);
        if(takeTwoB && (right-left) >= 1){
            int option3 = minimax(0, array, left+2, right, totalScore, takeTwo, 0, optimalMove);
            int option4 = minimax(0, array, left, right-2, totalScore, takeTwo, 0, optimalMove);
            int option5 = minimax(0, array, left+1, right-1, totalScore, takeTwo, 0, optimalMove);
            bestOption = Min5(option1, option2, option3, option4, option5);
            return bestOption;
        }
        bestOption = Min(option1, option2);
        return bestOption;
    }
    return 0;
}

int minValueForPlayerB(int arr[], int takeTwo, int takeTwoB, int left, int right, int offset1L, int offset1R, int offset2L, int offset2R, int offset3L, int offset3R, int offset4L, int offset4R, int offset5L, int offset5R){
    return (takeTwoB ? Min5(
        solveBroken(arr,left+offset1L,right+offset1R,1, 1), //takes 1
        solveBroken(arr,left+offset2L,right+offset2R,1,1),
        solveBroken(arr,left+offset3L,right+offset3R,takeTwo,0), //takes 2 
        solveBroken(arr,left+offset4L,right+offset4R,takeTwo,0),
        solveBroken(arr,left+offset5L,right+offset5R,takeTwo,0)
    ) : Min( solveBroken(arr,left+offset1L,right+offset1R, 1,1), //takes 1
        solveBroken(arr,left+offset2L,right+offset2R,1, 1)));
}

int solveBroken(int arr[], int left, int right, int takeTwo, int takeTwoB){
    if(left>right) return 0;
    if(left==right) return arr[left];
    int option1 = arr[left] + minValueForPlayerB(arr, 1, takeTwoB, left, right, 2, 0, 1, -1, 3, 0, 0, -2, 2, -1); //left
    int option2 = arr[right] + minValueForPlayerB(arr,1, takeTwoB, left, right, 1, -1, 0, -2, 2, -1, 0, -3, 1, -2); //right
    if(takeTwo){
        int option3 = arr[left] + arr[left+1] + minValueForPlayerB(arr, 0, takeTwoB, left, right, 3, 0, 2, -1, 4, 0, 2, -2, 3, -1);
        int option4 = arr[right] + arr[right-1] + minValueForPlayerB(arr, 0, takeTwoB, left, right, 1, -2, 0, -3, 2, -2, 0, -4, 1, -3);
        int option5 = arr[left] + arr[right] + minValueForPlayerB(arr, 0, takeTwoB, left, right, 2, -1, 1, -2, 3, -1, 1, -3, 2, -2);
        int maxOption = Max5(option1, option2, option3, option4, option5);
        //if(maxOption == option1){
        //    optimalMove = 1;
        //} else if(maxOption == option2){
        //    optimalMove = 2;
        //} else if(maxOption == option3){
        //    optimalMove = 3;
        //} else if(maxOption == option4){
        //    optimalMove = 4;
        //} else if(maxOption == option5){
        //    optimalMove = 5;
        //}
        return maxOption;
    }
    int maxOption = Max(option1, option2);
    //if(maxOption == option1){
    //    optimalMove = 1;
    //} else if(maxOption == option2){
    //    optimalMove = 2;
    //}
    return maxOption;
}

int maximumAmountBroken(int arr[], int left, int right) {
    int maxSumA = 0; // solveBroken(arr,0,n-1, 1, 1);
    //maxSumA = minimax(0, arr, left, right, maxSumA,1,1);
    return maxSumA;
}

int main() {
    printf("Zetony:\n");
    while (scanf(" %d ", &tokens[count]) != EOF) {
        count++;
        if (count >= MAX_TOKENS) {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    int left = 0;
    int right = count-1;

    int total = totalTokens(tokens, count);
    int optimalMove = 0;
    int sumA = 0;
    sumA = minimax(0, tokens, left, right, sumA,1,1, optimalMove);
    int sumB = total - sumA;
    int tmp = 0;
    printf("Prvni tah: %i\n", optimalMove);
    while(right-left >= 1 && optimalMove != 0){
        int movedPlayer = 0;
        char player = movedPlayer ? 'B' : 'A';
        minimax(movedPlayer,tokens, left, right, tmp, 1,1, optimalMove);
        switch(optimalMove){
            case MODE_LEFT:
                printf("%c [%i]: %i\n", player, left, tokens[left]);
                left += 1;
            break;
            case MODE_RIGHT:
                printf("%c [%i]: %i\n", player, right, tokens[right]);
                right -=1;
            break;
            case MODE_LEFT_2:
                printf("%c [%i], [%i]: %i + %i\n", player, left, left+1, tokens[left], tokens[left+1]);
                left += 2;
            break;
            case MODE_RIGHT_2:
                printf("%c [%i], [%i]: %i + %i\n", player, right, right-1, tokens[right], tokens[right-1]);
                right -= 2;
            break;
            case MODE_LEFT_RIGHT:
                printf("%c [%i], [%i]: %i + %i\n", player, left, right, tokens[left], tokens[right]);
                left += 1;
                right -=1;
            break;
        }
    }
    printf("Total count: %i\n", total);
    printf("A: %i\n", sumA);
    printf("B: %i\n", sumB);

    return 0;
}