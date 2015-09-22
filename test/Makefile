## Test suites
TESTS := $(shell ls -d ./*/)

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
