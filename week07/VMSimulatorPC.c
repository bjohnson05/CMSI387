#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define FRAME_ARRAY_SIZE 4096
#define NUMBER_OF_PAGES     4

int *pageFrames;     // used for an array of page frames of FRAME_ARRAY_SIZE size each
int *frameStart;     // used to keep a permanent reference to the start of pageFrames
int *pageTable;      // used for an array of page REFERENCES to find the page table
int *tableStart;     // used to keep a permanent referrece to the start of pageTable

DWORD WINAPI myThread( LPVOID );

typedef struct ThreadData_t {
   int threadID;
   int time;
   int startAddress;
} ThreadData_t;

DWORD WINAPI myThread( LPVOID argStruct ) {
   ThreadData_t *myData = (ThreadData_t*)argStruct;
   printf( "      in myThread, " );
   if( 0 == myData->time ) {
      myData->time = 17;
   }
   printf( "thread number: %d, time: %d, address: %d...\n", myData->threadID, myData->time, myData->startAddress );
   int instruction = 0;
   int pageAddress = myData->startAddress;
   for( int i = 0; i < myData->time; i++ ) {
      instruction = *(&pageAddress);
      printf( "         Thread number %d, executing VM instruction: %d\n", myData->threadID, instruction );
      Sleep( 100 );
      pageAddress += sizeof(int);
   }
   Sleep( myData->time );
   return 0;
}

int main( int argc, char * argv[] ) {

   HANDLE hThreads[NUMBER_OF_PAGES];
   DWORD  threadIDs[NUMBER_OF_PAGES];
   struct ThreadData_t tData[NUMBER_OF_PAGES];

   printf( "\n\n   Welcome to the Virtual Memory Base Table Simulator......\n" );

  // allocate space for the page table
   pageTable = (int *)malloc( sizeof(int) * NUMBER_OF_PAGES );
   if( NULL == pageTable ) {
      printf( "\n    Could not allocate array of %d size.\n\n", NUMBER_OF_PAGES );
      exit( -1 );
   }
   printf( "\n   Array of size %d allocated for page table...\n", NUMBER_OF_PAGES );
   tableStart = pageTable;

  // allocate space for the page frames
   pageFrames = (int *)malloc( (sizeof(int) * FRAME_ARRAY_SIZE) * NUMBER_OF_PAGES );
   if( NULL == pageFrames ) {
      printf( "\n    Could not allocate array of %d size.\n\n", FRAME_ARRAY_SIZE );
      exit( -1 );
   }
   printf( "\n   Array of size %d allocated for page frames, now filling with random int values...\n\n", \
                FRAME_ARRAY_SIZE * NUMBER_OF_PAGES );
   frameStart = pageFrames;

  // Fill up the page frames with random numbers to simulate program code in each page
   srand( time(0) );  // Feed me, Seymore!!
   for( int i = 0; i < FRAME_ARRAY_SIZE * NUMBER_OF_PAGES; i++ ) {
      *pageFrames = (rand() % RAND_MAX);
      pageFrames++;
   }

  // Load the pageTable with the values of the starting locations of the four frames
   int j = 0;
   for( int i = 0; i < NUMBER_OF_PAGES; i++ ) {
      *pageTable = (int)&pageFrames[j];    // the first one is just the start of the whole thing
      pageTable++;
      j += FRAME_ARRAY_SIZE;
   }

  // NOW the fun begins
  // We need to create four threads, each one will read from the array at a different page
  //  the page table slot will be determined by the thread's initialization
  //  the page frame starting location will be determined by the VALUE in the page table slot
  //  the thread will read and display a certain number of "pseudo-instructions" for each time
  //    it is accessed
   for( int i = 0; i < NUMBER_OF_PAGES; i++ ) {
      tData[i].threadID = i;
      tData[i].time = 123 * ((rand() % NUMBER_OF_PAGES) + 1);
      tData[i].startAddress = pageTable[i];
      hThreads[i] = CreateThread( NULL, 0, myThread, (LPVOID)(&tData[i]), 0, &threadIDs[i] );
      // hThreads[i] = CreateThread( NULL, 0, myThread, (LPVOID)i, 0, &threadIDs[i] );
      if( hThreads[i] ) {
         printf( "      myThread %d created successfully and launched...\n", i );
         Sleep( 1000 );
      } else {
         fprintf( stderr, "CreateThread failed on myThread %d with code %d\n", hThreads[i] );
      }
   }
   Sleep( 2000 );


  // free up the memory we've used
   free( pageFrames );
   free( pageTable );

}
