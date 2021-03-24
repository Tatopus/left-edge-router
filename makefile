all:main.o
	gcc -c graph.c -o graph.o
	gcc -c queue.c -o queue.o
	gcc -c main.c -o main.o
	gcc main.o graph.o queue.o -o leftedge_router
