.PHONY: all test clean clean-tests

all: clean-tests test

build:
	mkdir build/

build/helloworld: *.nasm build.sh | build
	./build.sh $@

tests/passed: build/helloworld tests/expected.txt
	$< | diff tests/expected.txt -
	@touch $@

test: tests/passed
	@echo "Test passed"

clean-tests:
	@rm -f tests/passed

clean: clean-tests
	@rm -rf build
