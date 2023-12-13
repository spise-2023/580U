#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef DATA_T
#define DATA_T
typedef uint64_t Data;
#endif // DATA_T

#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
  size_t size;     // index of last element in the array
  size_t capacity; // the total number of elements that can be held in array
  Data *array;     // pointer to the storage space
} Vector;

Vector *newVector(size_t size);
void deleteVector(Vector *v);
int printVector(const void *v);

Data *at(Vector *v, size_t index);
void clear(Vector *v);
Data *find(Vector *v, Data d);
Data *insert(Vector *v, Data d, size_t idx);
Vector *resize(Vector *v, size_t count);
Data *removes(Vector *v, size_t index);

#endif // VECTOR_H