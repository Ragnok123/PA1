#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#define MAP_MAX 1000
#endif /* __PROGTEST__ */

void printMap(int map[][MAP_MAX], int size){
  for(int y = 0; y < size; y++){
        for(int x = 0; x < size; x++){
            printf("%d", map[y][x]);
            if(x < size - 1){
              printf(",");
            }
        }
        printf("\n");
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int tryAndStepAbove(int altitude[][MAP_MAX], int y, int x){
    if(y-1 < 0) return 0;
    if(altitude[y-1][x] < altitude[y][x]){
        return 1;
    }
    return 0;
}
int tryAndStepDown(int altitude[][MAP_MAX], int y, int x, int size){
    if(y+1 >= size) return 0;
    if(altitude[y+1][x] < altitude[y][x]){
        return 1;
    }
    return 0;
}

int tryAndStepLeft(int altitude[][MAP_MAX], int y, int x){
    if(x-1 < 0) return 0;
    if(altitude[y][x-1] < altitude[y][x]){
        return 1;
    }
    return 0;
}

int tryAndStepRight(int altitude[][MAP_MAX], int y, int x, int size){
    if(x+1 >= size) return 0;
    if(altitude[y][x+1] < altitude[y][x]){
        return 1;
    }
    return 0;
}

int calculateSquare(int altitude[][MAP_MAX], int size, int y, int x) {
    int maxArea = 1; // Minimální velikost území je 1 (hrad zabírá jeden čtverec)
    int hradAltitude = altitude[y][x]; // Nadmořská výška hradu

    for (int h_start = 0; h_start < size; h_start++) {
        for (int w_start = 0; w_start < size; w_start++) {
            for (int h_end = h_start; h_end < size; h_end++) {
                for (int w_end = w_start; w_end < size; w_end++) {
                    int isValid = 1;

                    // Projít všechny čtverce v obdélníku
                    for (int i = h_start; i <= h_end && isValid; i++) {
                        for (int j = w_start; j <= w_end && isValid; j++) {
                            if (altitude[i][j] >= hradAltitude && (i != y || j != x)) {
                                isValid = 0;
                                //printf("Ve vyrezu [%d,%d] - [%d,%d] se nasel hrad s vyskou %d, nejvyssi ale musi byt %d\n.", h_start, w_start, h_end, w_end, altitude[i][j], hradAltitude);
                                
                            }
                        }
                    }

                    if (isValid) {
                        // Calculate the area of the submatrix
                        if (y >= h_start && y <= h_end && x >= w_start && x <= w_end) {
                            int area = (h_end - h_start + 1) * (w_end - w_start + 1);
                            if (area > maxArea) {
                                maxArea = area;
                                //printf("Hrad [%d, %d]  ma nejvyssi obsah %d v podmatici [%d,%d]-[%d,%d]\n", y, x, area, h_start, w_start, h_end, w_end);
                            }
                        }
                    }
                }
            }
        }
    }
    return maxArea;
}


void castleArea(int altitude[][MAP_MAX], int size, int area[][MAP_MAX]){
    int y, x;
    for (y = 0; y < size; y++){
        for (x = 0; x < size; x++){
            if(altitude[y][x] == 0 || (!tryAndStepAbove(altitude,y,x) && !tryAndStepDown(altitude,y,x,size) && !tryAndStepRight(altitude,y,x,size) && !tryAndStepLeft(altitude,y,x))){
                area[y][x] = 1;
            } else {
                area[y][x] = calculateSquare(altitude,size,y,x);
                //printf("For coord [%i,%i] is biggest area %i\n", y,x,area[y][x]);
            }
        }
    }
}



#ifndef __PROGTEST__
int identicalMap ( int a[][MAP_MAX], int b[][MAP_MAX], int size ){
    printf("Result:\n");
    printMap(a,size);
    printf("Original\n");
    printMap(b,size);
    for(int y = 0; y < size; y++){
        for(int x = 0; x < size; x++){
            if (a[y][x] == b[y][x]){
              printf("Areas match");
                return 1;
            }
        }
    }
    printf("Areas dont match");
    return 0;
}

int main ( int argc, char * argv [] )
{
  static int result[MAP_MAX][MAP_MAX];

static int alt00[MAP_MAX][MAP_MAX] =
  {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 }
  };
  static int area00[MAP_MAX][MAP_MAX] =
  {
    { 1, 2, 3 },
    { 2, 4, 6 },
    { 3, 6, 9 }
  };
  castleArea ( alt00, 3, result );
  identicalMap ( result, area00, 3 );
  static int alt0[MAP_MAX][MAP_MAX] =
  {
    { 1, 2 },
    { 3, 4 }
  };
  static int area0[MAP_MAX][MAP_MAX] =
  {
    { 1, 2 },
    { 2, 4 }
  };
  castleArea ( alt0, 2, result );
  identicalMap ( result, area0, 2 );
  //assert ( identicalMap ( result, area0, 2 ) );
  static int alt1[MAP_MAX][MAP_MAX] =
  {
    { 2, 7, 1, 9 },
    { 3, 5, 0, 2 },
    { 1, 6, 3, 5 },
    { 1, 2, 2, 8 }
  };
  static int area1[MAP_MAX][MAP_MAX] =
  {
    { 1, 12, 2, 16 },
    { 4, 4, 1, 2 },
    { 1, 9, 4, 4 },
    { 1, 2, 1, 12 }
  };
  castleArea ( alt1, 4, result );
  identicalMap ( result, area1, 4 ) ;
 // assert ( identicalMap ( result, area1, 4 ) );
  static int alt2[MAP_MAX][MAP_MAX] =
  {
    { 1, 2, 3, 4 },
    { 2, 3, 4, 5 },
    { 3, 4, 5, 6 },
    { 4, 5, 6, 7 }
  };
  static int area2[MAP_MAX][MAP_MAX] =
  {
    { 1, 2, 3, 4 },
    { 2, 4, 6, 8 },
    { 3, 6, 9, 12 },
    { 4, 8, 12, 16 }
  };
  castleArea ( alt2, 4, result );
  identicalMap ( result, area2, 4 ) ;
  //assert ( identicalMap ( result, area2, 4 ) );
  static int alt3[MAP_MAX][MAP_MAX] =
  {
    { 7, 6, 5, 4 },
    { 6, 5, 4, 5 },
    { 5, 4, 5, 6 },
    { 4, 5, 6, 7 }
  };
  static int area3[MAP_MAX][MAP_MAX] =
  {
    { 12, 6, 2, 1 },
    { 6, 2, 1, 2 },
    { 2, 1, 2, 6 },
    { 1, 2, 6, 12 }
  };
  castleArea ( alt3, 4, result );
   identicalMap ( result, area3, 4 ) ;
  //assert ( identicalMap ( result, area3, 4 ) );
  static int alt4[MAP_MAX][MAP_MAX] =
  {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 2, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 }
  };
  static int area4[MAP_MAX][MAP_MAX] =
  {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 25, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 }
  };
  castleArea ( alt4, 5, result );
   identicalMap ( result, area4, 5 ) ;
/*
  int matrix[MAP_MAX][MAP_MAX];
  srand(time(NULL)); // Seed the random number generator with the current time
  for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
          matrix[i][j] = rand() % 10 + 1; // Generates random values between 1 and 10
      }
  }
  castleArea(matrix, 3, result);
  printMap(result, 3);*/

  return EXIT_SUCCESS;
}
#endif