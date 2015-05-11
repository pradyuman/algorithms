make: functions.o fiblog.o
	gcc functions.o fiblog.o -o fibLog
functions.o: functions.c
	gcc functions.c -c
fiblog.o: fiblog.c
	gcc fiblog.c -c

clean:
	rm -f *.o fibLog
