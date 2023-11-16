#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Define the data type used in the Vector
typedef int Data;

// Define the Vector structure
typedef struct Vector {
    size_t size;
    size_t capacity;
    Data *array;
} Vector;

// Function to create and initialize a new Vector
Vector *newVector(size_t capacity) {
    Vector *newVector = (Vector *)malloc(sizeof(Vector));
    if (newVector != NULL) {
        newVector->size = 0;
        newVector->capacity = capacity;
        newVector->array = (Data *)calloc(capacity, sizeof(Data));
    }
    return newVector;
}

// Function to deallocate an existing Vector
void deleteVector(Vector *v) {
    if (v != NULL) {
        free(v->array);
        free(v);
    }
}

// Function to print details of a Vector
int printVector(const void *v) {
    if (v == NULL) {
        return printf("(null)");
    } else {
        printf("Vector(%p){.size=%lu, .capacity=%lu, .array={", v, ((Vector *)v)->size, ((Vector *)v)->capacity);
        for (size_t i = 0; i < ((Vector *)v)->capacity; ++i) {
            printf("%d", ((Vector *)v)->array[i]);
            if (i < ((Vector *)v)->capacity - 1) {
                printf(",");
            }
        }
        printf("}}");
    }
    return 0;
}

// Function to get a pointer to the Data element at an index
Data *at(Vector *v, size_t index) {
    return (v != NULL && index < v->size) ? &(v->array[index]) : NULL;
}

// Function to clear the Vector in place
void clear(Vector *v) {
    if (v != NULL) {
        for (size_t i = 0; i < v->capacity; ++i) {
            v->array[i] = 0;
        }
        v->size = 0;
    }
}

// Function to search for the first matching Data item
Data *find(Vector *v, Data d) {
    if (v != NULL) {
        for (size_t i = 0; i < v->size; ++i) {
            if (v->array[i] == d) {
                return &(v->array[i]);
            }
        }
    }
    return NULL;
}

// Function to insert a data item into the Vector
Data *insert(Vector *v, Data d, size_t idx) {
    if (v != NULL && idx <= v->size) {
        if (v->size == v->capacity) {
            // If the size is equal to the capacity, resize the vector
            v = resize(v, v->capacity * 2);
            if (v == NULL) {
                return NULL; // Resize failed
            }
        }

        // Shift elements to the right to make space for the new element
        for (size_t i = v->size; i > idx; --i) {
            v->array[i] = v->array[i - 1];
        }

        // Insert the new element at the specified index
        v->array[idx] = d;
        ++(v->size);

        return &(v->array[idx]);
    }
    return NULL;
}

// Function to dynamically resize the Vector's array storage
Vector *resize(Vector *v, size_t count) {
    if (v != NULL) {
        Data *newArray = (Data *)realloc(v->array, count * sizeof(Data));
        if (newArray != NULL) {
            v->array = newArray;
            v->capacity = count;
            return v;
        } else {
            return NULL; // realloc failed
        }
    }
    return NULL;
}

// Function to remove an item from the Vector
Data *remove(Vector *v, size_t index) {
    if (v != NULL && index < v->size) {
        Data *removedItem = &(v->array[index]);

        // Shift elements to the left to fill the gap
        for (size_t i = index; i < v->size - 1; ++i) {
            v->array[i] = v->array[i + 1];
        }

        // Set the last element to 0
        v->array[v->size - 1] = 0;
        --(v->size);

        return removedItem;
    }
    return NULL;
}
