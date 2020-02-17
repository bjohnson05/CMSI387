   #include <stdio.h>
   #include <stdlib.h>

   int mutex = 1;
   int full  = 0;
   int empty = 7;          // maximum of seven messages in buffer
   int x     = 0;

   int myWait( int s ) {
      return( --s );
   }

   int mySignal( int s ) {
      return( ++s );
   }

   int main()
   {
      int n;
      void producer();
      void consumer();

      while( 1 ) {
         printf( "\n\n   1.Producer\n   2.Consumer\n   3.Exit" );
         printf("\n      Enter your choice: ");
         scanf("%d",&n);
         switch( n ) {
            case 1:  if( (mutex == 1) && (empty != 0) ) {
                        producer();
                     } else {
                        printf( "\nBuffer is full!!" );
                     }
                     break;
            case 2:  if( (mutex == 1) && (full != 0) ) {
                        consumer();
                     } else {
                        printf("\nBuffer is empty!!");
                     }
                     break;
            case 3:
            default: exit( 0 );
                     break;
         }
      }
      return 0;
   }

   void producer() {
      mutex = myWait( mutex );
      full  = mySignal( full );
      empty = myWait( empty );
      x++;
      printf( "\n  Producer produces the item %d", x );
      mutex = mySignal( mutex );
   }

   void consumer()
   {
      mutex = myWait( mutex );
      full  = myWait( full );
      empty = mySignal( empty );
      printf( "\n  Consumer consumes item %d", x );
      x--;
      mutex = mySignal( mutex );
   }
