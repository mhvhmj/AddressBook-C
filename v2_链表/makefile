Target ?= main
Objs ?= main.o mystring.o linklist.o
CC := gcc
Cflags := -c -o
Cflag := -o

$(Target):$(Objs)
	$(CC) $(Objs) $(Cflag) $(Target)
%.o:%.c
	$(CC) $< $(Cflags) $@
clean:
	rm $(Objs) $(Target)