#include <stdio.h>
#include <math.h>
/*
Initialiyujeme strukturu bodu
*/
struct bod{
    int x;
    int y;
};

/**
 * 
 * Podle teorie, kazdy obdelnik je pravouhly a proto postaci u kazde strany overit,
 * zda tvori skalarni soucin k jednomu bodu
*/
int makesScalar(struct bod a, struct bod b, struct bod c){
    if((b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y) == 0){ //Kontrolujeme skalarni soucin, pro jistotu, i na opak. Pokud je 0, pak tvori pravy uhel
        return 0; //v mem C neni return booleanu, takze nahradime intem...
    }
    return 1;
}
/**
 * Ted overujeme, zda vsechny body tvori skalarni soucin rovny nule.
 * Pro jistotu, prosvapujeme vsechny body, kdyby byl vstu napr a,c,b,d;
*/
int checkForRectangle(struct bod a, struct bod b, struct bod c, struct bod d){
    if((makesScalar(a,b,c) == 0 && makesScalar(b,c,d) == 0 && makesScalar(c,d,a) == 0) || //abcd
        (makesScalar(b,c,a) == 0 && makesScalar(c,a,d) == 0 && makesScalar(a,d,b) == 0) || //bcad
        (makesScalar(c,a,b) == 0 && makesScalar(a,b,d) == 0 && makesScalar(b,d,c) == 0) || //cabd
        (makesScalar(a,b,d) == 0 && makesScalar(b,d,c) == 0 && makesScalar(d,c,a) == 0)){ //abdc
        return 0;
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