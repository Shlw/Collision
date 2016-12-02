# Project Collision

## Introduction

This is the project Collision, groupwork of the course Introduction to
Computing (A) (Honor Track) in the year of 2016. This project aims at 3-D
modeling, rendering and collision detection.

## Changelog

* lzh @ 2016.12.02.20.10
  1. Fix link flags *-static* in CMakeLists.txt for static linking.

* lzh @ 2016.12.02.14.53
  1. Fix unrecognized suffices under XCode with LLVM.

* lzh @ 2016.12.02.10.18
  1. Use CLOCKS_PER_SEC to enhance compatibility.
  2. Update UNIX arguments in CMakelists.txt.

* lzh @ 2016.12.01.14.44
  1. Add commentary to each files.

* lzh @ 2016.12.01.13.27
  1. Substitute *Sleep* with *glutTimerFunc* to solve compatibility
  issues.

* lzh @ 2016.12.01.11.17
  1. Rewrite *Readme.md* in English in order to enhance compatibility and
  to practise English for the approaching CET-4 test.

* lzh @ 2016.12.01.00.46
  1. Create the basic framework consisting of four parts including
  *display*, *draw*, *update*, *game*, which is exactly the rendering,
  modeling, collision detection and application part of the project
  correspondingly.
  2. Use Cmake to ensure Cross-platform Compile compatibility.

## TodoList and Remarks

* lzh @ 2016.12.02.20.10
  1. None.

* lzh @ 2016.12.02.14.53
  1. None.

* lzh @ 2016.12.02.10.18
  1. Contact lzh if CMakelists.txt doesn't work in UNIX.

* lzh @ 2016.12.01.14.44
  1. Feel free to correct typos in the *Readme.md* and the source files.

* lzh @ 2016.12.01.13.27
  1. None.

* lzh @ 2016.12.01.11.17
  1. Please help to correct typos in *Readme.md*, which accounts for my
  poor English.

* lzh @ 2016.12.01.00.46
  1. The compile argument for UNIX in CMakelists.txt need updating.
  Therefore, attempt to use Cmake to generate Makefile in Unix leads to
  fatal errors. An alternative is to compile in command-line by hand,
  which needs to compile *main.cpp*, *display.cpp*, *draw.cpp*,
  *update.cpp* and *game.cpp* with the libraries *glut* (or *freeglut*)
  and *glm*. Additionally, I suggest thost who want to compile the project
  in UNIX contact lzh in time to update the arguments.
  2. The classes Object and Model in global.hpp use stupid and clumsy
  declarations, especially forcing all the members to be *public*, which
  should be overriden in time.
  3. *display.cpp* contains a naive demo, which is to be overriden
  eventually.
  4. It is **strongly recommended** to log your change and remarks in the
  file *Readme.md*. The grammar of *.md* files is quite easy and
  tutorials can be easily found on the Internet.
