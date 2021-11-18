CC = g++
CFLAGS = -Wall -g
#CFLAGS = -Wall


schedule: main.o Scheduler.o RTScheduler.o InputManager.o Process.o Average.o
	$(CC) $(CFLAGS) -o schedule main.o Scheduler.o RTScheduler.o InputManager.o Process.o Average.o

main.o: Scheduler.h RTScheduler.h InputManager.h Process.h
	$(CC) $(CFLAGS) -c main.cpp

Scheduler.o: Scheduler.cpp Scheduler.h Average.h Process.h Queue.h
	$(CC) $(CFLAGS) -c Scheduler.cpp

RTScheduler.o: RTScheduler.cpp RTScheduler.h Average.h Process.h
	$(CC) $(CFLAGS) -c RTScheduler.cpp

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