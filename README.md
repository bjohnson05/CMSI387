# CMSI387

## Notes on building Linux

Remember that the kernel and the rest of the operating system are two different things!  The kernel is the only thing you will need to build and/or modify in this class.

1. <strong>Download a copy of the free VM</strong> from Oracle called <q>Virtual Box</q> and install it.  Versions are available for both Windows [I used version 6.0.4-128413-Win.exe] and Mac [I used 6.0.0-127566-OSX.dmg], so you should be able to do this without regard to which platform you use.  There may be later versions available, and they should work.  I have found that when I started up the installed versions, I got a notification [on mac] that there is a later version available.  If that is the case for you, go ahead and install the later version &ndash; it won't corrupt anything you've done previously.  Virtual Box is available for free from: [this site](https://www.oracle.com/technetwork/server-storage/virtualbox/downloads/index.html)
1. <strong>Download a copy of Ubuntu Linux</strong> from the Ubuntu website.  I used version 18.10, which is the SECOND green button on the page.  The "LTS" button is for "Long Term Support" and the 18.10 version still has 9 months of support if you want it.  Ubuntu is available for free from: [here](https://www.ubuntu.com/download/desktop)
1. <strong>When you've downloaded it</strong> [it's an <q>iso</q> file] you need to make a new <q>machine</q> on your Virtual Box VM.  Start up the VM, then click the <q>new</q> icon to make a new machine.  Call it whatever you like [I used <q>ubuntuv1</q> so I can make more with successive numbers in case of a mistake].  Make sure you select the Linux install [which appears automatically if you name your VM instance with the word ubuntu in it] and click next.  Reportedly you should use at least 4GB of RAM for this instance, so set the slider accordingly, and click next.  You will also need to give yourself a 40GB hard drive to be able to successfully compile.  I tried it with 10, 20, and 30 GB drives and it failed on all of them.  You can take the defaults for the rest of the selections.
1. <strong>Start the VM you just built</strong>, and us it to install Ubuntu.  There are a number of screens that will be required on this first start up and install, but once you have it up and running, it will start Linux automatically every time you start this particular VM instance.  DON'T WORRY about the prompt that says something about <q>erasing your hard disk</q>&hellip; this is just erasing the VIRTUAL MACHINE'S HARD DISK, not the real one on your computer.  Also, REMEMBER YOUR PASSWORD as this will be used to log in and to do <q>sudo</q> tasks later.
1. <strong>Start Ubuntu</strong>, if it isn't already started, and wait for it to load completely and display the desktop.  Click on the little arrow in the upper right corner of the Ubuntu screen, then click the tool icon.  Click the PRIVACY tab and turn screen lock off.  Then click the POWER tab and make sure power saving is set to NEVER blank the screen.
1. <strong>Check if GCC is loaded</strong>: open a terminal window in Ubuntu and run the command <q>gcc</g> to check.  If it's not there, you can get it by doing <q>sudo apt install gcc</q> to get it.  When it is finished, type <q>gcc</q> again to make sure it's working.  NOTE THAT THIS IS A DIFFERENT INSTANCE than the one you installed on your HOST machine to do homework and exercises!
1. Check out [askubuntu.com](https://askubuntu.com/) for help &ndash; this site can be your best friend
1. Check out [the build your own kernel page](https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel) for some help and advice on the overall process of downloading the source and building the project; make sure you build it BEFORE you modify it, to prove the build process works, THEN do your modification
1. Note that building a NEW kernel takes several hours to compile; however, building the EXISTING kernel only takes a few minutes, since you didn't change any code [yet].
1. The <q>sudo</q> command will give you a temporary access as if you were the root user;  you will need the account password you set up when you installed Ubuntu on your VM
1. The <q>fakeroot</q> command is also very helpful, and sometimes you need to use them together to get things to work.  I've had success with <q>sudo fakeroot</q> when the command didn't work for either of them independently
1. Run <q>sudo software-properties-gtk</q> to get a dialog box that has a check box which will enable downloading the source code
1. Run <q>sudo apt-get update</q> to update the <code>apt-get</code> utility
1. Run <q>sudo apt-get install dpkg-dev</q> to install the <code>dpkg-dev</code> package if it is missing</li>
1. Run <q>sudo apt-get dist-upgrade</q> to upgrade the distribution manager utility; this will NOT update the UBUNTU O/S, it will ONLY do the distribution manager
1. Check out [Dr. Forney's homework 3 page](http://forns.lmu.build/classes/spring-2018/cmsi-387/homework/hw3/homework-3.html) for more helpful information, including some fun XKCD comics; there are also some helpful links and advice
1. Remember that the <q>frustration</q> is part of the <q>fun</q>&hellip;

## The Build Process that helped me the most with Linux

1. <strong>Here is a list of things to do and to know</strong> that helped my get my build completed:</br>
  1. LTS = "Long Term Service" ~ you don't really need, but is slightly more stable than non-LTS version
  1. The kernel is a <em>file</em> that is in directory "/boot".  The file is called <q>vmlinuz&lt;version&gt;"
  1. Find the linux kernel archives at "www.kernel.org" and download the tarball for the version of interest.  I used 4.19.34 which is from April 5th 2019
  1. The "xz" extension is yet another type of "zip" archive compression.  The Linux "tar" program knows how to unzip it with the correct command line switch option "J" <note: uppercase!>
  1. Start firefox and navigate to [www.kernel.org](www.kernel.org)
  1. Get kernel 4.19.34 tar ball &ndash; goes into Downloads folder when using FireFox
  1. Use the <code>mv</code> command to move the zipped file to your home directory
  1. Untar with <code>tar xJvf linux-4.19.34.tar.xz</code>: the gibberish <q>xJvf</q> means:
      * x to extract
      * J because it's a zipped file with XZ format
      * v for verbose so you can see the listings
      * f for the file name which follows
  1. Change into the resulting top level directory linux-4.19.34
  1. Do <q>sudo apt install gcc</q> to make sure that gcc is installed and updated
  1. Do <q>sudo apt install make</q> to make sure that the make utility is installed and updated
  1. During these operations you may get an error as follows:
         <strong>E: Could not get lock /var/lib/dpkg/lock – open (11: Resource temporarily unavailable)<br />
         E: Unable to lock the administration directory (/var/lib/dpkg/), is another process using it?</strong>
  1. Do <q>ps -eaf | grep -i apt</q>  :: this shows running apt processes ~~ there is a daily check for updates that locks apt ~~ you can kill the processes using <q>kill -9 &lt;process id&gt;, or you can just wait for them to finish, they don't take TOO long...
  1. You can use the <code>ps -eaf | grep -i apt</code> command to get the processes using the lock
  1. You can use the <code>kill -9 &lt;process ID&gt;</code> command to kill them off
  1. Do <q>sudo apt-get install dpkg-dev</q> to install the dpkg manager for the <em>development environment</em>
  1. Do <q>sudo apt-get dist-upgrade</q> to update the <code>apt-get</code> distribution
  1. Do <q>make menuconfig</q> to see options ~ <em>make sure you SAVE so there is a config file for the build</em>
  1. Execute the command <code>make && make modules_install && make install</code> to run the build<br />
      The <q>&&</q> means concatenate the commands, but only continues if the previous one is successful<br />
      You might have trouble with some of the required libraries being missing<br />
      I had to get the ssl lib with <q><code>sudo apt-get install libssl-dev</code></q><br />
      &nbsp;&nbsp;&nbsp;the <q>-dev</q> makes sure to put the headers where they belong<br />
      I had to get the ncurses lib with <q><code>sudo apt install ncurses-dev</code></q><br />
      I had to install bison with <q><code>sudo apt-get install bison</code></q><br />
      I had to install flex with <q><code>sudo apt-get install flex</code></q><br />

  1. Then I had to do the make line again:<br />
      <q><code>make && make modules_install && make install</code></q>
  1. I did this on a VM that had 4096 RAM and 30 GB hard disk and ran out of space; I tried again with 8192 RAM and 40 GB hard disk
  1. I started the build at 08:43; build failed at about 12:45 because I couldn't make a directory.
  1. I switched to root account and tried again.  Just did <q><code>make</code></q> and that seemed to work
  1. I then did <q><code>make module_install && make install</code></q> and make skipped the compilation and went directly to "INSTALL"
  1. Finished the build, then restarted Ubuntu
  1. <strong>FINALLY SUCCESS!!</strong>  I did a "uname -a" and saw the kernel version is my new 4.19 and the created date is today.


## Adding a New System Call to the Kernel
In the directory where you put your source code; e.g., /home/beej/linux-4.19.34<br />
   * NOTE: you will need to write the code for your addition first because you need the "entry point"<br />
   * change to the directory arch/x86/entry/syscals<br />
   * find the file "syscall_64.tbl"  [or "syscall_32.tbl" if you are on a 32-bit machine]<br />
   * you can list it out with <q>more</q><br />
   * there are [on my build] 547 entries in there<br />
   * edit the file using vi or vim<br />
   * add your new command to the end with a new number<br />
The list of calls in the table will show you what you can modify if you are changing something<br />

## Semester Project Actions and Deliverables
* <strong>Come up with an idea</strong> for a modification or addition to the Linux kernel, and get it approved with the instructor.  This might be an addition to an existing command, a new command, or an entirely new application that runs on Linux.
* <strong>Design the modification</strong>; don't do this in the dark.  You might start by implementing some version of your idea in a <q>stand-alone</q> way so that you can more easily build and de-bug it.  Doing this on a prototype can be much faster than having to wait three hours for compilation each time you re-build the Linux kernel
* <strong>Here is a list of the Spring 2019 project teams</strong> with an idea of what needs to be modified or implemented to accomplish the project tasks<br />
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
    <li>Arteaga, Wroblewski, Persily: "top" utility modification for priorities ~ module[s]: top [[might get from http://procps.sourceforge.net/index.html]](http://procps.sourceforge.net/index.html)</li>
    <li>Patterson, Richardson: timedatectl modification ~ modules: set-time</li>
</ol></li>
* <strong>Some project resources</strong>: Consider using "apt-get source &lt;module_name&gt;" to get the source code for specific commands or modules.  You might get them from [http://procps.sourceforge.net/index.html](http://procps.sourceforge.net/index.html) or possibly from [http://lxr.linux.no/#linux+v4.15.14/kernel/sched.c#L3566'](http://lxr.linux.no/#linux+v4.15.14/kernel/sched.c#L3566).  Don't forget you may need to <q>sudo</q> the apt-get command.
* note that not all of these are technically <q>kernel</q> modifications or addiitons.  However, in my view, if you are creating or modifying a <em>utility level</em> program, you will still be making use of the kernel system calls, and you will have had to build your own version of the kernel as part of the class, so it still counts for credit!

 
