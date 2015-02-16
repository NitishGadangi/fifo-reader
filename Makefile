##Thu Aug 21 14:33:52 CDT 2014 ##

EXEC := fifo-reader

objects := fifo-reader.o
objects +=

CFLAGS := -g
CFLAGS += -Wall
CFLAGS += -pthread
CFLAGS += -std=c99
CFLAGS += -I./include

CC := arm-linux-gnueabihf-gcc

vpath %.c src

$(EXEC) : $(objects)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY : clean
clean :
	rm -f $(EXEC) $(objects)
