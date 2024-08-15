#include "../generator.h"
#include "lib.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void _fibonacci(void* arg) {
  uint64_t a = 0, b = 1;
  for (;;) {
    yield(&b);
    uint64_t c = (a + b);
    a = b;
    b = c;
  }
}

Generator fibonacci() {
  return makeGenerator(_fibonacci, NULL, 0);
}

int main() {
  Generator seq = fibonacci();
  if (seq == NULL) {
    perror("Error in main");
    return EXIT_FAILURE;
  }
  do {
    uint64_t n = *(uint64_t*) next(seq);
    printf("%" PRIu64 "\n", n);
  } while (shouldContinue());
}
