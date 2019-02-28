/**
 * filename: schedPracticePC.c
 * prupose: thread and scheduler demonstrator on windows
 * \author: Dr. Johnson
 * \date:   2019-02-10
 * \description: starts a thread for each simulated process, running
 *					them until the time runs out for that thread, and
 *					displaying the time used from that time slice and
 *					the time remaining for each thread.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI ThreadFunc( LPVOID );

int main( int argc, char * argv[] ) {
	HANDLE hThread;
	DWORD  threadID;
	int    data[2];
	int    i;

	printf( "argc = %d\n", argc );
   if( 1 == argc ) {
      printf( "\n\n   Usage: schedPracticePC A 100 B 200 C 130 D 74 ...");
      printf( "\n       Where 'A' is a thread identifier letter, and" );
      printf( "\n             '100' is the number of milliseconds that thread requires" );
      printf( "\n                to run to completion\n\n\n" );
      exit( 0 );
   } else {
   	printf( "\n  Processing.....\n\n"  );
   }
	for( i = 1; i < argc; i++ ) {
		data[0] = (int)argv[i];
		data[1] = atoi( argv[i+1] );
		hThread = CreateThread( NULL, 0, ThreadFunc, (LPVOID)data, 0, &threadID );
		if( hThread ) {
			printf( "Child thread %d launched...\n", i );
		}
		Sleep( 1000 );
	}

  // wait for the threads to complete
	printf( "[Waiting for threads to complete...]\n" );
	Sleep( 10000 );
	printf("\n\nMain program completed\n");
	return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc( LPVOID n ) {

   int d[2];
	int i;

	// d[0] = (int)n[0];
	d[1] = (int)n[1];

	for( i = 0; i < 10; i++ ) {
		for( int j = -1; j < (int)n; j++ ) {
			printf( " " );
		}
		printf( "Child thread %d executes iteration: %d\n", n, i );
		Sleep( 1000 );
	}
	printf( "Child thread %d completed\n", n );
	return 0;
}
