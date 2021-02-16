#include <stdio.h>

int main( int argc, char * argv ) {

   // declare and initialize some stuff
   double x, y, *p;
   x = 123.45;
   y = 678.9;
   p = 0;
   printf( "\n\n   after initialization... " \
           "x is: %f, y is: %f, and p is: %d\n", \
            x, y, p );

   // now assign the pointer p to the address of x
   p = &x;
   printf( "\n\n   after assignment of p... " \
           "x is: %f, y is: %f, and p is: %d\n", \
            x, y, p );

   // now assign the value @ pointer p to y
   y = *p;
   printf( "\n\n   after assignment of y... " \
           "x is: %f, y is: %f, and p is: %d\n", \
            x, y, p );

}