# CMSI387

## Notes on building Linux

Remember that the kernel and the rest of the operating system are two different things!  The kernel is the only thing you will need to build and/or modify in this class.

1. <strong>Download a copy of the free VM</strong> from Oracle called <q>Virtual Box</q> and install it.  Versions are available for both Windows [I used version 6.0.4-128413-Win.exe] and Mac [I used 6.0.0-127566-OSX.dmg], so you should be able to do this without regard to which platform you use.  There may be later versions available, and they should work.  I have found that when I started up the installed versions, I got a notification [on mac] that there is a later version available.  If that is the case for you, go ahead and install the later version &ndash; it won't corrupt anything you've done previously.  Virtual Box is available for free from: [this site](https://www.oracle.com/technetwork/server-storage/virtualbox/downloads/index.html)
1. <strong>Download a copy of Ubuntu Linux</strong> from the Ubuntu website.  I used version 18.10, which is the SECOND green button on the page.  The "LTS" button is for "Long Term Support" and the 18.10 version still has 9 months of support if you want it.  Ubuntu is available for free from: [here](https://www.ubuntu.com/download/desktop)
1. <strong>When you've downloaded it</strong> [it's an <q>iso</q> file] you need to make a new <q>machine</q>
                 on your Virtual Box VM.  Start up the VM, then click the <q>new</q> icon to make a new machine.  Call it
                 whatever you like [I used <q>ubuntuv1</q> so I can make more with successive numbers in case of a mistake].
                 Make sure you select the Linux install [which appears automatically if you name your VM instance with the word
                 ubuntu in it] and click next.  Reportedly you should use at least 4GB of RAM for this instance, so set the
                 slider accordingly, and click next.  You can take the defaults for the rest of the selections.</li>
1. <strong>Start the VM you just built</strong>, and us it to install Ubuntu.  There are a number of screens
                 that will be required on this first start up and install, but once you have it up and running, it will start
                 Linux automatically every time you start this particular VM instance.  DON'T WORRY about the prompt that
                 says something about <q>erasing your hard disk</q>&hellip; this is just erasing the VIRTUAL MACHINE'S HARD
                 DISK, not the real one on your computer.  Also, REMEMBER YOUR PASSWORD as this will be used to log in and
                 to do <q>sudo</q> tasks later.</li>
1. <strong>Start Ubuntu</strong>, if it isn't already started, and wait for it to load completely and display
                 the desktop.  Click on the little arrow in the upper right corner of the Ubuntu screen, then click the
                 tool icon.  Click the PRIVACY tab and turn screen lock off.  Then click the POWER tab and make sure power
                 saving is set to NEVER blank the screen.</li>
1. <strong>Check if GCC is loaded</strong>: open a terminal window in Ubuntu and run the command <q>gcc</g>
                 to check.  If it's not there, you can get it by doing <q>sudo apt install gcc</q> to get it.  When it is
                 finished, type <q>gcc</q> again to make sure it's working.  NOTE THAT THIS IS A DIFFERENT INSTANCE than the
                 one you installed on your HOST machine to do homework and exercises!</li>
1. <strong>Download the source code and build Linux</strong>: this sounds easier than it turns out to be.
                 There are a number of errors that will appear.  Some of them have fairly straightforward solutions, some of
                 them aren't as easy to find and implement fixes.  Here are some hints:
                 <ul><li>check out <a href='https://askubuntu.com/'>askubuntu.com</a> for help &ndash; this site can be your
                         best friend</li>
                     <li>check out <a href='https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel'>this page</a> for some help
                         and advice on the overall process of downloading the source and building the project; make sure you
                         build it BEFORE you modify it, to prove the build process works, THEN do your modification</a></li>
                     <li>note that building a NEW kernel takes several hours to compile; however, building the EXISTING
                         kernel only takes a few minutes, since you didn't change any code [yet].</li>
                     <li>run the build from the directory level ABOVE the <q>debian</q> directory in your home structure</li>
                     <li>you WILL do a lot of googling for this assignment, but there have been thousands of people who
                         have come before you and have solved these problems, so you CAN find an answer</li>
                     <li>the <q>sudo</q> command will give you a temporary access as if you were the root user;  you will
                         need the account password you set up when you installed Ubuntu on your VM</li>
                     <li>the <q>fakeroot</q> command is also very helpful, and sometimes you need to use them together to
                         get things to work.  I've had success with <q>sudo fakeroot</q> when the command didn't work for
                         either of them independently</li>
                     <li>run <q>sudo software-properties-gtk</q> to get a dialog box that has a check box which will enable
                         downloading the source code</li>
                     <li>run <q>sudo apt-get update</q> to update the <code>apt-get</code> utility</li>
                     <li>run <q>sudo vi /etc/apt/sources.list</q> to check the version of Ubuntu that will be built</li>
                     <li>run <q>sudo apt-get install dpkg-dev</q> to install the <code>dpkg-dev</code> package if it is
                         missing</li>
                     <li>run <q>sudo apt-get dist-upgrade</q> to upgrade the distribution manager utility; this will NOT
                         update the UBUNTU O/S, it will ONLY do the distribution manager</li>
                     <li>check out <a href='http://forns.lmu.build/classes/spring-2018/cmsi-387/homework/hw3/homework-3.html'>
                         Dr. Forney's homework 3 page</a> for more helpful information, including some fun XKCD comics; there
                         are also some helpful links and advice</li>
                     <li>Remember that the <q>frustration</q> is part of the <q>fun</q>&hellip;</li>
                 </ul></li>
1. <strong>Here is a list of things to do</strong> that helped my get my build completed:</br>
                 <blockquote>
                    <pre>
   LTS = "Long Term Service" ~ you don't really need, but is slightly more stable than non-LTS version
   the kernel is a <em>file</em> that is in directory "/boot".  The file is called <q>vmlinuz&lt;version&gt;"
   find the linux kernel archives at "www.kernel.org" and download the tarball for the
      version of interest.  I used 4.19.34 which is from April 5th 2019
   the "xz" extension is yet another type of "zip" archive compression.  The Linux "tar" program
      knows how to unzip it with the correct command line switch option "J" <note: uppercase!>
   start firefox
   go to www.kernel.org
   get kernel 4.19.34 tar ball &ndash; goes into Downloads folder when using FireFox
   use <code>mv</code> command to move the zipped file to your home directory
   untar with <code>tar xJvf linux-4.19.34.tar.xz</code>: the gibberish <q>xJvf</q> means:
      x to extract
      J because it's a zipped file with XZ format
      v for verbose so you can see the listings
      f for the file name which follows

   change into the resulting top level directory linux-4.19.34
   sudo apt install gcc
   sudo apt install make
      may get an error as follows:
         E: Could not get lock /var/lib/dpkg/lock – open (11: Resource temporarily unavailable)
         E: Unable to lock the administration directory (/var/lib/dpkg/), is another process using it?
      ps -eaf | grep -i apt  :: this shows running apt processes -- there is a daily check for updates
                                that locks apt -- you can kill them or you can just wait for them to finish
      You can use the <code>ps -eaf | grep -i apt</code> command to get the processes using the lock
      You can use the <code>kill -9 &lt;process ID&gt;</code> command to kill them off
   sudo apt-get install dpkg-dev
   sudo apt-get dist-upgrade
   make menuconfig to see options ~ make sure you SAVE so there is a config file for the build
   execute the command <code>make && make modules_install && make install</code> to run the build
      the "&&" means concatenate the commands, but only continues if the previous is successful
      You might have trouble with some of the required libraries being missing
      I had to get the ssl lib with
         sudo apt-get install libssl-dev
            the "-dev" makes sure to put the headers where they belong
      I had to get the ncurses lib with
         sudo apt install ncurses-dev
      I had to install bison with
         sudo apt-get install bison
      I had to install flex with
         sudo apt-get install flex

   then do the make line again:
      make && make modules_install && make install

   I did this on a VM that had 4096 RAM and 30 GB hard disk and ran out of space
   Tried again with 8192 RAM and 40 GB hard disk

   Started build at 08:43

   build failed at about 12:45 because I couldn't make a directory.
   switched to root account and tried again.  Just did "make" and that seemed to work
   then did "make module_install && make install"  and it skipped the compilation and went directly to "INSTALL"

   FIANLLY SUCCESS!!  I did a "uname -a" and saw the kernel version is my new 4.19 and the created date is today.

   ADDING A NEW SYSTEM CALL TO THE KERNEL
   ======================================

   In the directory where you put your source code; e.g., /home/beej/linux-4.19.34
   change to the directory arch/x86/entry/syscals
   find the file "syscall_64.tbl"  <or "syscall_32.tbl" if you are on a 32-bit machine>
   you can list it out with "more"
   there are <on my build> 547 entries in there
   edit the file using vi or vim
   add your new command to the end with a new number
   you will need to write the code for your addition first because you need the "entry point"
   the list of calls in the table will show you what you can modify if you are changing something
                    </pre>
                 </blockquote></li>
             <li><strong>Come up with an idea</strong> for a modification or addition to the Linux kernel, and get it
                 approved with the instructor.  This might be an addition to an existing command, a new command, or
                 an entirely new application that runs on Linux.</li>
             <li><strong>Design the modification</strong>; don't do this in the dark.  You might start by implementing some
                 version of your idea in a <q>stand-alone</q> way so that you can more easily build and de-bug it.  Doing
                 this on a prototype can be much faster than having to wait three hours for compilation each time
                 you re-build the Linux kernel</li>
             <li><strong>Here is a list of the Spring 2019 project teams</strong> with an idea of what needs to be modified
                 or implemented to accomplish the project tasks<br />
                 <ol><li>Chu, Edmiston, Keba: drive automounting ~ module[s]: mount</li>
                     <li>Crowther, Rajavasireddy, Simmons: user account creation ~ module[s]: useradd</li>
                     <li>Moini, Lizarda, Zafiris: "hog" system utility that lists CPU hogs ~ new module: hog</li>
                     <li>Santander, Namba, C. Nguyen: "mbob it" file name case randomizer utility ~ module[s]: "mv" and "ls" utilities</li>
                     <li>K. Nguyen, Ruiz, Tolliver: "processInfo" module interfaces to kernel log ~ new module: processInfo</li>
                     <li>Higgins, Fletcher, KPatterson: fun inefficient task scheduler ~ module[s]: sched.c</li>
                     <li>Lopez, Byrne, Boyac: new scheduling algorithm for the I/O scheduler ~ module[s]: sched.c</li>
                     <li>Prochnow, Flora, Jay: new output to "w" module ~ module[s]: [[unsure which is required]]</li>
                     <li>Ochsner, Peters, West: cursor movement without mouse ~ module[s]: mousedev, keydev</li>
                     <li>Braekman, Kern, Martin: combination utility, mimics "find" and "grep" in one ~ new module: search</li>
                     <li>Arteaga, Wroblewski, Persily: "top" utility modification for priorities ~ module[s]: top [[might get from http://procps.sourceforge.net/index.html]]</li>
                     <li>Patterson, Richardson: timedatectl modification ~ modules: set-time</li>
                 </ol></li>
             <li><strong>Some project resources</strong>: Consider using "apt-get source &lt;module_name&gt;" to get the source code
                         for specific commands or modules.  You might get them from
                         <a href='http://procps.sourceforge.net/index.html'>http://procps.sourceforge.net/index.html</a> or
                         possibly from <a href='http://lxr.linux.no/#linux+v4.15.14/kernel/sched.c#L3566'>
                         http://lxr.linux.no/#linux+v4.15.14/kernel/sched.c#L3566</a>.  Don't forget you may need to <q>sudo</q>
                         the apt-get command.</li>
 
