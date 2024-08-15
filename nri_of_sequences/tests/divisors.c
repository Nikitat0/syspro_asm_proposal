#include "../generator.h"

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void _divisorsRecursive(uint64_t n, uint64_t sqrtn, uint64_t i) {
  for (; i <= sqrtn; i++)
    if (n % i == 0) {
      yield(&i);
      _divisorsRecursive(n, sqrtn, i + 1);
      uint64_t j = n / i;
      if (i != j)
        yield(&j);
      break;
    }
}

static void _divisors(void* arg) {
  uint64_t n = *(uint64_t*) arg;
  _divisorsRecursive(n, (uint64_t) sqrtl(n), 1);
}

Generator divisors(uint64_t* n) {
  return makeGenerator(_divisors, n, 4096 /* 4KiB */);
}

int main() {
  uint64_t n;
  printf("Enter number: ");
  if (scanf("%" SCNu64, &n) != 1)
    return EXIT_FAILURE;
  Generator divs = divisors(&n);
  if (divs == NULL) {
    perror("Error in main");
    return EXIT_FAILURE;
  }
  uint64_t* div;
  printf("Divisors:");
  while ((div = next(divs)) != NULL) {
    printf(" %" PRIu64, *div);
  }
  puts("");
}
