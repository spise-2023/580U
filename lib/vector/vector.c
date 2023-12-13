#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector *newVector(size_t capacity) {
    Vector *v = (Vector *)malloc(sizeof(Vector));
    if (!v) return NULL;

    v->array = (Data *)calloc(capacity, sizeof(Data));
    if (!v->array) {
        free(v);
        return NULL;
    }

    v->size = 0;
    v->capacity = capacity;
    return v;
}

void deleteVector(Vector *v) {
    if (v) {
        free(v->array);
        free(v);
    }
}

int printVector(const void *v) {
    const Vector *vec = (const Vector *)v;
    int chars_written = 0;
    
    chars_written += printf("Vector(%p){.size=%lu, .capacity=%lu, .array={", (void *)vec, vec->size, vec->capacity);
    for (size_t i = 0; i < vec->size; i++) {
        if (i > 0) {
            chars_written += printf(", ");
        }
        chars_written += printf("%lu", vec->array[i]);
    }
    chars_written += printf("}}\n");
    
    return chars_written;
}

Data *at(Vector *v, size_t index) {
    if (index >= v->size) return NULL;
    return &(v->array[index]);
}

void clear(Vector *v) {
    memset(v->array, 0, v->capacity * sizeof(Data));
    v->size = 0;
}

Data *find(Vector *v, Data d) {
    for (size_t i = 0; i < v->size; i++) {
        if (v->array[i] == d) return &(v->array[i]);
    }
    return NULL;
}

Data *insert(Vector *v, Data d, size_t idx) {
    if (idx >= v->capacity) {
        // Expand the capacity
        size_t new_capacity = v->capacity * 2;
        if (idx >= new_capacity) {
            new_capacity = idx + 1;
        }
        Data *new_array = (Data *)realloc(v->array, new_capacity * sizeof(Data));
        if (!new_array) return NULL;
        
        // Initialize new elements to zero
        for (size_t i = v->capacity; i < new_capacity; i++) {
            new_array[i] = 0;
        }
        
        v->array = new_array;
        v->capacity = new_capacity;
    }

    // Handle the insertion
    if (idx >= v->size) {
        // Extend and fill with zeros if necessary
        for (size_t i = v->size; i < idx; i++) {
            v->array[i] = 0;
        }
        v->size = idx + 1;
    }

    v->array[idx] = d;
    return &(v->array[idx]);
}


Vector *resize(Vector *v, size_t count) {
    Data *new_array = (Data *)realloc(v->array, count * sizeof(Data));
    if (!new_array) return NULL;

    if (count > v->capacity) {
        // Initialize new elements to zero
        memset(new_array + v->capacity, 0, (count - v->capacity) * sizeof(Data));
    }

    v->array = new_array;
    v->capacity = count;
    if (v->size > count) v->size = count; // Adjust size if reduced
    return v;
}

Data *removes(Vector *v, size_t index) {
    if (index >= v->size) return NULL;

    Data *removed_item = &(v->array[index]);

    // Shift elements
    for (size_t i = index; i < v->size - 1; i++) {
        v->array[i] = v->array[i + 1];
    }

    v->array[v->size - 1] = 0; // Zero out the last element
    v->size--;

    return removed_item;
}
