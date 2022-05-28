#pragma once

#include "point.h"

struct Circle 
{
    const void* class;
    struct Point center;
    int rad;
};

extern const void *Circle;
