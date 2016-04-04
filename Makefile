## Project settings
PROJECT_NAME ?= glisy

## Source files
SRC := $(wildcard src/*.c)

## Dependency source files
SRC += $(wildcard deps/glisy/*/*.c)
SRC += $(wildcard deps/rgba/*.c)
SRC += $(wildcard deps/sop/*.c)

## Source objects
OBJS := $(SRC:.c=.o)

## Compiler flags
CFLAGS += -Ideps
CFLAGS += -Iinclude
CFLAGS += -Wall
CFLAGS += -O2

## Target static library
TARGET_STATIC := lib$(PROJECT_NAME).a

## Builds everything
.PHONY: all
all: $(TARGET_STATIC)

## Builds static library
$(TARGET_STATIC): $(OBJS)
	$(AR) crus $@ $^

## Compiles object files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

## Installs library into system
.PHONY: install
install: $(TARGET_STATIC)
	$(CP) -r include/* $(PREFIX)/include/
	$(CP)  $(TARGET_STATIC) $(PREFIX)/lib

## Uninstalls library from system
.PHONY: uninstall
uninstall:
	$(RM) -r $(PREFIX)/include/$(PROJECT_NAME)
	$(RM) $(PREFIX)/lib/$(TARGET_STATIC)

## Cleans project directory
.PHONY: clean
clean: test/clean
clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET_STATIC)

## Compiles and runs all test
.PHONY: test
test:
	$(MAKE) -C $@

.PHONY: test/clean
test/clean:
	$(MAKE) clean -C test
