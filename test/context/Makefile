SRC := $(wildcard *.c)
LIB := ../../libglisy.a
TESTS := $(SRC:.c=)
CFLAGS += -I../../include
CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -lglfw3

all: $(TESTS)
$(TESTS): $(LIB)
$(TESTS): $(SRC) $(wildcard ../../include/*/*.h)
	$(CC) $(CFLAGS) $(LIB) $@.c -o $@
	./$@

$(LIB):
	$(MAKE) -C ../../

clean:
	$(RM) $(SRC:.c=)
