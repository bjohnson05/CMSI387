   public class Simple2Threads {
      public static void main( String[] args ) {
         System.out.println( "\n...Starting program Simple2threads [in java]..." );
         System.out.println( "......Parent started, will start child then sleep 5000 milliseconds..." );

         Thread childThread = new Thread( new Runnable() {
            public void run() {
               System.out.println( "......Child started, sleeping 3000 milliseconds..." );
               sleep(3000);
               System.out.println( "......Child is done sleeping 3 seconds.\n" );
            }
         });

         System.out.println( "\n......Starting child thread..." );
         childThread.start();
         sleep(5000);
         System.out.println("......Parent is done sleeping 5 seconds.\n\n");

      }
      private static void sleep( int milliseconds ) {
         try{
            Thread.sleep( milliseconds );
         } catch( InterruptedException ie ) {
            // ignore this exception; it won't happen anyhow
         }
      }
   }
