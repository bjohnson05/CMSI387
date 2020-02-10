/**
 * filename: simple2threadspc.c
 * prupose: thread demonstrator on windows
 * \author: B.J. Johnson
 * \date:   2019-02-01
 * \description: starts five threads and gives visible feedback
 *		of those threads running by displaying a number passed
 *	    in from the primary thread.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI ThreadFunc( LPVOID );

int main( int argc, char * argv ) {
	HANDLE hThread;
	DWORD  threadID;
	int i;

	for( i = 0; i < 5; i++ ) {
		hThread = CreateThread( NULL, 0, ThreadFunc, (LPVOID)i, 0, &threadID );
		if( hThread ) {
			printf( "Child thread %d launched...\n", i );
		}
		Sleep( 1000 );
	}

  // wait for the threads to complete
	printf( "\n[[Waiting for threads to complete...]]\n\n" );
	Sleep( 10000 );
	printf("\n\nMain program completed\n");
	return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc( LPVOID n ) {

	int i;
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
