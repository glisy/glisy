SRC := $(wildcard *.c)
LIB := ../../libglisy.a
TESTS := $(SRC:.c=)

all: $(TESTS)
$(TESTS): $(LIB)
$(TESTS): $(SRC) $(wildcard ../../include/*/*.h)
	$(CC) $(CFLAGS) $(LIB) $@.c -o $@
	./$@

$(LIB):
	$(MAKE) -C ../../

clean:
	$(RM) $(SRC:.c=)
