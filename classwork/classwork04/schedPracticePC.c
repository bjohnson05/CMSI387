/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * filename: schedPracticePC.c
 * prupose: thread and scheduler demonstrator on Windows without POSIX
 * \author: Dr. Johnson
 * \date:   2019-02-10
 * \description: starts a thread for each simulated process, running them until the time
 *                slice runs out for that thread, and displaying the time used for that
 *                thread and the time remaining for that thread.  The main program must
 *                wait until all the threads have completed, so the "quick and dirty"
 *                way is to just calculate a sleep time that is long enough duration to
 *                ensure the main won't stop while the children are running.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Revision History:
 *  =================
 *  Vers.     Date     Modified by:  Reason for modification
 *  -----  ----------  ------------  -----------------------------------------------------
 *  1.0.0  2019-02-10  B.J. Johnson  Initial coding and release
 *  1.1.0  2020-02-14  B.J. Johnson  Fixed for updated gcc compiler, and to pass structs
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// This is the data structure we will use to pass arguments to the children
typedef struct {
   char threadLetter;
   int  secondsToRun;
} MyData;

#define TIME_SLICE 40
#define SLEEP_MULTIPLIER 250

// This is the child thread function that will be started by "CreateThread()"
DWORD WINAPI child( LPVOID passedData ) {

   MyData *childData = (MyData*)passedData;           // data struct passed in
   char threadLetter = childData->threadLetter;       // remember the struct is a pointer
   int  timeToLive   = childData->secondsToRun;       //   so we use the "->" to access fields

   // Loop until the time to live expires, then exit
   while( timeToLive >= 0 ) {
      timeToLive -= TIME_SLICE;
      if( timeToLive <= 0 ) {
         if( (timeToLive + TIME_SLICE) != 0 ) {
            printf( "%c:%d:done\n", threadLetter, timeToLive + TIME_SLICE );
         }
      } else {
         printf( "%c:%d:%d\n", threadLetter, TIME_SLICE, timeToLive );
      }
      Sleep( 500 );
   }
   return 0;

}

//
// the "main()" begins here
//
int main( int argc, char * argv[] ) {
   DWORD  threadID;           // ID of the threads when they are spawned
   MyData *data;              // pointer to local copy of MyData struct
   int    i;
   int    j = 0;              // thread handle array index
   int    threadCount = 0;    // number of threads to be run
   int    totalTime   = 0;    // total thread running time from command line

   // Check to make sure there are enough arguments to run, output usage message
   if( (1 == argc) || (0 == (argc % 2)) ) {
      printf( "\n\n   Usage: schedPracticeMac A 100 B 200 C 130 D 74 ...");
      printf( "\n       Where 'A' is a thread identifier letter, and" );
      printf( "\n             '100' is the number of milliseconds that thread requires" );
      printf( "\n                to run to completion\n\n\n" );
   } else {
      printf( "\n  Processing.....\n\n"  );
      threadCount = (argc - 1) / 2;
      data = (MyData *)malloc( sizeof( MyData ) * threadCount );
      printf( "\n...Starting program schedPracticepc [in c]...\n" );
      printf( "......Parent started, will start children then wait for threads to finish...\n\n" );
   }

   // Create the thread handle array, then spawn the threads
   HANDLE hThread[threadCount];
   for( i = 1; i < argc; i += 2 ) {
      data->threadLetter = *argv[i];
      data->secondsToRun = atoi( argv[i + 1]);
      totalTime += data->secondsToRun;
      hThread[j] = CreateThread( NULL, 0, child, (LPVOID)data, 0, &threadID );
      if( !hThread[j++] ) {
         printf( "   ERROR: problem starting child thread %d:%c ~ ERROR: %d\n", i, data->threadLetter, hThread );
      }
      Sleep( 1000 );
   }

  // wait for the threads to complete
   totalTime = (int)(totalTime / TIME_SLICE);
   printf( "\n   main sleeping for %d milliSeconds to let threads finish.\n\n", totalTime * SLEEP_MULTIPLIER);
   Sleep( totalTime * SLEEP_MULTIPLIER );
   free( data );
   printf("\n   All threads completed ~ thanks for joining us today.\n\n");
   return EXIT_SUCCESS;
}

