
GIT_HOOKS := .git/hooks/applied
CC := gcc
CFLAGS += -std=gnu99 -g -Wall

all: $(GIT_HOOKS) 

$(GIT_HOOKS):
	@.githooks/install-git-hooks
	@echo

simulator:simulator.o os2021_thread_api.o function_libary.o
	$(CC) $(CFLAGS) -o simulator simulator.o os2021_thread_api.o function_libary.o

simulator.o:simulator.c os2021_thread_api.h
	$(CC) $(CFLAGS) -c simulator.c

os2021_thread_api.o:os2021_thread_api.c os2021_thread_api.h function_libary.h
	$(CC) $(CFLAGS) -c os2021_thread_api.c

function_libary.o: function_libary.c function_libary.h
	$(CC) $(CFLAGS) -c function_libary.c

.PHONY: clean
clean:
	rm *.o
test:
	git pull
	gcc -o t simulator.c os2021_thread_api.c function_libary.c
check:
	cppcheck function_libary.c
	cppcheck function_libary.h
	cppcheck os2021_thread_api.c
	cppcheck os2021_thread_api.h
	cppcheck simulator.c
	cppcheck init_threads.json	
	astyle --style=bsd --indent=spaces=4 --suffix=none function_libary.c
	astyle --style=bsd --indent=spaces=4 --suffix=none function_libary.h
	astyle --style=bsd --indent=spaces=4 --suffix=none os2021_thread_api.c
	astyle --style=bsd --indent=spaces=4 --suffix=none os2021_thread_api.h
	astyle --style=bsd --indent=spaces=4 --suffix=none simulator.c
	astyle --style=bsd --indent=spaces=4 --suffix=none init_threads.json	
move:
	cp function_libary.c ~/hw3/function_libary.c
	cp function_libary.h ~/hw3/function_libary.h
	cp os2021_thread_api.c ~/hw3/os2021_thread_api.c
	cp os2021_thread_api.h ~/hw3/os2021_thread_api.h
	cp simulator.c ~/hw3/simulator.c
	cp init_threads.json ~/hw3/init_threads.json
	