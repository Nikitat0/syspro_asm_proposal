.PHONY: all clean clean-tests

SOURCES=$(wildcard impl*.nasm)
OBJS=$(SOURCES:%.nasm=tests/%.o)
BINARIES=$(OBJS:%.o=%)
PASS=$(BINARIES:%=%.passed)

all: clean-passed tests/passed

$(OBJS): tests/%.o:%.nasm
	nasm -f elf64 $< -o $@

$(BINARIES): %:%.o tests/test.c
	gcc -std=c99 tests/test.c $@.o -o $@

$(PASS): %.passed:% $(BINARIES) 
	@echo "Testing $(<:tests/%=%)..."
	@$<
	@touch $@

tests/passed: $(PASS)
	@test 5 -le $(words $(PASS))
	@echo "All implementations seem to be working!"
	@touch tests/passed

clean-passed:
	@rm -f $(PASS) tests/passed

clean: clean-passed
	@rm -f $(OBJS) $(BINARIES) 
