make: tree.o list.o functions.o main.o
	gcc tree.o list.o functions.o main.o -o huffman
tree.o: tree.c
	gcc tree.c -c
list.o: list.c
	gcc list.c -c
functions.o: functions.c
	gcc functions.c -c
main.o: main.c
	gcc main.c -c

clean:
	rm -f *.o core
