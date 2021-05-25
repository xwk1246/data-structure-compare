all:  main.o datagenerator.o array.o bst.o hash.o linkedlist.o
	gcc main.o datagenerator.o array.o bst.o hash.o linkedlist.o -o main
main.o: main.c
	gcc -c main.c -o main.o
datagenerator.o: datagenerator.c datagenerator.h
	gcc -c datagenerator.c -o datagenerator.o	
array.o: array.c array.h
	gcc -c array.c -o array.o
bst.o: bst.c bst.h
	gcc -c bst.c -o bst.o
hash.o: hash.c hash.h
	gcc -c hash.c -o hash.o
linkedlist.o: linkedlist.c linkedlist.h
	gcc -c linkedlist.c -o linkedlist.o
clean:
	rm -r -f *.o *.txt