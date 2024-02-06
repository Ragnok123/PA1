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
/*
int minValueForPlayerB(int arr[], int takeTwo, int takeTwoB, int left, int right, int offset1L, int offset1R, int offset2L, int offset2R, int offset3L, int offset3R, int offset4L, int offset4R, int offset5L, int offset5R){
    return (takeTwoB ? Min5(
        solve(arr,left+offset1L,right+offset1R,1, 1), //takes 1
        solve(arr,left+offset2L,right+offset2R,1,1),
        solve(arr,left+offset3L,right+offset3R,takeTwo,0), //takes 2 
        solve(arr,left+offset4L,right+offset4R,takeTwo,0),
        solve(arr,left+offset5L,right+offset5R,takeTwo,0)
    ) : Min( solve(arr,left+offset1L,right+offset1R, 1,1), //takes 1
        solve(arr,left+offset2L,right+offset2R,1, 1)));
} */

int solve(int player, int array[], int left, int right, int totalScore, int takeTwo, int takeTwoB, int *optimalMove) {
    if(left > right) return totalScore;
    int bestOption;
    if(player == 0) {
        int option1 = solve(1, array, left + 1, right, totalScore + array[left], 1, takeTwoB, optimalMove);
        int option2 = solve(1, array, left, right - 1, totalScore + array[right], 1,  takeTwoB, optimalMove);
        if(takeTwo && (right-left) >= 1){
            int option3 = solve(1, array, left+2, right, totalScore + array[left] + array[left+1], 0, takeTwoB, optimalMove);
            int option4 = solve(1, array, left, right-2, totalScore + array[right] + array[right-1], 0, takeTwoB, optimalMove);
            int option5 = solve(1, array, left+1, right-1, totalScore + array[left] + array[right], 0, takeTwoB, optimalMove);
            bestOption = Max5(option1, option2, option3, option4, option5);
            if(bestOption == option1){
                *optimalMove = MODE_LEFT;
            } else if(bestOption == option2){
                *optimalMove = MODE_RIGHT;
            } else if(bestOption == option3){
                *optimalMove = MODE_LEFT_2;
            } else if(bestOption == option4){
                *optimalMove = MODE_RIGHT_2;
            } else if(bestOption == option5){
                *optimalMove = MODE_LEFT_RIGHT;
            }
            return bestOption;
        }
        bestOption = Max(option1, option2);
        if(bestOption == option1){
            *optimalMove = MODE_LEFT;
        } else if(bestOption == option2){
            *optimalMove = MODE_RIGHT;
        }
        return bestOption;
    } else{
        int option1 = solve(0, array, left + 1, right, totalScore, takeTwo, 1, optimalMove);
        int option2 = solve(0, array, left, right - 1, totalScore, takeTwo,  1, optimalMove);
        if(takeTwoB && (right-left) >= 1){
            int option3 = solve(0, array, left+2, right, totalScore, takeTwo, 0, optimalMove);
            int option4 = solve(0, array, left, right-2, totalScore, takeTwo, 0, optimalMove);
            int option5 = solve(0, array, left+1, right-1, totalScore, takeTwo, 0, optimalMove);
            bestOption = Min5(option1, option2, option3, option4, option5);
            if(bestOption == option1){
                *optimalMove = MODE_LEFT;
            } else if(bestOption == option2){
                *optimalMove = MODE_RIGHT;
            } else if(bestOption == option3){
                *optimalMove = MODE_LEFT_2;
            } else if(bestOption == option4){
                *optimalMove = MODE_RIGHT_2;
            } else if(bestOption == option5){
                *optimalMove = MODE_LEFT_RIGHT;
            }
            return bestOption;
        }
        bestOption = Min(option1, option2);
        if(bestOption == option1){
            *optimalMove = MODE_LEFT;
        } else if(bestOption == option2){
            *optimalMove = MODE_RIGHT;
        }
        return bestOption;
    }
    return 0;
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
    if(count == 0){
        printf("Nespravny vstup.\n");
        return 1;
    }
    int left = 0;
    int right = count-1;
    int total = totalTokens(tokens, count);

    int optimalMove = 0;
    int sumA = 0;
    sumA = solve(0, tokens, left, right, sumA,1,1, &optimalMove);
    int sumB = total - sumA;
    int movedPlayer = 0;

    int tmp = 0;
    int tmpA = 1;
    int tmpB = 1;
    while(right-left >= 0 && optimalMove != 0){
        //printf("\n");
        //printf("A2: %i, B2: %i\n", tmpA, tmpB);
        //printf("left: [%i] ...... right: [%i]\n", left, right);
        //for(int i = left; i <= right; i++){
        //    printf("%i ", tokens[i]);
        //}
        //printf("\n");
        char player = movedPlayer ? 'B' : 'A';
        solve(movedPlayer,tokens, left, right, tmp, tmpA,tmpB, &optimalMove);
        //printf("Tah: %i\n", optimalMove);
        switch(optimalMove){
            case MODE_LEFT:
                printf("%c [%i]: %i\n", player, left, tokens[left]);
                left += 1;
                if(movedPlayer){
                    tmpB = 1;
                } else {
                    tmpA = 1;
                }
                movedPlayer = 1 - movedPlayer;
            break;
            case MODE_RIGHT:
                printf("%c [%i]: %i\n", player, right, tokens[right]);
                right -=1;
                if(movedPlayer){
                    tmpB = 1;
                } else {
                    tmpA = 1;
                }
                movedPlayer = 1 - movedPlayer;
            break;
            case MODE_LEFT_2:
                printf("%c [%i], [%i]: %i + %i\n", player, left, left+1, tokens[left], tokens[left+1]);
                left += 2;
                if(movedPlayer){
                    tmpB = 0;
                } else {
                    tmpA = 0;
                }
                movedPlayer = 1 - movedPlayer;
            break;
            case MODE_RIGHT_2:
                printf("%c [%i], [%i]: %i + %i\n", player, right, right-1, tokens[right], tokens[right-1]);
                right -= 2;
                if(movedPlayer){
                    tmpB = 0;
                } else {
                    tmpA = 0;
                }
                movedPlayer = 1 - movedPlayer;
            break;
            case MODE_LEFT_RIGHT:
                printf("%c [%i], [%i]: %i + %i\n", player, left, right, tokens[left], tokens[right]);
                left += 1;
                right -=1;
                if(movedPlayer){
                    tmpB = 0;
                } else {
                    tmpA = 0;
                }
                movedPlayer = 1 - movedPlayer;
            break;
        }
    }
    printf("A: %i, B: %i\n", sumA, sumB);
    return 0;
}