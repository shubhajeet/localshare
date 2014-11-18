NAME=glocalshare
CFLAGS=-g -Wall -ggdb -o $(NAME)
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-3.0`
SRCS=glocalshare.c
DEP=builder.ui
CC=gcc

# compiling the source file.
main: $(SRCS) $(DEP)
	$(CC) $(CFLAGS) $(SRCS) $(GTKFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	 /bin/rm -f $(NAME)
