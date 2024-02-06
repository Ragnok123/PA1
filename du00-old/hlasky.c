#include <stdio.h>
#include <math.h>

int main (void){
	int hlaska;
	printf("ml' nob:\n");
	if(scanf(" %d ", &hlaska) != 1){
		printf("luj\n");
		return 1;
	}
	if(hlaska < 1 || hlaska > 9){
		printf("luj\n");
		return 1;
	}
	printf("Qapla'\n");
	if(hlaska == 1){
		printf("noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
	} else if(hlaska == 2){
		printf("bortaS bIr jablu'DI' reH QaQqu' nay'.\n");
	} else if(hlaska == 3){
		printf("Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
	} else if(hlaska == 4){
		printf("bISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");
	} else if(hlaska == 5){
		printf("qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
	} else if(hlaska == 6){
		printf("Suvlu'taHvIS yapbe' HoS neH.\n");
	} else if(hlaska == 7){
		printf("Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo.'\n");
	} else if(hlaska == 8){
		printf("Heghlu'meH QaQ jajvam.\n");
	} else if(hlaska == 9){
		printf("leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
	}
	return 0;
}
