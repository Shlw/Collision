# Project Collision

## Introduction

This is the project Collision, groupwork of the course Introduction to
Computing (A) (Honor Track) in the year of 2016. This project aims at 3-D
modeling, rendering and collision detection.

## Changelog and Note

* lzh @ 2016.12.08.01.31
  1. I'm sorry to ignore some changes before I start working and I have
  already merged those additional commentaries in now.

* lzh @ 2016.12.08.00.52
  1. Modify classes and merge changes.
  2. Create a naive demo using the new classes.
  3. Create Configure files, executing which in shell can help configure
  Makefile and CMakeLists.txt.
  4. Contact me if Configure doesn't work.
  5. Modify *Readme.md*.

* Shlw @ 2016.12.06.16.11
  1. Re-write the draw.cpp, display.cpp, game.cpp, update.cpp.
  2. Implement moment-of-inertia formula.
  3. Re-write the draw.cpp, display.cpp, game.cpp, update.cpp.
  4. Implement moment-of-inertia formula.

* Shlw @ 2016.12.04.23.40
  1. Create Point, Triangle Class.
  2. Create global.cpp & function v4Cross.
  3. Add Linux makefile & Executable File-run.
  4. Rewrite Class Model&Object.
  5. Add Function is_inside. 

* lzh @ 2016.12.01.22.13
  1. Fix bug about CLOKS_PER_SEC.
  2. Enable blend and anti-alias in *display*.
  3. Add *Modifier* entry in commentary of each file.

* lzh @ 2016.12.02.20.10
  1. Fix link flags *-static* in CMakeLists.txt for static linking.

* lzh @ 2016.12.02.14.53
  1. Fix unrecognized suffices under XCode with LLVM.

* lzh @ 2016.12.02.10.18
  1. Use CLOCKS_PER_SEC to enhance compatibility.
  2. Update UNIX arguments in CMakelists.txt.
  3. Contact lzh if CMakelists.txt doesn't work in UNIX.

* lzh @ 2016.12.01.14.44
  1. Add commentary to each files.
  2. Feel free to correct typos in the *Readme.md* and the source files.

* lzh @ 2016.12.01.13.27
  1. Substitute *Sleep* with *glutTimerFunc* to solve compatibility
  issues.

* lzh @ 2016.12.01.11.17
  1. Rewrite *Readme.md* in English in order to enhance compatibility and
  to practise English for the approaching CET-4 test.
  2. Please help to correct typos in *Readme.md*, which accounts for my
  poor English.

* lzh @ 2016.12.01.00.46
  1. Create the basic framework consisting of four parts including
  *display*, *draw*, *update*, *game*, which is exactly the rendering,
  modeling, collision detection and application part of the project
  correspondingly.
  2. Use Cmake to ensure Cross-platform Compile compatibility.
  3. The compile argument for UNIX in CMakelists.txt need updating.
  Therefore, attempt to use Cmake to generate Makefile in Unix leads to
  fatal errors. An alternative is to compile in command-line by hand,
  which needs to compile *main.cpp*, *display.cpp*, *draw.cpp*,
  *update.cpp* and *game.cpp* with the libraries *glut* (or *freeglut*)
  and *glm*. Additionally, I suggest thost who want to compile the project
  in UNIX contact lzh in time to update the arguments.
  4. The classes Object and Model in global.hpp use stupid and clumsy
  declarations, especially forcing all the members to be *public*, which
  should be overriden in time.
  5. *display.cpp* contains a naive demo, which is to be overriden
  eventually.
  6. It is **strongly recommended** to log your change and remarks in the
  file *Readme.md*. The grammar of *.md* files is quite easy and
  tutorials can be easily found on the Internet.
