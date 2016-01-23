mmn18 : main.o rb_tree.o
	gcc -g -ansi -Wall main.o rb_tree.o -pedantic -o mmn18

rb_tree.o : rb_tree.c rb_tree.h
	gcc -c -g -ansi rb_tree.c -Wall -pedantic -o rb_tree.o 

main.o : main.c rb_tree.h
	gcc -c  -g -ansi main.c -Wall -pedantic -o main.o 
