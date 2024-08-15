.PHONY: all clean clean-tests

SOURCES=$(wildcard impl*.nasm)
OBJS=$(SOURCES:%.nasm=build/%.o)
BINARIES=$(OBJS:%.o=%)
PASS=$(BINARIES:build/%=tests/%.passed)

all: clean-tests tests/task.passed

build:
	mkdir build

$(OBJS): build/%.o:%.nasm | build
	nasm -f elf64 $< -o $@

$(BINARIES): %:%.o tests/test.c | build
	gcc -std=c99 tests/test.c $@.o -o $@

$(PASS): tests/%.passed:build/%
	@echo "Testing $(<:tests/%=%)..."
	@$<
	@touch $@

tests/task.passed: $(PASS)
	@test 5 -le $(words $(PASS)) || (echo "At least 5 implementations are required" && false)
	@echo "All implementations seem to be working!"
	@touch $@

clean-tests:
	@rm -f $(PASS) tests/task.passed

clean: clean-passed
	@rm -rd build/
