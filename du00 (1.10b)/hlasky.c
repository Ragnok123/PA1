#include <stdio.h>
#include <math.h>

int main (void){
	int hlaska;
	printf("ml' nob:\n");
	if(scanf(" %d ", &hlaska) != 1){
		printf("Neh mi'\n");
		return 1;
	}
	if(hlaska < 0 || hlaska > 8){
		printf("Qih mi' %d\n", hlaska);
		return 1;
	}
	printf("Qapla'\n");
	if(hlaska == 0){
		printf("noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
	} else if(hlaska == 1){
		printf("bortaS bIr jablu'DI' reH QaQqu' nay'.\n");
	} else if(hlaska == 2){
		printf("Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
	} else if(hlaska == 3){
		printf("bISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");
	} else if(hlaska == 4){
		printf("qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
	} else if(hlaska == 5){
		printf("Suvlu'taHvIS yapbe' HoS neH.\n");
	} else if(hlaska == 6){
		printf("Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
	} else if(hlaska == 7){
		printf("Heghlu'meH QaQ jajvam.\n");
	} else if(hlaska == 8){
		printf("leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
	}
	return 0;
}
