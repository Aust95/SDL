# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := -Wall -Wextra -ggdb -std=c99 -pedantic-errors -O3 -fsanitize=address -lSDL2 -I./src -I./src/sdl2 -lSDL2_image

# add header files here
HDRS :=

# add source files here
SRCS := win1rf.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := sdle

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
