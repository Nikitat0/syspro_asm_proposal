.PHONY: all clean clean-before

SOURCES=$(wildcard impl*.S)
OBJS=$(SOURCES:%.S=build/%.o)
BINARIES=$(OBJS:%.o=%)
PASS=$(BINARIES:build/%=tests/%.passed)

DONE=$(words $(PASS))

all: clean-before tests/task.passed

build:
	mkdir build

$(OBJS): build/%.o:%.S | build
	aarch64-linux-gnu-as $< -o $@

$(BINARIES): %:%.o tests/test.c | build
	aarch64-linux-gnu-gcc -std=c99 tests/test.c $@.o -o $@

$(PASS): tests/%.passed:build/%
	@echo "Testing $(<:tests/%=%)..."
	@qemu-aarch64 $<
	@touch $@

tests/task.passed: $(PASS)
	@echo $(DONE)/7 implementations pass the tests
	@test 7 -le $(DONE) || (echo "More implementations are required" && false)
	@touch $@

clean-before:
	@rm -f $(PASS) tests/task.passed *.core

clean: clean-before
	@rm -rd build/
