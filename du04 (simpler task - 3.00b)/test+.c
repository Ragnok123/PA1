#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
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
                    for (int i = h_start; i <= h_end && isValid; i++) {
                        for (int j = w_start; j <= w_end && isValid; j++) {
                            if (altitude[i][j] >= hradAltitude && (i != y || j != x)) {
                                isValid = 0;
                                //printf("Ve vyrezu [%d,%d] - [%d,%d] se nasel hrad s vyskou %d, nejvyssi ale musi byt %d\n.", h_start, w_start, h_end, w_end, altitude[i][j], hradAltitude);
                            }
                        }
                    }
                    if (isValid) {
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
            if(altitude[y][x] == 1 || (!tryAndStepAbove(altitude,y,x) && !tryAndStepDown(altitude,y,x,size) && !tryAndStepRight(altitude,y,x,size) && !tryAndStepLeft(altitude,y,x))){
                area[y][x] = 1;
            } else {
                area[y][x] = calculateSquare(altitude,size,y,x);
                //printf("For coord [%i,%i] is biggest area %i\n", y,x,area[y][x]);
            }
        }
    }
}


#ifndef __PROGTEST__
bool identicalMap ( int a[][MAP_MAX], int b[][MAP_MAX], int size ){
    //printf("Result:\n");
    //printMap(a,size);
    //printf("Original\n");
    //printMap(b,size);
    for(int y = 0; y < size; y++){
        for(int x = 0; x < size; x++){
            if (a[y][x] == b[y][x]){
              //printf("Areas match");
                return true;
            }
        }
    }
//    printf("Areas dont match");
    return false;
}

int main ( int argc, char * argv [] )
{
  static int result[MAP_MAX][MAP_MAX];

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
  return EXIT_SUCCESS;
}
#endif