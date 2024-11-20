#include "array.h"

Array_int* newArray_int()
{
    Array_int* a = malloc(sizeof(Array_int));
    a->items = malloc(sizeof(int));
    a->length = 1;
    a->capacity = 1;
    return a;
}

void freeArray_int(Array_int* a)
{
    free(a->items);
    free(a);
}

Array_float* newArray_float()
{
    Array_float* a = malloc(sizeof(Array_float));
    a->items = malloc(sizeof(float));
    a->length = 1;
    a->capacity = 1;
    return a;
}

void freeArray_float(Array_float* a)
{
    free(a->items);
    free(a);
}

Array_char* newArray_char()
{
    Array_char* a = malloc(sizeof(Array_char));
    a->items = malloc(sizeof(char));
    a->length = 1;
    a->capacity = 1;
    return a;
}

void freeArray_char(Array_char* a)
{
    free(a->items);
    free(a);
}

Array_double* newArray_double()
{
    Array_double* a = malloc(sizeof(Array_double));
    a->items = malloc(sizeof(double));
    a->length = 1;
    a->capacity = 1;
    return a;
}

void freeArray_double(Array_double* a)
{
    free(a->items);
    free(a);
}

Array_size_t* newArray_size_t()
{
    Array_size_t* a = malloc(sizeof(Array_size_t));
    a->items = malloc(sizeof(size_t));
    a->length = 1;
    a->capacity = 1;
    return a;
}

void freeArray_size_t(Array_size_t* a)
{
    free(a->items);
    free(a);
}

Array_Buffer* newArray_Buffer()
{
    Array_Buffer* a = malloc(sizeof(Array_Buffer));
    a->items = malloc(sizeof(Buffer));
    a->length = 1;
    a->capacity = 1;
    return a;
}

void freeArray_Buffer(Array_Buffer* a)
{
    free(a->items);
    free(a);
}

Array_Line* newArray_Line()
{
    Array_Line* a = malloc(sizeof(Array_Line));
    a->items = malloc(sizeof(Line));
    a->length = 1;
    a->capacity = 1;
    return a;
}

void freeArray_Line(Array_Line* a)
{
    free(a->items);
    free(a);
}
