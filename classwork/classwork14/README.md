
# Week 14 In-Class Exercise

## Roll Your Own Command Line

In this directory is a version of the code from the "microshell" program from figure 7.6 on page 279 of your text book, but re-written in "C".  

## For this exercise...
...you will modify the code to accept multiple words on the command line instead of single words. The second word on the command line will be an "option" which will be passed to the command as it is run by the "exec" command.  As you can see when you download the code, it uses the "fork" and "execlp" system calls [for Mac/Linux] and the "CreateProcess()" system call [for Win32] to create another process and run the command.

### For Mac/Linux
...you will need to use a different version of the "execlp()" command, namely "execvp" to pass the words as command line arguments to the command your program will run.

### For Windows
...you will need to add the extra commands to the variable that is passed to the "CreateProcess()" system call.

## The specifications are as follows:

1. Create the file <code>commandlineMac.c</code> or <code>commandlinePC.c</code> as is appropriate for the system you are on.
1. Copy the code from the applicable file in this directory above into your file.
1. Save the file, compile it, and run it to make sure it works.<br />**Make sure you understand how the code actually works** for your particular version.
1. Test the program using the "pwd" and/or the "ls" and/or the "dir" command to be sure it works properly.
1. You should see a prompt telling you to enter one word; when you do, it should execute that command and then prompt again.
1. Be sure to also test the "exit" command. Feel free to include all of the "printf()" statements you like, to see what is happening in the code.
1. Look up online to find the way to change the "execlp()" function call into its "execvp()" counterpart.
1. Make the appropriate changes to your code to allow for having parameters on the command line within your program. For example, instead of simply "ls", get your program to work when given the command "ls -alF".
1. Pat yourself on the back for having written a basic command line interface! You have now forked a process and seen how processes work in action!
