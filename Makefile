CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c90
EXEC = main
WORKDIR = src
OBJDIR = obj

SOURCES = $(wildcard $(WORKDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))

run:
	@$(CC) test.c -lncurses
	@./a.out

$(EXEC): $(OBJDIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o $(EXEC)

$(OBJDIR)/%.o: $(WORKDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=yes ./$(EXEC)

$(OBJDIR):	
	mkdir $(OBJDIR)

clean:
	rm -rf *.o
	rm -rf $(EXEC)
	rm -rf $(OBJDIR)
