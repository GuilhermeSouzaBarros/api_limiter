COMPILER = gcc
FLAGS = -Wall -Wextra -g
BINARYDIR = binary
EXENAME = rate_limiter

SRCS = $(filter-out main.c, $(wildcard *.c))
OBJS = $(SRCS:%.c=$(BINARYDIR)/%.o)

.PHONY: all clean

all: $(BINARYDIR) $(EXENAME)

$(EXENAME): $(OBJS) $(BINARYDIR)/main.o
	$(COMPILER) $(FLAGS) $^ -o $@

$(BINARYDIR)/%.o: %.c %.h
	$(COMPILER) $(FLAGS) -c $< -o $@

$(BINARYDIR)/main.o: main.c
	$(COMPILER) $(FLAGS) -c $< -o $@

$(BINARYDIR): 
	test ! -d $(BINARYDIR) && mkdir $(BINARYDIR)

run:
	./$(EXENAME)

clean:	
	rm -rf $(BINARYDIR) $(EXENAME)