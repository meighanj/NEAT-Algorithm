DEL_FILE= rm -f
CFLAGS    = -lm -W -Wall

SOURCES   = operations.c  \
						propagation.c \
						gameboard.c

OBJECTS   =	operations.o  \
						propagation.o \
						gameboard.o   \
						main.o

TARGET    = exec

all: main

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

operations.o: operations.c
	$(CC) operations.c -c $(CFLAGS)

propagation.o: propagation.c
	$(CC) propagation.c -c $(CFLAGS)

gameboard.o: gameboard.c
	$(CC) gameboard.c -c $(CFLAGS)

clean: 
	-$(DEL_FILE) $(OBJECTS) $(TARGET) 

