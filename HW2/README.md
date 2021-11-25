# HW2 Simple Key-value Store

## Directories
- /server ->	server program related sources
- /client ->	client program related sources
- /common ->	common inclusions
- /util ->	common utilization
- /build ->	target build directory

## Building the Project
Code out your `/server/server.c` and `/client/client.c`, then
```shell
$ make
```
Test your `/build/server` and `build/client`.

## Implementations
### Please briefly describe your multi-threading design pattern
Use a while loop ,in each loop , allocate a new fd and wait for accept , when accept , create a thread and call service function , then detach the thread so server will not need to wait for thread terminate and thread can free automatically when all the task for thread is all done , in the service functino , server receive command and key(and value if command is SET) and do SET/GET/DELETE command use set()/get()/delete() in my program, while do these functions lock before do functions and unlock after functions are done then send return value from functions , then free fd and terminate the thread 
### Please briefly describe your data structure implementation
Construct a database with an array which contain 23 pointers , use strlen() to get key length and mod 23 to get index of database say i , then use ith element of database , which is the first node of a list to implement SET/GET/DELETE   

## References
* [POSIX thread man pages](https://man7.org/linux/man-pages/man7/pthreads.7.html)
* [socket man pages](https://linux.die.net/man/7/socket)

