EXE = build/main_gcc
SCRIPT = build.sh

IN = $(wildcard tests/*-input.txt)
ACT = $(IN:-input.txt=-actual.txt)
PASS = $(IN:-input.txt=.passed)

.PHONY: all test clean clean-tests clean-formatted

all: clean-tests test clean-formatted

build:
	mkdir -p build

main.c.formatted: main.c
	@clang-format $< > $@
	diff $< $@

$(EXE): $(SCRIPT) main.c.formatted library.h library.nasm | build
	bash ./$(SCRIPT) $@

test: $(PASS)
	@echo "All tests passed"

$(PASS): %.passed: %-input.txt %-expected.txt $(EXE)
	@echo "Running test $(*:tests/%=%)..."
	./$(EXE) < $*-input.txt > $*-actual.txt
	diff $*-expected.txt $*-actual.txt -Z
	@touch $@

clean-tests:
	@rm -f $(PASS)
	@rm -f $(ACT)

clean-formatted:
	@rm *.c.formatted

clean: clean-tests
	@rm -rf build
