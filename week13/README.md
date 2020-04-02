# Week 13 Demonstration Files

These files are the beginning of the keylogger in-class exercise for week 13.<br />
[Note: this is the PC version only as of the first commit; mac version will be coming soon]

Clone the repo or copy the class to your local machine and compile with:

gcc keylogger.c -o keylogger.exe   [for PC]
gcc keylogger.c -o keylogger [for Mac/Linux]

then run with:

keylogger logfilename.txt

The program is in an infinite loop by design, so you must use "control+C" to stop it.  This fact is true for either type of machine; in other words, it's CONTROL plus C on Mac, not COMMAND plus C.

I've also found that technically you don't need to add the "exe" to the PC compile output name, it will be automatically added for you.

## Initial Version
For this initial version the key logger reads and echos each key press to the console window.  You must enter at least 255 characters to get the output into the file.  Each output writes another buffer-full of key press information to the file, but if there are not at least 255 characters you will get no output, other than the starting time stamp.

Another problem with this initial version is that if you kill the program while the buffer has less than the required 255 key presses, you will lose the last values.

Finally, this version will OVER-WRITE the previous output if you stop and re-start the keylogger.

## Your Task
For this in-class exercise, you should modify the keylogger.c program to do the following:
* write each character to the log file as it is pressed
* append the data from each subsequent running of the program to the same file if the same log file name is given
* change the program so the key presses are NOT echoed to the console when they occur

## Completion
Once you have the keylogger working per the requirements tasks above, see what you can do to make it run in the background.  Hide the file by putting it in some other directory than the one the program is located in.


