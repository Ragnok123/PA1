#include <stdio.h>
#include <cstdlib>

#define MAX_TOKENS 100

int tokens[MAX_TOKENS];
int optimalMoves[MAX_TOKENS*MAX_TOKENS][2];
int optimalMoveCount = 0;
int count = 0;

typedef struct Stage{
    int maxSum;
    int* moves;
};

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

void storeMove(int player, int tokenIndex, int secondTokenIndex) {
    optimalMoves[optimalMoveCount][0] = tokenIndex;
    optimalMoves[optimalMoveCount][1] = secondTokenIndex;
    optimalMoveCount++;
}

void printOptimalMoves() {
    for (int i = 0; i < optimalMoveCount; i++) {
        int tokenIndex = optimalMoves[i][0];
        int secondTokenIndex = optimalMoves[i][1];
        if (secondTokenIndex == -1) {
            printf("%c [%d]: %d\n", (i % 2 == 0) ? 'A' : 'B', tokenIndex, tokens[tokenIndex]);
        } else {
            printf("%c [%d], [%d]: %d + %d\n", (i % 2 == 0) ? 'A' : 'B', tokenIndex, secondTokenIndex, tokens[tokenIndex], tokens[secondTokenIndex]);
        }
    }
}

int minValueForPlayerB(int arr[], int takeTwo, int takeTwoB, int left, int right, int offset1L, int offset1R, int offset2L, int offset2R, int offset3L, int offset3R, int offset4L, int offset4R, int offset5L, int offset5R){
    return (takeTwoB ? Min5(
        solveBroken(arr, left+offset1L,right+offset1R,takeTwo, 1), //takes 1
        solveBroken(arr, left+offset2L,right+offset2R,takeTwo,1),
        solveBroken(arr, left+offset3L,right+offset3R,takeTwo,0), //takes 2 
        solveBroken(arr, left+offset4L,right+offset4R,takeTwo,0),
        solveBroken(arr, left+offset5L,right+offset5R,takeTwo,0)
    ) : Min( solveBroken(arr, left+offset1L,right+offset1R, takeTwo,1), //takes 1
        solveBroken(arr, left+offset2L,right+offset2R,takeTwo, 1)));
}

int solveBroken(int arr[], int left, int right, int takeTwo, int takeTwoB){

    if(left>right) return 0;
    if(right-left == 1 && (takeTwo || takeTwoB)){
        return arr[left] + arr[right];
    } else if(left==right){
        return arr[left];
    }

    int option1 = arr[left] + minValueForPlayerB(arr, 1, takeTwoB, left, right, 1, -1, 2, 0, 2, -1, 0, -2, 3, 0); //left
    int option2 = arr[right] + minValueForPlayerB(arr,1, takeTwoB, left, right,1, -1, 0, -2, 1, -2, 2, -1, 0, -3); //right
    if(takeTwo){
        int option3 = arr[left] + arr[left+1] + minValueForPlayerB(arr, 0, takeTwoB, left, right, 3, 0, 2, -1, 4, 0, 3, -1, 2, -2);
        int option4 = arr[right] + arr[right-1] + minValueForPlayerB(arr, 0, takeTwoB, left, right, 1, -2, 0, -3, 2, -2, 0, -4, 1, -3);
        int option5 = arr[left] + arr[right] + minValueForPlayerB(arr, 0, takeTwoB, left, right, 2, -1, 1, -2, 2, -2, 3, -1, 1, -3);
        int maxOption = Max5(option1, option2, option3, option4, option5);
        if(maxOption == option1){
            printf("Selected option 1\n");
        } else if(maxOption == option2){
            printf("Selected option 2\n");
        } else if(maxOption == option3){
            printf("Selected option 3\n");
        } else if(maxOption == option4){
            printf("Selected option 4\n");
        } else if(maxOption == option5){
            printf("Selected option 5\n");
        }
        printf("Highest value: %i\n", maxOption);
        return maxOption;
    }
    int maxOption = Max(option1, option2);
    printf("2 Highest value: %i\n", maxOption);
    return maxOption;
}

int maximumAmountBroken(int arr[], int n) {
    int maxSumA = solveBroken(arr, 0,n-1, 1, 1);
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
    int total = totalTokens(tokens, count);
    int sumA = maximumAmountBroken(tokens, count);
    int sumB = total - sumA;
    printOptimalMoves();
    printf("Total count: %i\n", total);
    printf("A: %i\n", sumA);
    printf("B: %i\n", sumB);

    return 0;
}