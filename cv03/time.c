#include <stdio.h>
#include <math.h>

int main (void){
	int hour1,min1,sec1, mil1, hour2,min2,sec2,mil2;
	printf("Zadejte cas t1:\n");
	if(scanf(" %02i : %02i : %02i , %03i ", &hour1, &min1, &sec1, &mil1) != 4){
		printf("Nespravny vstup.\n");
		return 1;
	}
	if(hour1 < 0 || hour1 > 23 || min1 < 0 || min1 > 59 || sec1 < 0 || sec1 > 59 || mil1 < 0 || mil1 > 999){
		printf("Nespravny vstup.\n");
		return 1;
	}
	long time1 = (hour1 * 3600) + (min1 * 60) + sec1 + (long) (mil1 / 1000);
	printf("Zadejte cas t2:\n");
	if(scanf(" %02i : %02i : %02i , %03i ", &hour2, &min2, &sec2, &mil2) != 4){
		printf("Nespravny vstup.\n");
		return 1;
	}
	if(hour2 < 0 || hour2 > 23 || min2 < 0 || min2 > 59 || sec2 < 0 || sec2 > 59 || mil2 < 0 || mil2 > 999){
		printf("Nespravny vstup.\n");
		return 1;
	}
	long time2 = (hour2 * 3600) + (min2 * 60) + sec2 + (long) (mil2 / 1000);
	if(time1 > time2){
		printf("Nespravny vstup.\n");
		return 1;
	}
	printf("Sekundy: %02i", sec2);
	printf("Mil2: %03i \n",mil2);
	printf("Sekundyfull: %ld\n", (long) sec2 + (long)(mil2 / 1000));
	printf("Zlomek sekund: %ld\n", (long)(mil2 / 1000));
	printf("Doba 2: %03ld \n",time2);
	
	long time = time2 - time1;
	
	int hour = ((int) time) / 3600;
	int minutes = (((int) time) % 3600 ) / 60;
	int seconds = ((int)time) % 60;
	int milliseconds = (time - (hour * 3600) - (minutes * 60) - seconds) * 1000;
	
	printf("Doba: %02i:%02i:%02i,%03i", hour, minutes, seconds, milliseconds);
	return 0;
}
