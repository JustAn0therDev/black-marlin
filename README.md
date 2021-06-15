## Black Marlin: An in-memory database based on Redis. Made using C++.
TODO: CHANGE EVERYTHING IN THIS README TO A WEB HTTP SERVER FOR READ/WRITE THINGS IN MEMORY.
Black Marlin is an in-memory database made for fast **read/write caching**.


### CURRENT ROADMAP:
- Support for multiple clients having access to the same memory location, being able to read, overwrite and delete the same keys written by other processes;
- I don't know how it deals with UTF-8/UTF-16 bytes/strings, so it will be tested in the near future along with the library and new, updated versions will be released.


### SIDENOTES:
- If you want a lot of memory space to "tinker with", do NOT run it in a device that has limited or close to no memory. Keep in mind that this application does not have a system for compression and decompression of information and comes and goes. Memory space usage optimization is not the main concern of this application;


The current state of this application is **reasonable for cross-platform (Windows and Unix) production use. If you or your team/organization have found problems with the application, please open up an issue so I can look into it**.
