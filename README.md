## Black Marlin: An in-memory, HTTP Web Server database based on Redis. Made using C++.
Black Marlin is an in-memory database made for fast **read/write caching**. It will have an interface for communication with HTTP methods for easier use in Web architectures with requests and responses. No plans for web sockets implementation.

### FEATURES:
- Unit testing code coverage;
- HTTP Web Server implementation for HTTP methods and usage by any other machine as a client (in development);
- Integration tests (coming soon);
- Use of C++ optimization and constant checking for memory leaks.

### SIDENOTE:
- If you want a lot of memory space to "tinker with", do NOT run it in a device that has limited or close to no memory. Keep in mind that this application does not have a system for compression and decompression of information that comes and goes. **Space usage optimization is not the main concern of this application**, but reading/writing as fast as possible.
