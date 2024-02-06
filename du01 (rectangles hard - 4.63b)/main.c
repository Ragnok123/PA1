#include <stdio.h>
#include <math.h>
#define PRECIZE 1e-3 // 0.001


/*
Initializujeme strukturu bodu
*/
struct bod{
    double x;
    double y;
};

/**
 * Podle teorie, kazdy obdelnik je pravouhly a proto postaci u kazde strany overit,
 * zda tvori skalarni soucin k jednomu bodu
*/
int makesScalar(struct bod a, struct bod b, struct bod c){
    if(fabs((b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y)) < PRECIZE){ //Kontrolujeme skalarni soucin, pro jistotu, i na opak. Pokud je 0, pak tvori pravy uhel
        //UPD.: zjistilo se, ze nektere hodnoty v inputu nedavaji presnou 0, ale 0.0003 (kvuli reprezentaci dat). Tudiz musime kontrolovat ne 0, ale zda je blizko 0.
        return 0;
    }
    return 1;
}

/*
Taky my zkontrolujeme i delku stran.
*/
double delkaStrany(struct bod a, struct bod b){
    return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}

/**
 * Ted overujeme, zda vsechny body tvori skalarni soucin rovny nule.
 * Pro jistotu, prosvapujeme vsechny body, kdyby byl vstu napr a,c,b,d;  //// DO HAJE, TO NE, NEBYLO TO V ZADANI!!! Ale kod je dobre zachovat
*/
int checkForRectangle(struct bod a, struct bod b, struct bod c, struct bod d){
    if((makesScalar(a,b,c) == 0 && makesScalar(b,c,d) == 0 && makesScalar(c,d,a) == 0)){// || //abcd
       // (makesScalar(b,c,a) == 0 && makesScalar(c,a,d) == 0 && makesScalar(a,d,b) == 0) || //bcad
       // (makesScalar(c,a,b) == 0 && makesScalar(a,b,d) == 0 && makesScalar(b,d,c) == 0) || //cabd
       // (makesScalar(a,b,d) == 0 && makesScalar(b,d,c) == 0 && makesScalar(d,c,a) == 0)){ //abdc
        double ab = delkaStrany(a, b);
        double bc = delkaStrany(b, c);
        double cd = delkaStrany(c, d);
        double da = delkaStrany(d, a);
        double ac = delkaStrany(a, c);
        double bd = delkaStrany(b, d);
        // kontrolujeme, zda dve opacne strany jsou stejne dlouhe, ale zaroven i uhlopricky
        if(fabs(ab - cd) < PRECIZE && fabs(bc - da) < PRECIZE && fabs(ac - bd) < PRECIZE){
            return 0;
        }
        return 1;
    }
    return 1;
}

/*
* Osetrime vstup podle formatu...
*/
int read_bod(struct bod *b) {
    char leva_zavorka, carka, prava_zavorka;
    if (scanf(" %c %lf %c %lf %c ", &leva_zavorka, &b->x, &carka, &b->y, &prava_zavorka) == 5 && leva_zavorka == '(' && carka == ',' && prava_zavorka == ')') {
        return 0;
    } else {
        return 1;
    }
}


int main (void){
    struct bod a, b, c, d;
    printf("Bod #1:\n");
    if(read_bod(&a) == 1){
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Bod #2:\n");
    if(read_bod(&b) == 1){
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Bod #3:\n");
    if(read_bod(&c) == 1){
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Bod #4:\n");
    if(read_bod(&d) == 1){
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    if(checkForRectangle(a,b,c,d) == 0){
        printf("Body tvori obdelnik.\n");
    } else {
        printf("Body netvori obdelnik.\n");
    }
    return 0;
}