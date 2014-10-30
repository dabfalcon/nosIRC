nos2014assignment
=================

Introduction
------------

For this assignment you will be applying both network and operating systems programming
techniques.

Your overall task is to implement a very simplified multi-threaded Internet Relay Chat (IRC) server.

I have provided you with a test program that you will use to track your progress and
guide your work.  I will use the same test program to assess your submissions, so you
can have good confidence prior to final submission as to the range in which your
assessment will be graded. 

I say range, because the technical component of this
assignment is worth 84%, with the remaining 16% being for style and readability of your
program. This will cover aspects such as a comprehendable architecture (which will of
course help you as you write it anyway), appropriate comments, clarity, brevity, and
use of efficient and appropriate algorithms and techniques.

Comments should address
why the code it documents is necessary, i.e., what would go wrong if it wasn't there,
rather than what the code does -- after all, anyone can read the code to see what it
does, but understanding WHY it is there is not so trivial.
  
In other words, to get an
HD your program must be both machine and human readable. 

Recommended approach
--------------------

I recommend that you start with the mostly empty sample.c that I provide, and use
this as the basis for your program.  Compile and run this through the test program,
with something like:

make && ./test ./sample

And pay attention to what it outputs.  The FAIL messages will tell you the next thing
that doesn't work in your program.  Fix that, then move on to the next one.  If any are
too hard, then skip them and work on another.

I have supplied you with the source code for the test program, and you are welcome to look
at that to get a better idea of what is being tested.  You can also use it as a reference
for many of the network programming tasks you will need.  IF YOU USE ANY OF THE TEST PROGRAM
IN YOUR OWN you must copy the copyright notice from the top of the file, adjust it appropriately
to include your name in the copyright list.  FAILURE TO ATTRIBUTE CODE DRAWN FROM TEST.C WILL
RESULT IN 0, and will be treated as any other form of academic misconduct.  Ask me if you
are unsure with how to comply with this requirement.

Recommended programming environment
-----------------------------------

You should do your software development using the CSEM UNIX systems.  YOu can install PUTTY.EXE
on Windows to log in remotely from home, or you can login in the lab.  ALL SUPPORT MATERIALS ARE
BASED ON DEVELOPING YOUR SOFTWARE THIS WAY.  Every year a few students ignore this advice and
try to use some Windows-based software development environment, and it almost invariably leads
to more hurt and pain, especially when they submit their solution only to find that IT DOESN'T
WORK ON THE UNIX SYSTEMS, WHICH IS WHERE I WILL BE MARKING, AND THEY GET ZERO.

The workflow for software development is to edit your source files using any normal UNIX text
editor, e.g., pico, emacs or vi, and then compile and test the programme using the commands I
described above.

EDITING THE SOURCE FILES USING MICROSOFT WINDOWS BASED EDITORS IS A RECIPE FOR PAIN AND
SUFFERING because they put the wrong end-of-line markers in the files, which can create all
sorts of subtle (and not so subtle) problems.

If you have a Mac, it is relatively safe to develop locally on that using Aquamacs as the editor
and to compile your program (press escape then x, then type the word compile and hit enter, and
it will compile in emacs, and you will be able to click on errors to jump to the relevant lines
of source code) and using Terminal to run the program.  The same applies to Linux, FreeBSD and
probably to other UNIX-based environments.  HOWEVER ALWAYS TEST ON THE CSEM UNIX SYSTEMS BEFORE
SUBMITTING TO AVOID UNPLEASANT SURPRISES, LIKE GETTING ZERO IF YOUR PROGRAM DOESN'T WORK ON THERE.

You are allowed to program in a language other than C if you wish, provided that you still use
similar networking and concurrency primitives, and that your submission still works when run
with the test program on the CSEM UNIX environment.  I recommend against using Java, since 
that will rob you of the opportunity to learn basic C programming, which you will need if you
go on to SE3 next year in any case.

Useful resources about IRC
--------------------------

http://en.wikipedia.org/wiki/Internet_Relay_Chat

Parsing IRC commands and example IRC sessions:

http://calebdelnay.com/blog/2010/11/parsing-the-irc-message-format-as-a-client
http://www.anta.net/misc/telnet-troubleshooting/irc.shtml

The complete RFC for IRC (which is way more detailed than you need, but may prove
helpful):

http://tools.ietf.org/html/rfc2812

Useful resources for the operating systems programming aspects
--------------------------------------------------------------

pthreads functions:

http://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html

You will need pthread_create(), pthread_exit() and the pthread_rwlock functions.

http://cursuri.cs.pub.ro/~apc/2003/resources/pthreads/uguide/users-86.htm
http://www.amparo.net/ce155/thread-ex.html

Useful resources for the network programming apsects
----------------------------------------------------

https://www.google.com.au/search?q=C+programming+tutorial&oq=C+programming+tutorial

General C programming
---------------------

https://www.google.com.au/search?q=C+programming+tutorial&oq=C+programming+tutorial
