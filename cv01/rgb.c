#include <stdio.h>
#include <math.h>

int main (void){
	int x,y,z;
	printf("Zadejte barvu v RGB formatu:\n");
	if(scanf(" rgb ( %i , %i , %i ) ", &x, &y, &z) != 3){
		printf("Nespravny vstup.\n");
		return 1;
	}
	if(x < 0 || x > 255 || y < 0 || y > 255 || z < 0 || z > 255){
		printf("Nespravny vstup.\n");
		return 1;
	}
	
	printf("#%02X%02X%02X\n", x & 0xFF, y & 0xFF, z & 0xFF);
	return 0;
}
