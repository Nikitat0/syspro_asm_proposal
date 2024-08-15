#include "../generator.h"
#include "lib.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void _collatz(void* arg) {
  uint64_t n = *(uint64_t*) arg;
  for (;;) {
    yield(&n);
    if (n == 1)
      break;
    if (n % 2 == 0)
      n /= 2;
    else
      n = 3 * n + 1;
  }
}

static Generator collatz(uint64_t* n) {
  return makeGenerator(_collatz, n, 0);
}

int main() {
  uint64_t n;
  printf("Enter number: ");
  if (scanf("%" SCNu64, &n) != 1)
    return EXIT_FAILURE;
  Generator seq = collatz(&n);
  if (seq == NULL) {
    perror("Error in main");
    return EXIT_FAILURE;
  }
  do {
    uint64_t n = *(uint64_t*) next(seq);
    printf("%" PRIu64 "\n", n);
  } while (shouldContinue());
}
