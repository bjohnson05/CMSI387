/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * filename: schedPracticeMac.c
 * prupose: thread and scheduler demonstrator on Mac/POSIX
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
#include <pthread.h>
#include <unistd.h>

// This is the data structure we will use to pass arguments to the children
struct MyData {
   char threadLetter;
   int  secondsToRun;
};

#define TIME_SLICE 40

// This is the child thread function that will be started by "pthread_create()"
static void *child( void *passedData ) {

   struct MyData *childData = (struct MyData*)passedData;  // data struct passed in
   char threadLetter = childData->threadLetter;            // remember the struct is a pointer
   int  timeToLive   = childData->secondsToRun;            //   so we use the "->" to access fields

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
      sleep( 1 );
   }
   return NULL;
}

//
// the "main()" begins here
//
int main(int argc, char *argv[]){

   pthread_t     child_thread;      // the child thread code
   int           code = 0;          // the return code from pthread_create
   struct MyData *data;             // pointer to local copy of MyData struct
   int           threadCount = 0;   // number of threads to be run
   int           totalTime = 0;     // total thread running time from command line

   // Check to make sure there are enough arguments to run, output usage message
   if( (1 == argc) || (0 == (argc % 2)) ) {
      printf( "\n\n   Usage: schedPracticeMac A 100 B 200 C 130 D 74 ...");
      printf( "\n       Where 'A' is a thread identifier letter, and" );
      printf( "\n             '100' is the number of milliseconds that thread requires" );
      printf( "\n                to run to completion\n\n\n" );
   } else {
      printf( "\n  Processing.....\n\n"  );
      threadCount = (argc - 1) / 2;
      data = malloc( sizeof( struct MyData ) * threadCount );
      printf( "\n...Starting program schedPracticeMac [in c]...\n" );
      printf( "......Parent started, will start children then wait for threads to finish...\n\n" );
   }

   // Main processing loop, loads the values to pass to the thread
   //   then spawns the thread and checks for an error
   for( int i = 1; i < argc; i += 2 ) {
      data->threadLetter = *argv[i];
      data->secondsToRun = atoi( argv[i + 1]);
      totalTime += data->secondsToRun;
      code = pthread_create( &child_thread, NULL, child, (void*)data );
      if( code ) {
         printf( "   ERROR: problem starting child thread %d:%c ~ ERROR: %d\n", i, data->threadLetter, code );
      }
      sleep( 1 );
   }

   // calculate the wait time for the "main()" and sleep for that long
   totalTime = (int)(totalTime / TIME_SLICE);
   sleep( totalTime );
   free( data );
   printf("\n   All threads completed ~ thanks for joining us today.\n\n");
   return 0;
}
