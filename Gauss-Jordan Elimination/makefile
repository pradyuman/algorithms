make: functions.o main.o
	gcc functions.o main.o -o matrix
functions.o: functions.c
	gcc functions.c -c
main.o: main.c
	gcc main.c -c

clean:
	rm -f *.o matrix
