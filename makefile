CC = g++
CFLAGS = -wall -g

schedule: main.o Scheduler.o InputManager.o Process.o Average.0
	$(CC) $(CFLAGS) -o schedule main.o Scheduler.o InputManger.o Process.o Average.o

main.o: Scheduler.h InputManager.h Process.h
	$(CC) $(CFLAGS) -c main.cpp

Scheduler.o: Scheduler.cpp Scheduler.h Average.h Process.h
	$(CC) $(CFLAGS) -c Scheduler.cpp

Average.o: Average.cpp Average.h Process.h
	$(CC) $(CFLAGS) -c Average.cpp

InputManager.o: InputManager.cpp InputManager.h Process.h
	$(CC) $(CFLAGS) -c InputManager.cpp

Process.o: Process.cpp Process.h
	$(CC) $(CFLAGS) -c Process.cpp

clean:
	rm -f *.o
	rm -f *.out
	rm -f *.gch
	rm -f *~
	rm -f schedule