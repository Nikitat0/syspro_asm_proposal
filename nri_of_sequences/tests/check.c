#include "../generator.h"

#include <stdio.h>
#include <stdlib.h>

extern void aligmentCheck(void* _);

int main() {
  int failure = 0;
  void* unique_ptr = malloc(0);
  Generator yield_gen = makeGenerator(yield, unique_ptr, 0);
  if (yield_gen == NULL) {
    perror("Failed to run checks");
    return 1;
  }
  Generator aligment_check_gen = makeGenerator(aligmentCheck, NULL, 0);
  if (aligment_check_gen == NULL) {
    perror("Failed to run checks");
    return 1;
  }
  int* aligmentCheckResult = next(aligment_check_gen);
  if (!*aligmentCheckResult) {
    puts("Stack must be properly aligned when calling entry of generator");
    failure = 1;
  }
  if (next(aligment_check_gen) != NULL)
    puts("next() must return NULL after exiting entry function of generator");
  dropGenerator(aligment_check_gen);
  if (next(NULL) != NULL) {
    puts("next(NULL) must return NULL");
    failure = 1;
  }
  if (next(yield_gen) != unique_ptr) {
    puts("Argument must be passed to entry of generator");
    failure = 1;
  }
  dropGenerator(yield_gen);
  free(unique_ptr);
  return failure;
}
