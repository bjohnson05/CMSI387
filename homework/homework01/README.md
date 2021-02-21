# CMSI 387: Homework Assignment #1
## General problems of an Introductory Nature
### Assignment Due: Friday 2021-02-05 [Friday of week 04]

<blockquote>
Learning Outcomes: Students will:
    
1. reinforce some of the basic concepts of operating systems
1. learn to spawn child threads in the <q>C</q>programming language
1. investigate interleaving two threads for efficiency
1. get extra practice with the <q>C</q> programming language
1. learn to make a Gantt chart to model different thread schedule ordering
</blockquote>

### The following guidelines are expected for all homework submissions:

* All homework must be typed. Homework which is not typed will be returned ungraded and will be subject to the late homework guidelines as set out on the syllabus page.
* PLEASE DO NOT scribble something on lined paper and rip it out of your spiral notebook — hanging chads went out with the presidential election in 2000.
* I don't care too much about what font you use or how large your margins are; however, you might want to check out a monospaced font for typing code, as it will be easy to see the indentations.
* Speaking of indenting, **PLEASE DON'T USE TABS TO INDENT YOUR CODE**.  Tabs can often get interpreted differently by different computers and applications, and could make code that is nicely formatted on your computer look <q>all over the map</q> on my computer or printer. **USE SPACES INSTEAD**. You can set up almost every modern text editor to insert spaces whenever you press the TAB key, or you can simply pound the spacebar.
* **Work with a partner**. I can't stress this enough; part of this policy is don't split up the work – **WORK TOGETHER** on the assignment. This activity mimics an industry code development model called "pair programming" which is part of the Extreme Programming software development method. Feel free to collaborate in your pairs as much as you want, doing the entire assignment together.
* **DO NOT share your work between groups**. Doing so will count as plagiarism.  If you wish to discuss solutions with another group over coffee in the Lair, that's fine as long as it is kept at the conceptual and you don't share your code between groups.  Each group needs to turn in its own version of the solutions.
* You only need to turn in one copy per group.
* Submit your homework through GitHub, in your repository, and be sure to make me a contributor so I have been allowed access. I cannot evaluate what I cannot see! If I cannot upload to your repo, you will not get a grade for the assignment.

### Problems for Assignment #1

1. What is the difference between an operating system and middleware?
1. What is the relationship between threads and processes?
1. Of all the topics previewed in chapter one of the text book, which one are you most looking forward to learning more about? Why?
1. Suppose thread A goes through a loop 100 times, each time performing one disk I/O operation, taking 10 milliseconds, and then some computation, taking 1 millisecond.  While each 10-millisecond disk operation is in progress, thread A cannot make any use of the processor.  Thread B runs for 1 second, purely in the processor, with no I/O.  One millisecond of processor time is spent each time the processor switches threads; other than this switching cost, there is no problem with the processor working on thread B during one of thread A's I/O operations.  [The processor and disk drive do not contend for memory access bandwidth, for example.]
   1. Suppose the processor and disk work purely on thread A until its completion, and then the processor switches to thread B and runs all of that thread. What will the total elapsed time be?
   1. Suppose the processor starts out working on thread A, but every time thread A performs a disk operation, the processor switches to B during the operation and then back to A upon the disk operation's completion. What will the total elapsed time be?
   1. In your opinion, which do you think is more efficient, and why?
1. Find and read the documentation for pthread_cancel().  Then, using your <q>C</q> programming environment, use the information and the model provided in Figure 2.4 on page 26 of the text book to write a program in which the initial [main] thread creates a second thread.  The main thread should sit on a read call of some kind, waiting to read input from the keyboard, waiting until the user presses the Enter key.  At that point, it should kill off the second thread and print out a message reporting that it has done so.  Meanwhile, the second thread should be in an infinite loop, each time around sleeping five seconds and then printing out a message.  Try running your program.
   1. Can the sleeping thread print its periodic messages while the main thread is waiting for keyboard input?
   1. Can the main thread read input, kill the sleeping thread, and print a message while the sleeping thread is in the early part of one of its five-second sleeps?
1. Suppose a system has three threads (T1, T2, and T3) that are all available to run at time 0 and need one, two, and three seconds of processing, respectively. Suppose each thread is run to completion before starting another. Draw six different Gantt charts, one for each possible order the threads can be run in. For each chart, compute the <q>turnaround</q> time of each thread; that is, the time elapsed from when it was ready (time 0) until it is complete. Also, compute the average turnaround time for each order.  Which order has the shortest average turnaround time? What is the name of the scheduling policy that produces this order?
1. Google the <q>C</q> standard library API and find out how to get information from the command line by using a printf() call to display a prompt, then another call [which you will look up] to get the user input. Write a program in <q>C</q> to prompt the user demographic information including name, age, class year, and any three other data times you wish. Structure the program as a "call-and-response" program such that each data item is a single question with a single answer. When all data has been obtained, display the data on the console. Each data item must be on a separate line, and it must be appropriately labeled. The output must be done using a single printf() statement.
