## Test suites
TESTS := $(shell ls -d ./*/)

CFLAGS += -I../../include
CFLAGS += -I/usr/local/include
CFLAGS += -L/usr/local/lib
CFLAGS += -lglfw3
CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -framework OpenGL

export CFLAGS

## Compiles and runs all test suites
.PHONY: all
all: $(TESTS)

## Test suite targets
.PHONY: $(TESTS)
$(TESTS):
	@$(MAKE) -C $@

## Clean all test suites
.PHONY: clean
clean:
	$(foreach T, $(TESTS), $(MAKE) clean -C $T;)
