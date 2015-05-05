make: bmp.o main.o
	gcc bmp.o main.o -o bmp
bmp.o: bmp.c
	gcc bmp.c -c
main.o: main.c
	gcc main.c -c

clean:
	rm -f *.o bmp
