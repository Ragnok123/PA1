#ifndef __PROGTEST__
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>
#endif /* __PROGTEST__ */

long long avg3 ( long long a, long long b, long long c )
{
  long long avg = 0;
    if (a>=LLONG_MAX || b>=LLONG_MAX || c>=LLONG_MAX) {
        avg = LLONG_MAX;
    } else {
        avg = (a+b+c)/3;
    }
    return avg;
}

#ifndef __PROGTEST__
int main (int argc, char * argv [])
{
  assert ( avg3 ( 1, 2, 3 ) == 2 );
  assert ( avg3 ( -100, 100, 30 ) == 10 );
  assert ( avg3 ( 1, 2, 2 ) == 1 );
  assert ( avg3 ( -1, -2, -2 ) == -1 );
  assert ( avg3 ( LLONG_MAX, LLONG_MAX, LLONG_MAX ) == LLONG_MAX );
  return 0;
}
#endif /* __PROGTEST__ */

