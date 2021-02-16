   #include <pthread.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>

   int mutex = 1;
   int full  = 7;
   int empty = 0;          // maximum of seven messages in buffer
   int x     = 0;

   int wait_( int s ) {
      return( --s );
   }

   int signal_( int s ) {
      return( ++s );
   }

   static void *producer( void *ignored ) {
      while( 1 ) {
         if( mutex == 1 ) {
            if( x != full ) {
               mutex = wait_( mutex );
               x++;
               mutex = signal_( mutex );
               printf( "  Producer produces the item %d\n", x );
            } else {
               printf( "\t\t\tBuffer is full!!\n" );
               usleep( 567890 );
            }
         }
         usleep( 123456 );
      }
      return NULL;
   }

   static void *consumer( void *ignored ) {
      while( 1 ) {
         if( mutex == 1 ) {
            if( x != empty ) {
               mutex = wait_( mutex );
               x--;
               mutex = signal_( mutex );
               printf( "  consumer consumes the item %d\n", x );
            } else {
               printf( "\t\t\tBuffer is empty!!\n" );
            }
         }
         usleep( 135790 );
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

      printf( "\n...Starting program boundedMac [in 'c']...\n" );
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

      while( count < 25 ) {
         printf( "  parent is sleeping for one second....\n" );
         sleep( 1 );
         count++;
      }
      printf("......Parent is done.\n\n");
      return 0;
   }
