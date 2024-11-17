#ifndef REQUEST_H
#define REQUEST_H

#include "line.h"

typedef enum {
    GET,
    POST,
    PUT,
    DELETE
} Method;

typedef struct {
    Line requestName;
    Line url;
    Method method;
} Request;

#endif // REQUEST_H
