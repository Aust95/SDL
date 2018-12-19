CC := gcc
CFLAGS := -Wall -Wextra -ggdb -std=c99 -pedantic-errors -O3 -fsanitize=address -lSDL2 -I./src -I./src/sdl2 -lSDL2_image
# add header files here
HDRS :=
SRCS := main.c spcs_stuff.c render.c
# generate names of object files
OBJS := $(SRCS:.c=.o)
# name of executable
EXEC := cityg
# default recipe
all: $(EXEC)
# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)
