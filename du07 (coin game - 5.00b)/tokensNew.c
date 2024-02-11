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