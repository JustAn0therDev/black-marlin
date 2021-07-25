![](https://img.shields.io/github/repo-size/JustAn0therDev/black-marlin) ![](https://img.shields.io/github/license/JustAn0therDev/black-marlin) ![](https://img.shields.io/github/downloads/JustAn0therDev/black-marlin/total)

# Black Marlin: A light in-memory database as an alternative to Redis with a REST API interface for easy development and integration.
**Black Marlin** is an in-memory database for fast reading, writing and deleting cached data. Light, fast and easy to use with no need for third-party libraries.


## Why does it have a REST API interface?
The interface was created with easy development in mind, instead of having to use some sort of third-party library or framework; meaning its no different from making requests to a REST API in your program.

Any other program can cache its data without having to worry about its own available space in memory (if running on another host), maintaining connections or manually reading the output of other processes.
This also allows servers in an architecture that uses Load Balancing to share keys as they want with a fast, easy access to the same cache.


## Features:
- Uses a `std::unordered_map` with a key `std::string` and a `std::string*` value. Long story short, its a hash table that allows fast lookup time (O(1) for keys and worst case O(N) for values, N being the size of a bucket);
- The code is covered by unit tests with [catchv2](https://github.com/catchorg/Catch2);
- REST API interface for HTTP methods written on top of the main library. Meaning this is a **raw web server using the awesome [cpp-httplib](https://github.com/yhirose/cpp-httplib)**;
- Integration tests validating every possible response and request with Postman;
- Performance profiling and memory leak checks are made with VS Diagnostic Tools and Valgrind;
- Allows **custom response headers** configured in a file called `"bm_response_headers.txt"`;
- Compatible with both Windows and Linux, having different versions for each (`.exe` and `.file`, respectively). Both are available in the releases tab.

## Usage:
The program runs on port **7000** by default. You can access it by making a GET request to http://127.0.0.1:7000/count with your program running, for example.
The only thing you have to do to integrate with your application is make the HTTP requests and handle the responses.

--------------------------
### Configuring a custom port:
If you want Black Marlin to be available in a port of your choice, you can run the program from your favorite CLI and pass in a number as an argument, like so:

For Linux:
`./black_marlin.file 8534`

For Windows:
`./black_marlin.exe 8534`

Note that if the port argument given contains something that is not a number (or is an invalid port value) the program will not run.

--------------------------

### How to set custom headers:

1. Create a file in the same directory as the program called `"bm_response_headers.txt"`;
2. Inside the file, put the headers as key values, separated by a single whitespace `" "`, like so: `Allow GET,POST,PUT,PATCH,DELETE`;
3. Run the program. The headers will be loaded only once in memory during startup and will return in the response **for every valid request**. Note that if the file is updated while the program is running the headers won't be updated. The program has to be restarted so it can load the contents of the file into memory again.

This allows for some special types of configurations such as cache control, specifying unusual HTTP methods etc.

--------------------------
### For each route and method:
**Any failed operation will return a `500 - Internal Server Error` HTTP status code**.


`"/"`:
- `GET` accepts a `key` query parameter: http://127.0.0.1:7000/?key=
	- Returns: `400 - Bad Request` if no key is sent, `200 - OK` if a key is found and `204 - No Content` if a key is provided but wasn't found.

- `POST` accepts a `key` query parameter (http://127.0.0.1:7000/?key=) and a **body**. The body can be sent in any format.
	- It accepts another query parameter called `expiresin`. This parameter should be an integer representing an amount of seconds: http://127.0.0.1:7000/?key=key&expiresin=900.
	- **The `expiresin` parameter is optional**, meaning that if you want a key that does not expire unless manually deleted, all you have to do is omit it.
	- Even if a key has been set to expire, **it can be deleted by calling the default route's `DELETE` method (or `/flush`) or have its value overwritten by the default route's `PUT` or `PATCH`**.
	- An already existing key cannot be set to expire.
	- The `expiresin` parameter must be a value bigger than 0 (zero) and less than or equal to `USHRT_MAX` (65535) and cannot be an invalid string such as `"abcd"`, otherwise a `400 - Bad Request` will return.
	- In summary, returns `400 - Bad Request` if:
		- No `key` parameter was sent;
		- No body was sent; or
		- The `expiresin` parameter was sent with an invalid value.
	- Returns `201 - Created` if the key-value pair was created successfully.

- `PUT and PATCH`: accepts a `key` query parameter (http://127.0.0.1:7000/?key=) and a **body**. The body can be sent in any format.
	- Returns: `400 - Bad Request` if no key or body was sent in the request and `200 - OK` if the key-value pair was updated successfully.

- `DELETE` accepts a `key` query parameter: http://127.0.0.1:7000/?key=
	- Returns: `400 - Bad Request` if no key is sent and `200 - OK` if a key was provided. **Even if the hash table does not have the provided key, no specific HTTP Status Code will return**.

`"/count"`:
- `GET` takes no parameters: http://127.0.0.1:7000/count
	- Returns: `200 - OK` with a body containing a single number. This number is a `size_t` value, so it can get as big as the max value of an `unsigned long long`.

`"/exists"`:
- `GET` accepts a `key` query parameter: http://127.0.0.1:7000/exists?key=
	- Returns: `400 - Bad Request` if no key is sent, `200 - OK` if a key is found and `204 - No Content` if a key provided wasn't found.

`"/flush"`:
- `DELETE` takes no parameters: http://127.0.0.1:7000/flush
	- Returns: `200 - OK` if everything went well.

---------------------------
## Current roadmap:
- Logging to file. Any exception or information that should be logged is currently being written to `STDOUT`;
- Support for HTTPS and IPv6 (now natively supported by `cpphttplib`).
---------------------------
## Sidenotes:
- **The pre-releases are available for testing**;
- Currently, this application is not intended to have any sort of manual security implementation like token validations, so it should run inside your organization/project's infraestructure. This decision was made to avoid **any** kind of overhead resulted from manually checking tokens in every request, for example.

---------------------------
## Contributions:

### General:
Feel free to open issues and fork as you feel like it. I'll be happy to help in any case.

### How to compile:
To compile the program on Windows, use Visual Studio (2015, 2017 or 2019) and build the program from the `CMakeLists.txt` file in the root directory of the repository.

To compile the program on Linux, do as you please as long as the compiler supports the C++17 standard and threads, since the main library and `cpphttplib` make use of threads. Optionally to compile directly with G++, run the `compile_linux_version_with_gcc.sh` file in the repository's root.

### Operating systems:
Since there are some specific things in Windows and POSIX, there are some files inside the repo that are only compiled for Windows versions and vice-versa. They are pretty
obvious and can be found in the `.sh` scripts.

### How to test:
`cd` to `unittests` directory and run `run_unittests.sh` (or `run_unittests_linux.sh` depending on your operating system). **Any other files that should be tested by the unit tests have to be added to the script.**

### Guidelines:
- Any files that are not required to compile the program and/or are not part of the usage at all, **should not be included in the version control system. This will be reviewed in any pull request**;
- Please follow the code's pattern; keeping the code looking the same everywhere in the program makes it easier to change stuff.
