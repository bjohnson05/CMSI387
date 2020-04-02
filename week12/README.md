# Week 12 Demonstration Files

The files in this directory are the ones shown in class the week of March 30th, 2020.

Both of these programs should work the same on either Windows or Mac/Linux platforms.  They were written on a PC, and have not been tested on Mac as yet; if any issues arise, contact me and I'll update appropriately.

## File Handler Demostration

The filehandler.c program is to denostrate a simple file copy program using the system call versions of open, read, write, and close, which are different from the "C" versions, as mentioned in class.

For PC, compile with "gcc filehandler.c -o filehander.exe" then run using "filehander this.txt that.txt"
For Mac, compile with "gcc filehandler.c -o filehandler" then run using "./filehandler this.txt that.txt"

The "this.txt" file is included for convenience.  Feel free to substitute any file you like, of any variety.

## Lseek Demonstration

The lseekdemo.c program is to show how a file is treated as a stream of bytes, and how the lseek system command can be used to locate specific information, leading to the idea of breaking a sequential file into more of a two-dimensional array for easier location of information.

For PC, compile with "gcc lseekdemo.c -o lseekdemo.exe" then run using "lseekdemo lseektest.txt"
For Mac, compile with "gcc lseekdemo.c -o lseekdemo" then run using "./lseekdemo lseektest.txt"

The "lseektest.txt" file is included for convenience.  Feel free to substitute any file you like, of any variety.


