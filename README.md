![](https://img.shields.io/github/repo-size/JustAn0therDev/black-marlin) ![](https://img.shields.io/github/license/JustAn0therDev/black-marlin)

# Black Marlin: A light in-memory database as an alternative to Redis with a REST API interface for easy development and integration.
**Black Marlin** is an in-memory database for fast reading, writing and deleting cached data. Light, fast and easy to use with no need for third-party libraries.


## Why does it have a REST API interface?
The interface was created with easy development in mind, instead of having to use some sort of third-party library or framework; meaning its no different from making requests to a REST API in your program.

Any other program can cache its data without having to worry about its own available space in memory (if running on another host), maintaining connections or manually reading the output of other processes.
This also allows servers in an architecture that uses Load Balancing to share keys as they want with a fast, easy access to the same cache.


## Features:
- The main library is covered by unit tests with [catchv2](https://github.com/catchorg/Catch2);
- REST API interface for HTTP methods written on top of the main library with [cpp-httplib](https://github.com/yhirose/cpp-httplib);
- Integration tests are made to insure that every route is working as intended. This repository has a Postman collection with a really big JSON file you can use to test its performance;
- Allows custom response headers and port.

## Usage:
The program runs on port **7000** by default. You can test it by making a GET request to "http://127.0.0.1:7000/count" with your program running, for example. It should return `200 - OK` with `0` in the response body (assuming you didn't have any keys cached by Black Marlin prior to calling this route). The only thing you have to do to integrate it with your application is make HTTP requests and handle its responses.

--------------------------

### Configuring a custom port:
If you want Black Marlin to be available via a port of your choice, you can run the program from a CLI and pass in a number as an argument, like so:

`./blackmarlin 8534`

Note that if the port argument is an invalid value the program will not run and an error message will be written to STDOUT.

--------------------------

### How to set custom headers:

1. Create a file in the same directory as the program called `"bm_response_headers.txt"`;
2. Inside the file, put the headers as "key-values", separated by a single whitespace `" "`, like so: `Allow GET, POST, PUT, PATCH, DELETE`;
3. Run the program. The headers will be loaded only once in memory during startup and will return in the response **for every valid request**. Note that if the file is updated while the program is running the headers won't be updated. The program has to be restarted so it can load the contents of the file into memory again.

This allows for custom configurations such as cache control, specifying unusual HTTP methods etc. depending on your use-case.

If there is no file with the name mentioned above, there will be no additional custom headers in the response and this step will be ignored.

**If the file exists and does not have the exact configurations as mentioned above (key and value separated by one whitespace character and then next line for every response header), the program will not be able to run.**

--------------------------

### How to set HTTPS with an SSL certificate:

1. Create a file in the same directory as the program called `bm_cert_key_paths.txt`;
2. Inside the file, there should be two lines:
    1. The first line should contain the path to the certificate file (the path can be absolute or relative);
    2. The second line should contain the path to the private key.


Inside your file there should be two lines like these:

`path/to/cert/my_cert.crt`

`path/to/cert/my_private_key.key`

Thats all. When you run the program again, your calls to the URL should now contain `https`.

To disable this behavior just delete/remove the file mentioned and the server will use `http`.

--------------------------

### For each route and method:
**Any failed operation will return a `500 - Internal Server Error` HTTP status code**.


`"/"`:
- `GET` accepts a `key` query parameter: http://127.0.0.1:7000/?key=
	- **Call this to get the value of an existing key**. Returns: `400 - Bad Request` if no key is sent, `200 - OK` if a key was found and `204 - No Content` if a key was provided but not found.

- `POST` accepts a `key` query parameter (http://127.0.0.1:7000/?key=) and a **body**. The body can be sent in any format.
	- **Call this to create a new key value pair**. Returns `201 - Created` if the key value pair was created successfully.
	- It accepts another query parameter called `expiresin`. This parameter should be an integer representing an amount of seconds: http://127.0.0.1:7000/?key=key&expiresin=900.
	- **The `expiresin` parameter is optional**, meaning that if you want a key that does not expire unless manually deleted, all you have to do is omit the parameter.
	- Even if a key has been set to expire, **it can be deleted by calling the default route `/` with the `DELETE` method (or `/flush`) or have its value overwritten by the default route's `PUT` or `PATCH`**.
	- An already existing key cannot be set to expire.
	- The `expiresin` parameter must be a value bigger than 0 (zero) and less than or equal to `USHRT_MAX` (65535) and cannot be an invalid string such as `"abcd"`, otherwise it will return `400 - Bad Request`.
	- In summary, returns `400 - Bad Request` if:
		- No `key` parameter was sent;
		- No body was sent; or
		- The `expiresin` parameter was sent with an invalid value.

- `PUT and PATCH`: accepts a `key` query parameter (http://127.0.0.1:7000/?key=) and a **body**. The body can be sent in any format.
	- **Call this to update an existing key's value**. Returns: `400 - Bad Request` if no key or body was sent in the request and `200 - OK` if the key value pair was updated successfully.

- `DELETE` accepts a `key` query parameter: http://127.0.0.1:7000/?key=
	- **Call this to delete a key value pair**. Returns: `400 - Bad Request` if no key is sent and `200 - OK` if a key was provided. **Even if the hash table does not have the provided key, no specific HTTP Status Code will return**.

`"/count"`:
- `GET` takes no parameters: http://127.0.0.1:7000/count
	- **Call this to get the number of key value pairs in memory**. Returns: `200 - OK` if everthing went well. This number is a `size_t` value, so it can get as big as the max value of an `unsigned long long`.

`"/exists"`:
- `GET` accepts a `key` query parameter: http://127.0.0.1:7000/exists?key=
	- **Call this to check if a key exists**. Returns: `400 - Bad Request` if no key is sent, `200 - OK` if a key is found and `204 - No Content` if a key provided wasn't found.

`"/flush"`:
- `DELETE` takes no parameters: http://127.0.0.1:7000/flush
	- **Call this to erase all items in memory**. Returns: `200 - OK` if everything went well.

---------------------------

### Logs:
Everytime an error occurs it is written to a file called `bm_logs.txt` (it is created if it doesn't already exist in the same directory). Every log message will have the following format:

`{Year}-{Month}-{Day} {Hour}:{Minute}:{Second} - {ErrorMessage}`

---------------------------

### Current roadmap:
- Support for HTTP/2 calls.

---------------------------

### Sidenotes:
- This program does NOT officially support any other operating system except for Linux. If you try to run it on a Mac OS for example, the program will not run.
- **The first official release is available!**

---------------------------

## Contributions:

### General:
Feel free to open issues and fork as you feel like it. I'll be happy to help in any case.

### How to compile:
The program can be compiled in any way as long as it supports threads (expiring keys in the main library and `cpphttplib`), is targeting the C++17 standard and includes OpenSSL. The recommended way to compile the program is using CMake. It is already configured in the repo and can be done both on Windows and Linux.

### How to test:
`cd` to `unittests` directory and run the `run_unittests.sh` bash file. **Any other modules to be tested have to be added to the mentioned file**.

### Guidelines:
- Please follow the code's pattern; keeping the code looking the same everywhere in the program makes it easier to change stuff.
