CC = gcc
CFLAGS = -Wall -Werror -Wextra# -std=c90
EXEC = main
WORKDIR = src
OBJDIR = build

SOURCES = $(wildcard $(WORKDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))

all: $(EXEC)

$(EXEC): $(OBJDIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o $(EXEC)

$(OBJDIR)/%.o: $(WORKDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s ./$(EXEC)

$(OBJDIR):	
	mkdir $(OBJDIR)

rebuild: clean $(EXEC)

clean:
	rm -f *.o
	rm -f $(EXEC)
	rm -f *.db
	rm -rf $(OBJDIR)
