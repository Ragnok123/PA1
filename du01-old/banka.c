#include <stdio.h>
#include <math.h>

int main (void){
	double kredit, debet;
	int den;
	int amount;
	int memoryDay = 0;
	int memoryAmount = 0;
	printf("Zadejte kreditni urok [%]:\n");
	scanf("%d", kredit);
	printf("Zadejte debetni urok [%]:\n");
	scanf("%d", debet);
	printf("Zadejte transakce:\n");
	while(amount != 0){
		if(scanf("%i %i", den, amount) != 2){
			printf("Nespravny vstup.");
			return 1;
		}
		if(!(den > memoryDay)){
			printf("Nespravny vstup.");
			return 1;
		}
		memoryDay = day;
		memoryAmount += amount;
	}
	return 0;
}