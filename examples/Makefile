CC := gcc
SRC := $(wildcard ../deps/*/*.c)

TARGETS += grid
TARGETS += cube
TARGETS += bunny

CFLAGS += -I ../include
CFLAGS += -I ../deps
CFLAGS += -I /usr/local/include
CFLAGS += -L /usr/local/lib
CFLAGS += -l glfw3
CFLAGS += -framework OpenGL
CFLAGS += ../libglisy.a
CFLAGS += $(SRC)

.PHONY: all
all: $(TARGETS)

clean:
	rm -f $(TARGETS)
