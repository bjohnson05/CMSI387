/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *    filename :  lseekdemo.c
 *    purpose  :  sample file seeker utility showing use of system calls
 *    author   :  Dr. Johnson
 *    date     :  2020-03-28
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE     4096              // use a buffer size of 4096 bytes
#define OUTPUT_MODE     0700              // protection patter for chmod

void printUsage() {
   printf( "\n\n   USAGE: lseekdemo <source> <target>\n" );
   printf( "         where:\n" );
   printf( "      <source> is the path/filename of the file to be copied\n" );
   printf( "      <target) is the path/filename of the file copied INOT\n\n" );
}

int main( int argc, char *argv[] ) {

   printf( "\n   compile test: hello world!\n\n" );

   char buffer[BUFFER_SIZE];  // buffer to hold file contents 4K at a time
   int inputFD;               // input file descriptor
   int offset = 447;          // file offset; for lorem ipsum
                              //    should point to "C" in "Curabitur"
   int readCount;             // count of bytes read from source

  // check to make sure there is enough information from the command line
   if( 2 != argc ) {
      printUsage();
      exit( -1 );
   }

   printf( "   ...arguments all good!\n\n" );

  // it's all good, so the source is in args[1] and target in args[2]
  //  they are already strings so no conversion is needed
  //  be sure to check the open return values for errors!
  //  first the input file
   inputFD = open( argv[1], O_RDONLY );
   if( inputFD < 0 ) {
      printf( "\n   Problem opening file '%s'...", argv[1] );
      printUsage();
      exit( -2 );
   }

   printf( "   ...file open all good!\n\n" );

  // seek to a specific address in the file, then read one character and
  //  display it to the screen
   readCount = lseek( inputFD, offset, SEEK_SET );
   readCount = read( inputFD, buffer, 9 );
   printf( "   read character '%s' from file\n\n", buffer );


  // close the files and exit the program
   close( inputFD );
   exit( 0 );

}

