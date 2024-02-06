#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#define MAP_MAX 200
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

int tryAndStepAbove(int altitude[][MAP_MAX], int y, int x, int areas){
    if(y-1 < 0) return 0;
    if(altitude[y-1][x] < altitude[y][x]){
        printf("Stepping above from %i,%i to %i,%i.\n", y,x, y-1, x);
        if(areas == 0) areas++;
        areas += tryAndStepAbove(altitude, y-1, x, areas);
    }
    printf("Stepped %i steps\n", areas);
    return areas;
}
int tryAndStepDown(int altitude[][MAP_MAX], int y, int x, int size, int areas){
    if(y+1 >= size) return 0;
    if(altitude[y+1][x] < altitude[y][x]){
        printf("Stepping down from %i,%i to %i,%i.\n", y,x, y+1, x);
        if(areas == 0) areas++;
        areas += tryAndStepDown(altitude, y+1, x, size, areas);
    }
    printf("Stepped %i steps\n", areas);
    return areas;
}

int tryAndStepLeft(int altitude[][MAP_MAX], int y, int x, int areas){
    if(x-1 < 0) return 0;
    if(altitude[y][x-1] < altitude[y][x]){
        printf("Stepping left from %i,%i to %i,%i.\n", y,x, y, x-1);
        if(areas == 0) areas++;
        areas += tryAndStepLeft(altitude, y, x-1, areas);
    }
    printf("Stepped %i steps\n", areas);
    return areas;
}

int tryAndStepRight(int altitude[][MAP_MAX], int y, int x, int size, int areas){
    if(x+1 >= size) return 0;
    if(altitude[y][x+1] < altitude[y][x]){
        printf("Stepping right from %i,%i to %i,%i.\n", y,x, y, x+1);
        if(areas == 0) areas++;
        areas += tryAndStepRight(altitude, y, x+1, size, areas);
    }
    printf("Stepped %i steps\n", areas);
    return areas;
}

void calculateArea(int altitude[][MAP_MAX], int size, int area[][MAP_MAX]){
    for (int y = 0; y < size; y++){
        for (int x = 0; x < size; x++){
          int minArea = 1;
          int topLength = tryAndStepAbove(altitude, y, x, 0);
          int bottomLength = tryAndStepDown(altitude, y, x, size, 0);
          int leftLength = tryAndStepLeft(altitude, y, x, 0);
          int rightLength = tryAndStepRight(altitude, y, x, size, 0);
          int width = leftLength + rightLength;
          int height = topLength + bottomLength;
          area[y][x] = minArea = width * height;
        }
    }
}

int calculateSquare(int altitude[][MAP_MAX], int size, int area[][MAP_MAX], int y, int x){
    int maxArea = 1; // Minimální velikost území je 1 (hrad zabírá jeden čtverec)
    int hradAltitude = altitude[y][x]; // Nadmořská výška hradu
    int subAreas[size][size];
    // Projít všechny možné obdélníky
    int h, w, i, j;
    for (h = 0; h < size; h++){
        for (w = 0; w < size; w++){
            int isValid = 1;
            int isHighest = 1;
            // Projít všechny čtverce v obdélníku
            for(i = y; i <= h; i++){  //y+h
                for (j = x; j <=w; j++){ // x+w
                    if(altitude[y][x] != altitude[h][w]){
                        printf("Vyrez: [%d,%d] - [%d,%d]\n", y,x,h,w);
                        // Pokud je nadmořská výška čtverce v obdélníku vyšší než nadmořská výška hradu, přeskočit tento obdélník
                        if (altitude[i][j] >= hradAltitude && (i != y || j != x)){
                            isValid = 0;
                            isHighest = 0;
                            subAreas[i][j] = h*w;
                            //printf("Ve vyrezu [%d,%d] - [%d,%d] se nasel hrad s vyskou %d, nejvyssi ale musi byt %d\n.", y,x,h,w, altitude[i][j], hradAltitude);
                            //printf("Nejvetsi pocet na [%d,%d]: %d\n", i,j, subAreas[i][j]);
                            break;
                        }
                    }
                }
                if (!isValid) break;
            }
            // Aktualizovat maximální velikost území
            if (isValid && isHighest && h * w > maxArea){
                maxArea = h * w;
            }
        }
    }
    return maxArea;
}

void castleArea(int altitude[][MAP_MAX], int size, int area[][MAP_MAX]){
    int y, x;
    for (y = 0; y < size; y++){
        for (x = 0; x < size; x++){
            area[y][x] = calculateSquare(altitude,size,area,y,x);
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
  //assert ( identicalMap ( result, area4, 5 ) );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */