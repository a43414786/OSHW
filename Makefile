all:
	git pull
	cp hw3/function_libary.c ~/hw3/function_libary.c
	cp hw3/function_libary.h ~/hw3/function_libary.h
	cp hw3/os2021_thread_api.c ~/hw3/os2021_thread_api.c
	cp hw3/os2021_thread_api.h ~/hw3/os2021_thread_api.h
	cp hw3/simulator.c ~/hw3/simulator.c
	cp hw3/init_threads.json ~/hw3/init_threads.json
push:
	git add .
	git commit . -m 'k'
	git push
t:
	git pull
	gcc -o t hw3/simulator.c hw3/os2021_thread_api.c
	./t
