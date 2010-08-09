# GUYS GUYS GUYS MAKE SURE THIS WORKS ON BSD MAKE
# DON'T GO INTO A WHOLE BUNCH OF GNU MAKE EXTENSIONS
# I *LIKE* MY BSD MAKE, HMMKAY?

# if you have new objects, add them here
INCLUDES = common.h
OBJS = main.o network.o sys_allegro.o menu.o game.o

CC := gcc
CCLD := gcc

# TODO supply crappy win32 crappity crap
# this method works best wrt FreeBSD
# it should work fine with GNU/Linux, too
COMPFLAGS = 
CFLAGS = `allegro-config --cflags` $(COMPFLAGS)
LDFLAGS = `allegro-config --cflags --libs`
BIN     = fringe

.PHONY: all
all:    $(BIN)

.PHONY: clean
clean:
	rm -f $(OBJS) $(BIN)

$(BIN): $(OBJS)
	${CCLD} -o $(BIN) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)
