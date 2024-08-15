#ifndef GENERATOR_H
#define GENERATOR_H

#include <stddef.h>

typedef struct Generator* Generator;

Generator makeGenerator(void (*fn)(void*), void* arg, size_t stack_size);
void dropGenerator(Generator gen);

void* next(Generator gen);
void yield(void* ptr);

#endif
