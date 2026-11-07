CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
TARGET = build/jokenpo
TEST_TARGET = build/test_jokenpo

.PHONY: all clean test

all: $(TARGET)

$(TARGET): src/jokenpo.c
	mkdir -p build
	$(CC) $(CFLAGS) $< -o $@

$(TEST_TARGET): tests/test_jokenpo.c
	mkdir -p build
	$(CC) $(CFLAGS) $< -o $@

test: $(TARGET) $(TEST_TARGET)
	$(TEST_TARGET)
	sh tests/test_inputs.sh $(TARGET)

clean:
	rm -rf build
