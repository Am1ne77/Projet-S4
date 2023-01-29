#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

struct vector
{
    size_t capacity;
    size_t size;
    int *data;
};

// Create a new vector.
// The initial capacity is 1.
// The initial size is 0.
// If there is not enough memory, the program prints
// "Not enough memory!" and exits with the error code 1.
struct vector *vector_new();

// Delete a vector.
// Free all the allocated memory.
// After this instruction, the vector can no longer be used.
void vector_free(struct vector *v);

// Double the capacity of a vector.
// If there is not enough memory, the program prints
// "Not enough memory!" and exits with the error code 1.
void double_capacity(struct vector *v);

// Append x at the end of a vector.
// According to the size of the vector,
// we may multiply its capacity by two.
void vector_push(struct vector *v, int x);

// Remove and return the last element of a vector.
// - If the vector is not empty, the last element
//   is removed from the vector, its value is stored in x,
//   and the function returns true (1).
// - Otherwise the function returns false (0).
int vector_pop(struct vector *v, int *x);

// Get the value at the i index.
// - If the i index is not out of bound,
//   the i-index element is stored in x,
//   and the function returns true (1).
// - Otherwise the function returns false (0).
int vector_get(struct vector *v, size_t i, int *x);

// Insert x in the vector at the i-index position.
// The i index must be between 0 and v->size (included).
// According to the size of the vector,
// we may multiply its capacity by two.
// If the i index is out of bound, we do nothing.
void vector_insert(struct vector *v, size_t i, int x);

// Remove and return the i-index element of a vector.
// - If the i index is not out of bound,
//   the i-index element is removed, its value is stored in x,
//   and the function returns true (1).
// - Otherwise the function returns false (0).
int vector_remove(struct vector *v, size_t i, int *x);

// Prints the vector v
void print_vector(struct vector* v);

#endif
