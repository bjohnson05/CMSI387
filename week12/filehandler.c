/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *    filename :  filehandler.c
 *    purpose  :  sample file copy utility showing use of system calls
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
   printf( "\n\n   USAGE: filehandler <source> <target>\n" );
   printf( "         where:\n" );
   printf( "      <source> is the path/filename of the file to be copied\n" );
   printf( "      <target) is the path/filename of the file copied INOT\n\n" );
}

int main( int argc, char *argv[] ) {

   printf( "\n   compile test: hello world!\n\n" );

   char buffer[BUFFER_SIZE];  // buffer to hold file contents 4K at a time
   int inputFD;               // input file descriptor
   int outputFD;              // output file descriptor
   int readCount;             // count of bytes read from source
   int writeCount;            // count of bytes written to target

  // check to make sure there is enough information from the command line
   if( 3 != argc ) {
      printUsage();
      exit( -1 );
   }

   printf( "   ...all good!\n\n" );

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

  //  then the output file
   outputFD = creat( argv[2], OUTPUT_MODE );
   if( outputFD < 0 ) {
      printf( "\n   Problem opening file '%s'...\n\n", argv[2] );
      printUsage();
      exit( -3 );
   }

  // now time to copy the source to the target
   while( 1 ) {
      readCount = read( inputFD, buffer, BUFFER_SIZE );
      if( readCount <= 0 ) {
         break;                  // read the whole thing
      }
      writeCount = write( outputFD, buffer, readCount );
      if( writeCount <= 0 ) {
         printf( "\n   Problem writing target '%s'\n\n", argv[2] );
         exit( -4 );
      }
   }

  // close the files and exit the program
   close( inputFD );
   close( outputFD );
   exit( 0 );

}
