/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *    filename :  CI-mac.c  [Command Intepreter - Mac/Linux version
 *    purpose  :  Sample command line intepreter program that uses execlp to execute commands
 *    author   :  Dr. Johnson
 *    date     :  2020-04-08
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
   #include <unistd.h>
   #include <stdio.h>
   #include <sys/wait.h>
   #include <string.h>
   #include <stdlib.h>

   #define  TRUE     1

   int main() {
      char input[25];
      int  retval = 0;

     // loop forever until the user inputs "exit"
      while( TRUE ) {

        // put up a prompt
         printf( "Need input [one word only] <== " );

        // read the user input
         if( NULL == gets( input ) ) {   // Note this produces a warning!
            printf( "\n   Sorry, can't do that....\n\n" );
            return -1;
         }

        // check for the word "exit" to quit
         if( 0 == strncmp( input, "exit", 4 ) ) {        // provides a way to "quit"
            return 0;

        // it's not "exit" so fork a new child process to handle the command
         } else {
            pid_t returnedValue = fork();
            if( returnedValue < 0 ) {
               perror( "error forking" );
               return -1;

           // fork was successful, so handle the input
            } else if( returnedValue == 0 ) {
               retval = execlp( input, input, NULL );   // here's the command you'll replace
               perror( command.c_str() );
               return -1;

           // wait for the forked child to finish
            } else {
               if( waitpid( returnedValue, 0, 0 ) < 0 ) {
                  perror( "error waiting for child" );
                  return -1;
               }
            }
         }
      }
   }
