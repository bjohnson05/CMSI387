/**
 * filename    : boundedPC.c
 * purpose     : thread demonstrator on windows
 * \author     : Dr. Johnson
 * \date       : 2019-02-01
 * \description: starts two threads and gives visible feedback
 *    of those threads running as a producer and a consumer with
 *    interleaving of output.  Messages are simulated by simply
 *    incrememting and decrementing a counter.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI producer( LPVOID );
DWORD WINAPI consumer( LPVOID );


int mutex = 1;
int full  = 0;
int empty = 7;          // maximum of seven messages in buffer
int x     = 0;

int wait_( int s ) {
   return( --s );
}

int signal_( int s ) {
   return( ++s );
}

DWORD WINAPI producer( void *ignored ) {
   while( empty != 0 ) {
      if( (mutex == 1) && (empty != 0) ) {
         mutex = wait_( mutex );
         full  = signal_( full );
         empty = wait_( empty );
         x++;
         printf( "  Producer produces the item %d\n", x );
         mutex = signal_( mutex );
      } else {
         printf( "  Buffer is full!!\n" );
      }
      Sleep( 123 );
   }
   return 0;
}

DWORD WINAPI consumer( void *ignored ) {
   while( empty != 0 ) {
      if( (mutex == 1) && (full != 0) ) {
         mutex = wait_( mutex );
         full  = wait_( full );
         empty = signal_( empty );
         printf( "  Consumer consumes item %d\n", x );
         x--;
         mutex = signal_( mutex );
      } else {
         printf("  Buffer is empty!!\n");
      }
      Sleep( 159 );
   }
   return 0;
}

int main() {
   HANDLE hThread1;
   HANDLE hThread2;
   DWORD  threadID1;
   DWORD  threadID2;

   int n;
   int wait_( int );
   int signal_( int );
   int count = 0;
   int code = 0;

   printf( "\n...Starting program schedPracticeMac [in c]...\n" );
   printf( "......Parent started, will start children then sleep waiting for keypress...\n\n" );
   hThread1 = CreateThread( NULL, 0, producer, (LPVOID)n, 0, &threadID1 );
   if( hThread1 ) {
      printf( "Producer thread launched...\n" );
   } else {
      fprintf( stderr, "CreateThread failed on producer with code %d\n", hThread1 );
   }
   hThread2 = CreateThread( NULL, 0, consumer, (LPVOID)n, 0, &threadID2 );
   if( hThread2 ) {
      printf( "Producer thread launched...\n" );
   } else {
      fprintf( stderr, "CreateThread failed on consumer with code %d\n", hThread2 );
   }

   while( count < 10 ) {
         printf( "  parent is sleeping for one second....\n" );
         Sleep( 1000 );
      count++;
   }
   printf("......Parent is done.\n\n");
   return 0;
}
