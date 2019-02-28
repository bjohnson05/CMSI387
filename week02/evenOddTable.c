/**
 * filename   : evenOddTable.c
 * purpose    : demonstrate "C" code for practice
 * author     : Dr. Johnson
 * date       : 2019-01-17
 * description: 
 *    1. Write a program to vary the value of an integer variable i 
 *          from -10 to +10 and output a simple table.
 *    2. For each value, print i as well as the value of i times i.
 *    3. Also print out whether i is even or odd by displaying the 
 *          word EVEN or ODD at the end of each line.
 *    4. Separate the output into columns to make a table using the 
 *          tab character "\t".
 *    5. Count the number of EVEN and ODD values, and display the 
 *          counts at the end of the table after a blank line.
 *    6. Try to make all the output columns line up neatly. You can 
 *          decide whether they are left- or right- justified. 
 *          Left is easier, but right looks nicer for the numbers.
 */

#include <stdio.h>
#include <stdlib.h>


int main( int argc, char * argv[] ) {

   int i = -10;
   printf( "\n\n   EVEN/ODD TABLE\n\n" );

   while( i < 11 ) {
      printf( "\t%3d\t%3d\t%s\n", i, (i * i), ((i % 2) == 0) ? "EVEN" : "ODD" );
      i++;
   }
   exit( 0 );

}
