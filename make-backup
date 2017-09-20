# Fall 2017 Unicorn X Micromouse primary makefile

TEST_FILES = $(shell find ./tests/ -name "*.c")
TEST_EXECUTABLES = $(TEST_FILES:.c=.out)

# Settings
INCLUDE_DIR = -Isrc/
TESTINCLUDE_DIR = -Isrc/
CFLAGS = -Wall -Wextra -g
TEST_FLAGS = -Wall -Wextra $(TESTINCLUDE_DIR) $(TEST_LIBS) 

# Includable libraries
LIBS = 
TEST_LIBS = -lcheck

# Builds

# Runs
run-tests: tests
	./tests/*.out

# Tests
tests: $(TEST_EXECUTABLES)
tests/%.out: tests/%.c
	$(CC) -o  $@ $^ $(TEST_FLAGS)

# Cleans
.PHONY: clean clean-tests
clean: clean-tests

clean-tests:
	-rm tests/*.out


