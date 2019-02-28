   #include <pthread.h>
   #include <unistd.h>
   #include <stdio.h>

   static void *child(void *ignored){
      printf( "......Child started, sleeping 3000 milliseconds...\n" );
      sleep(3);
      printf( "......Child is done sleeping 3 seconds.\n\n" );
      return NULL;
   }

   int main(int argc, char *argv[]){
      pthread_t child_thread;
      int code;

      printf( "\n...Starting program schedPracticeMac [in c]...\n" );
      printf( "......Parent started, will start children then sleep waiting for keypress...\n\n" );
      code = pthread_create(&child_thread, NULL, child, NULL);
      if(code){
         fprintf(stderr, "pthread_create failed with code %d\n", code);
      }

      sleep(5);
      printf("......Parent is done sleeping 5 seconds.\n\n");
      return 0;
   }
            