#include <stdio.h>
#include <math.h>
/* 1 - done
int main (void){
int a[5] = { 1, 2, 0, 3, 0 };
int * b = a + 1;

while ( b )
 {
   *b ++ = 0;
 }
 for(int i = 0; i < 5; i++){
	printf("%i,", a[i]);
 }
}*/

void foo ( int a, int b, int * c )
 {
   *c = a + b;
 }

int bar ( int x, int y )
 {
   static int * z;
   foo ( x, y, z );
   return *z;
 }

int main ( void )
 {
   printf ( "%d", bar ( 18, 17 ) );
   //neslo zkompilovat, ale nemam chybu
 }


/*3 - done
int main(void){
	char str[10] = "abcd";
	char * p1, *p2;

	p1 = str;
	p2 = str;
	*p2 = 'A';
	printf ( "%s %s", p1, p2 );
}*/

/*4 - 50/50
int * readInput ( int * nr )
 {
   int * d = NULL, * tmp = NULL, x, i;
   *nr = 0;
   while ( scanf ( "%d", &x ) == 1 ) 
    {
      tmp = (int *) malloc ( (*nr + 1) * sizeof ( int ) );
      if ( ! tmp ) 
       { 
         free ( d );
         return NULL; 
       }
      for ( i = 0; i < *nr; i ++ )
       tmp[i] = d[i];
      free ( d );
      d = tmp;
      d[ (*nr) ++ ] = x;
    } 
   free ( tmp );
   return d;
 }*/

/* 5 - done
 int foo ( int a[21], int b[44] )
 {
   return sizeof ( a ) - sizeof ( b );
 }

int main(void){
	int a[21];
int b[5];

printf ( "%d", foo ( a, b ) );
}*/