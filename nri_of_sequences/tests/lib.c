#include "lib.h"

#include "../generator.h"

#include <stdio.h>

static Generator should_continue_gen;

static void _shouldContinue(void* arg) {
  int c;
  while ((c = getchar()) != EOF)
    if (c == '\n')
      yield(arg);
}

bool shouldContinue() {
  void* non_null_ptr = &should_continue_gen;
  if (should_continue_gen == NULL) {
    should_continue_gen = makeGenerator(_shouldContinue, non_null_ptr, 4096 /* 1KiB */);
    if (should_continue_gen == NULL) {
      perror("Error in shouldContinue");
      return false;
    }
  }
  return next(should_continue_gen) != NULL;
}
