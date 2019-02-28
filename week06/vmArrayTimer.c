#include <stdio.h>
#include <stdlib.h>

int main( int argc, char * argv[] ) {
   
   int arraySize = 0;
   int *vmArray;
   int randomValue = 0;

   if( 1 == argc ) {
      printf( "\n\n   Please enter one argument, the array size.\n\n" );
      exit( 0 );
   }
   arraySize = atoi( argv[1] ) ;
   printf( "\n\n   OK, using array of %d elements.\n\n", arraySize );

   vmArray = (int *)malloc( sizeof(int) * arraySize );
   if( NULL == vmArray ) {
      printf( "\n    Could not allocate array of %d size.\n\n", arraySize );
      exit( -1 );
   }

   printf( "\n  Array allocated, now filling with random int values...\n" );
   srand( 17 );

   for( int i = 0; i < arraySize; i++ ) {
      vmArray[i] = (rand() % 100);
   }
   printf( "\n\n    Array element 23 is %d\n", vmArray[23] );
   printf( "    Array element 49 is %d\n", vmArray[49] );
   printf( "    Array element 02 is %d\n", vmArray[2] );
   printf( "    Array element 97 is %d\n", vmArray[97] );
   printf( "    Array element %d is %d\n", (arraySize - 1), vmArray[(arraySize - 1)]);

   for( int i = 0; i < arraySize; i+=4096 ) {
      printf( "    Array element %d is %d\n", i, vmArray[i]);
   }

   free( vmArray );

}