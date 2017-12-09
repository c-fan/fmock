CC = gcc

FMOCKDIR = ../..
FMOCKINC = $(FMOCKDIR)/include
FMOCKLIB = $(FMOCKDIR)/lib/fmock.a

CFLAGS += -I$(FMOCKINC) 
CFLAGS += -g -rdynamic

TARGET = mocktest

OBJS = user.o test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(FMOCKLIB)

$(OBJS) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

user.o: user.c todo.h user.h
test.o: test.c todo.h user.h

.PHONY: clean
clean:
	@echo clean up
	rm -f $(TARGET) $(OBJS)

