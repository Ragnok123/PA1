#include <stdio.h>
#include <math.h>

int main (void){
	double aX, aY, bX, bY, cX, cY;
	printf("Bod A:\n");
	if(scanf(" %d %d ", &aX, &aY) != 2){
		printf("Nespravny vstup.\n");
		return 1;
	}
	printf("Bod B:\n");
	if(scanf(" %d %d ", &bX, &bY) != 2){
		printf("Nespravny vstup.\n");
		return 1;
	}
	printf("Bod C:\n");
	if(scanf(" %d %d ", &cX, &cY) != 2){
		printf("Nespravny vstup.\n");
		return 1;
	}
	if((aY - bY) * (aX - cX) == (aY - cY) * (aX - bX)){
		if((aX == bX && aY == bY) || (aX == cX && aY == cY) || (bX == cX && bY == cY) || (aX == bX && aX == cX && aY == bY && aY == cY)){
			printf("Nektere body splyvaji.");
		} else {
			printf("Body lezi na jedne primce.");
		}
		return 0;
	} else {
		printf("Body nelezi na jedne primce.");
		return 1;
	}
	return 0;
}