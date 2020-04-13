/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *    filename :  CI-pc.c  [Command Intepreter - PC version
 *    purpose  :  Sample command line intepreter program that uses execlp to execute commands
 *    author   :  Dr. Johnson
 *    date     :  2020-04-08
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
   #include <stdio.h>
   #include <string.h>
   #include <stdlib.h>
   #include <windows.h>
   #include <process.h>

   #define  FALSE    0
   #define  TRUE     1

   int main( int argc, char * argv[] ) {
      char input[25];
      char command[255];
      int  retval = 0;
      int  running = FALSE;

      STARTUPINFO si;
      PROCESS_INFORMATION pi;

      ZeroMemory( &si, sizeof(si) );
      si.cb = sizeof(si);
      ZeroMemory( &pi, sizeof(pi) );

     // loop forever until the user inputs "exit"
      while( TRUE ) {

        // put up a prompt
         printf( "\nNeed input [one word only] <== " );

        // read the user input
         if( NULL == gets( input ) ) {   // Note this produces a warning!
            printf( "\n   Sorry, can't do that....\n\n" );
            return -1;
         }

        // check for the word "exit" to quit
         if( 0 == strncmp( input, "exit", 4 ) ) {        // provides a way to "quit"
            return 0;

        // it's not "exit" so "fork" a new child process to handle the command
        //  Note that Win32 doesn't have "fork()" so we have to use "CreateProcess()" instead
         } else {

            printf( "   ...forking new process with CreateProcess to run command %s\n", input );
            sprintf( command, "C:\\Windows\\System32\\cmd.exe /C %s", input );
            printf( "      command line is: %s\n", command );
            retval = CreateProcess( NULL,    // NULL means use the command line; else, need full path name [and /C option?]
                                    command,   // Command to execute
                                    NULL,    // Process handle not inheritable
                                    NULL,    // Thread handle not inheritable
                                    FALSE,   // Set handle inheritance to FALSE
                                    0,       // No creation flags
                                    NULL,    // Use parent's environment block
                                    NULL,    // Use parent's starting directory
                                    &si,     // Pointer to STARTUPINFO structure
                                    &pi );   // Pointer to PROCESS_INFORMATION structure
            if( !retval ) {
               printf( "      CreateProcess failed ~ cannot execute command.\n" );
               printf( "         error code is [%d]\n", retval );
            } else {

              // wait for the forked child to finish
               WaitForSingleObject( pi.hProcess, INFINITE );

              // Close process and thread handles.
               CloseHandle( pi.hProcess );
               CloseHandle( pi.hThread );
            }
         }
      }
   }
