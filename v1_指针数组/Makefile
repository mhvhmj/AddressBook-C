Target ?= main
Objs ?= main.o function.o mystring.o
CC := gcc
CFLAGS := -c -o
CFLAG := -o

$(Target):$(Objs)
	$(CC) $(Objs) $(CFLAG) $(Target)
%.o:%.c
	$(CC) $< $(CFLAGS) $@
clean:
	rm $(Objs) $(Target)
