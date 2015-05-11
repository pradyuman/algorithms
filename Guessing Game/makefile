make: functions.o guessingGame.o
	gcc functions.o guessingGame.o -o guessingGame
functions.o: functions.c
	gcc functions.c -c
guessingGame.o: guessingGame.c
	gcc guessingGame.c -c

clean:
	rm -f *.o guessingGame
