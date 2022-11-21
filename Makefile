CC=gcc
OBJS=functions.o questionInput.o main.o
EXEC=homework1
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@

functions.o: functions.c functions.h macros.h
main.o: main.c questionInput.h macros.h
questionInput.o: questionInput.c functions.h questionInput.h


clean: 
	rm -f $(EXEC) $(OBJS)
	
