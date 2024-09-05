#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

extern int isEven(int64_t n);

int main() {
  uint64_t numbers[12] = {
      LLONG_MIN,
      LLONG_MIN + 1,
      (int) SHRT_MIN - 1,
      (int) SHRT_MIN,
      -1,
      0,
      1,
      2,
      (int) SHRT_MAX,
      (int) SHRT_MAX + 1,
      LLONG_MAX - 1,
      LLONG_MAX,
  };
  int failed = 0;
  for (uint64_t* n = numbers; n != &numbers[10]; n++) {
    int expected = !(*n & 1), got = isEven(*n);
    if (expected != got) {
      printf("n=%" PRId64 " expected: %d, got: %d\n", *n, expected, got);
      failed = 1;
    }
  }
  return failed != 0;
}
