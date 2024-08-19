.PHONY: all test clean-tests clean

LIB=tests/lib.h tests/lib.c

SAMPLES=$(wildcard tests/*-expected.txt)
SOURCES=$(SAMPLES:%-expected.txt=%.c)
BINARIES=$(SOURCES:tests/%.c=build/%)
PASS=$(BINARIES:build/%=tests/%.passed)

all: clean-tests test

build:
	mkdir build

main: main.c generator.o
	gcc -Wall -Wextra -Wpedantic -std=c99 $^ -o $@

build/generator.o: generator.nasm | build
	nasm -f elf64 $< -o $@

build/check.o: tests/check.nasm | build
	nasm -f elf64 $< -o $@

build/check: tests/check.c build/check.o build/generator.o | build
	gcc $^ -o $@

tests/check.passed: build/check
	@echo "Running preliminary checks..."
	@$<

$(BINARIES): build/%:tests/%.c build/generator.o $(LIB) | build
	gcc $^ -O3 -lm -o $@

$(PASS): tests/%.passed: build/% tests/%-input.txt tests/%-expected.txt
	@echo "Testing with $*.c..."
	$< < tests/$*-input.txt > tests/$*-actual.txt
	diff tests/$*-expected.txt tests/$*-actual.txt
	@touch $@

test: tests/check.passed $(PASS)
	@echo "All tests passed"

clean-tests:
	@rm -f tests/*-actual.txt tests/*.passed

clean: clean-tests
	@rm -rf build/
