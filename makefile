CC = g++
CFLAGS = -wall -g

schedule: main.o Scheduler.o InputManager.o Process.o
	$(CC) $(CFLAGS) -o schedule main.o Scheduler.o InputManger.o Process.o

main.o: Scheduler.h InputManager.h Process.h
	$(CC) $(CFLAGS) -c main.cpp

Scheduler.o: Scheduler.cpp Scheduler.h Process.h
	$(CC) $(CFLAGS) -c Scheduler.cpp

InputManager.o: InputManager.cpp InputManager.h Process.h
	$(CC) $(CFLAGS) -c InputManager.cpp

Process.o: Process.cpp Process.h
	$(CC) $(CFLAGS) -c Process.cpp

clean:
	rm -f *.o
	rm -f *~
	rm -f schedule