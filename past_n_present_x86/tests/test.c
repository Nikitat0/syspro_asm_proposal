#include <limits.h>
#include <stdio.h>

extern int isEven(int n);

int main() {
  int numbers[12] = {
      INT_MIN,
      INT_MIN + 1,
      (int) SHRT_MIN - 1,
      (int) SHRT_MIN,
      -1,
      0,
      1,
      2,
      (int) SHRT_MAX,
      (int) SHRT_MAX + 1,
      INT_MAX - 1,
      INT_MAX,
  };
  int failed = 0;
  for (int* n = numbers; n != &numbers[10]; n++) {
    int expected = !(*n & 1), got = isEven(*n);
    if (expected != got) {
      printf("n=%d expected: %d, got: %d\n", *n, expected, got);
      failed = 1;
    }
  }
  return failed != 0;
}
