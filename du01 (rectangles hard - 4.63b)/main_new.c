#include <stdio.h>
#include <math.h>


/*
Initializujeme strukturu bodu
*/
struct bod{
    int x;
    int y;
};

/**
 * Podle teorie, kazdy obdelnik je pravouhly a proto postaci u kazde strany overit,
 * zda tvori skalarni soucin k jednomu bodu
*/
int makesScalar(struct bod a, struct bod b, struct bod c){
    if((b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y) == 0){ //Kontrolujeme skalarni soucin, pro jistotu, i na opak. Pokud je 0, pak tvori pravy uhel
        //UPD.: zjistilo se, ze nektere hodnoty v inputu nedavaji presnou 0, ale 0.0003 (kvuli reprezentaci dat). Tudiz musime kontrolovat ne 0, ale zda je blizko 0.
        return 0;
    }
    return 1;
}

/*
Taky my zkontrolujeme i delku stran.
*/
double delkaStrany(struct bod a, struct bod b){
    return sqrt(((double)b.x - (double)a.x)*((double)b.x - (double)a.x) + ((double)b.y - (double)a.y)*((double)b.y - (double)a.y));
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
        if(fabs(ab - cd) == 0 && fabs(bc - da) == 0 && fabs(ac - bd) == 0){
            return 0;
        }
        return 1;
    }
    return 1;
}


int main (void){
    struct bod a, b, c, d;
    printf("Bod #1:\n");
    if(scanf(" ( %i , %i ) ", &a.x, &a.y) != 2){
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Bod #2:\n");
    if(scanf(" ( %i , %i ) ", &b.x, &b.y) != 2){
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Bod #3:\n");
    if(scanf(" ( %i , %i ) ", &c.x, &c.y) != 2){
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Bod #4:\n");
    if(scanf(" ( %i , %i ) ", &d.x, &d.y) != 2){
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