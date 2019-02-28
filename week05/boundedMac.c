   #include <pthread.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>
    
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

   static void *producer( void *ignored ) {
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
         usleep( 123 );
      }
      return NULL;
   }
    
   static void *consumer( void *ignored ) {
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
         usleep( 159 );
      }
      return NULL;
   }

   int main() {
      int n;
      int wait_( int );
      int signal_( int );
      int count = 0;
      int code = 0;
      pthread_t producer_thread;
      pthread_t consumer_thread;

      printf( "\n...Starting program schedPracticeMac [in c]...\n" );
      printf( "......Parent started, will start children then sleep waiting for keypress...\n\n" );
      code = pthread_create( &producer_thread, NULL, producer, NULL );
      if( code ){
         fprintf( stderr, "pthread_create failed on producer with code %d\n", code);
      } else {
         printf( " .. producer child thread started... \n" );
      }
      code = pthread_create( &consumer_thread, NULL, consumer, NULL );
      if( code ){
         fprintf( stderr, "pthread_create failed on consumer with code %d\n", code);
      } else {
         printf( " .. consumer child thread started... \n" );
      }

      while( count < 10 ) {
            printf( "  parent is sleeping for one second....\n" );
            sleep( 1 );
         count++;
      }
      printf("......Parent is done.\n\n");
      return 0;
   }
