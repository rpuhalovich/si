#ifndef ARRAY_H
#define ARRAY_H

#include "line.h"
#include "buffer.h"

typedef struct {
    int* items;
    int length;
    int capacity;
} Array_int;

Array_int* newArray_int();
void freeArray_int(Array_int* a);

typedef struct {
    float* items;
    int length;
    int capacity;
} Array_float;

Array_float* newArray_float();
void freeArray_float(Array_float* a);

typedef struct {
    char* items;
    int length;
    int capacity;
} Array_char;

Array_char* newArray_char();
void freeArray_char(Array_char* a);

typedef struct {
    double* items;
    int length;
    int capacity;
} Array_double;

Array_double* newArray_double();
void freeArray_double(Array_double* a);

typedef struct {
    size_t* items;
    int length;
    int capacity;
} Array_size_t;

Array_size_t* newArray_size_t();
void freeArray_size_t(Array_size_t* a);

typedef struct {
    Buffer* items;
    int length;
    int capacity;
} Array_Buffer;

Array_Buffer* newArray_Buffer();
void freeArray_Buffer(Array_Buffer* a);

typedef struct {
    Line* items;
    int length;
    int capacity;
} Array_Line;

Array_Line* newArray_Line();
void freeArray_Line(Array_Line* a);

#endif // ARRAY_H
