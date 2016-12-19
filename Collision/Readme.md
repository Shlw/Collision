# Project Collision

## Introduction

This is the project Collision, groupwork of the course Introduction to
Computing (A) (Honor Track) in the year of 2016. This project aims at 3-D
modeling, rendering and collision detection.

## Changelog and Note

* lzh @ 2016.12.18.22.34
  1. Update CMakeLists.txt for building under Mac OS X.

* Shlw @ 2016.12.19.20.13
  1. Generate two rather rougher divided models.
  2. Update model generator.

* Shlw @ 2016.12.19.19.36
  1. Replace >> in priority_queue with > >.

* lziad @ 2016.12.19.01.11
  1. Use a minimum heap to record sources.
  2. Use a queue to record the sounds which cannot be played on time.

* lzh @ 2016.12.18.21.17
  1. Revert the changes
  2. @ 2016.12.18.21.17 for some unknown issues
  disabling the display of box.

* lzh @ 2016.12.18.19.51
  1. Disable the ability to resize the window.
  2. Fix bugs about the depth when drawing box.

* lziad @ 2016.12.18.17.32
  1. Change faces when collision happens.

* lzh @ 2016.12.18.17.00
  1. Fix cmake configurations.
  
* lziad @ 2016.12.18.16.00
  1. Fix a bug causing memory leak when playing sounds.
  2. Volume can be adjusted using arrow keys.
  3. Fix the try-catch statement.

* Shlw @ 2016.12.18.15.57
  1. Fix Texture bugs.
  2. Update models.

* lziad @ 2016.12.18.11.38
  1. Change the logic of playing sound.
  2. Now main function will call *GameCleanUp*.

* lzh @ 2016.12.18.00.38
  1. Update CMakeLists.txt to compile with openal and alut under win-systems.

* Shlw @ 2016.12.17.20.48
  1. Add Ellipsoid model.
  2. Add Sphere model.

* Shlw @ 2016.12.17.20.00
  1. Decrease the angular speed.

* Shlw @ 2016.12.17.19.35
  1. Fix compile bugs in Linux.
  2. Correct some remaining conflicts.

* lziad @ 2016.12.17.15.55
  1. *alutLoadWAVFile* and *alutUnloadWAV* are substituted with *alutLoadMemoryFromFile*.
  2. Rewrite the singleton pattern.

* lziad @ 2016.12.17.02.16
  1. Add class *Audio* to load *.wav files.
  2. Add background music.
  3. Add sound effects when collision happens.
     (using *guichu* or *remix* materials)
  4. Finally main function has try-catch!

* lzh @ 2016.12.16.21.56
  1. Add lighting.

* lzh @ 2016.12.16.19.55
  1. Add true textures with *Baidu emojis*.

* Shlw @ 2016.12.16.16.16
  1. Reverse global.cpp.
  2. It turns out the new method is more time-consuming and less precise. QAQ
  3. Stupid Geometry...

* Shlw @ 2016.12.16.16.00
  1. Update Models and Textures.

* lzh @ 2016.12.16.14.47
  1. Add pictures.
  2. Add *GameInit* and a lot of functions about textures.

* Shlw @ 2016.12.16.13.35
  1. Add texture.

* Shlw @ 2016.12.15.17.35
  1. Re-write isinside.

* lzh @ 2016.12.14.20.15
  1. Fix memory leaks.
  2. Let *nModelList* begin from 0.

* Shlw @ 2016.12.14.17.40
  1. Adjust the density.

* ymw @ 2016.12.14.17.00
  1. Finished the collision update algorithm, not perfect, though.
  2. Adjusted the function *IsInside()*.

* lzh @ 2016.12.14.16.53
  1. Fix a lot of things including things about matrix transformations.

* lzh @ 2016.12.12.21.51
  1. Change vpSpeed to global coordinates from local coordinates.
  2. Update GameDrag to ensure the objects dragged are released in correct
  position.

* lziad @ 2016.12.12.16.55
  1. Rewrite the function GameDrag.
  2. Using global coordinates when updating positions.

* Shlw @ 2016.12.12.12.28
  1. Add Angular Momentum to Class Object.

* Shlw @ 2016.12.10.23.24
  1. Add Moment of Inertia(mat3).
  2. Update models.
  3. Make directory Models.

* lzh @ 2016.12.10.21.00
  1. Substitute cross, dot and length with the that in glm.
  2. Update drawing strategy to hide the black border of the box's frame.

* Shlw @ 2016.12.10.17.28
  1. Add MaxRadius.
  2. Update models.

* lziad @ 2016.12.10.16.44
  1. Update game logic.
  2. Add an exception flag.
  3. Add the header files on Apple OS X.

* lzh @ 2016.12.10.15.34
  1. Add the show box to indicate the absolute position.

* Shlw @ 2016.12.10.15.24
  1. Modify models.
  2. Add Ellipsoid.
  3. Rewrite model-generator.

* Shlw @ 2016.12.10.15.24
  1. Add nFlag.
  2. Modify models.

* Shlw @ 2016.12.10.15.00
  1. Re-write Readfile.

* Shlw @ 2016.12.10.14.38
  1. Add model-generator.
  2. Add sphere.
  3. Delete triangle-cone.

* lzh @ 2016.12.10.12.46
  1. Add a drag and drop demo.

* lzh @ 2016.12.10.11.41
  1. Add mouse events under glfw.
  2. Add function to handle drag and drop events.

* lzh @ 2016.12.10.11.02
  1. Update CMakeLists.txt on the dependent libraries.

* lzh @ 2016.12.10.10.06
  1. Substitute freeglut with glfw.

* Shlw @ 2016.12.10.00.10
  1. Partly re-write class
  2. Re-write Readfile
  3. Re-generate model.txt
  4. TIRANGLE-CONE IS INCORRECT, NEED TO BE CALCULATE AGAIN!!!

* lzh @ 2016.12.09.21.32
  1. Add *event.cpp* to handle mouse events, and now it is possible to use
  mouse to control the rotation of the model.
  2. Enable multi-sample, which, unfortunately cannot function properly on
  my computer. Please help check out weather the polygon drawn has been
  anti-aliased.
  3. Use freeglut instead of glut, which requires to substitute the *glut*
  library with *freeglut*.

* lzh @ 2016.12.09.14.31
  1. Substitute clock() with glutGet(GLUT_ELAPSED_TIME) to get time in the
  unit of milliseconds to enhance compatibility.
  2. Update configuration files.

* lzh @ 2016.12.08.13.08
  1. Change collision to Collision, which is caused by a typo when using
  git .

* lzh @ 2016.12.08.11.42
  1. Merge again.

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
