#include <stdio.h>
#include "line.h"
#include "new.h"

static void* Line_ctor(void* _self, va_list* app) 
{
    struct Line* self = _self;

    void* p1 = &(self->p1);
    void* p2 = &(self->p2);

    ((const struct Class*)Point)->ctor(p1, app);
    ((const struct Class*)Point)->ctor(p2, app);

    return self;
}

#define x(p) (((const struct Point *)(p)) -> x)
#define y(p) (((const struct Point *)(p)) -> y)

static void Line_draw(const void* _self)
{
    const struct Line* self = _self;
    printf("line at (%d,%d), (%d,%d)\n", x(&self->p1), y(&self->p1), x(&self->p2), y(&self->p2));
}

static const struct Class _Line = {
    sizeof(struct Line),
    Line_ctor,
    0,
    Line_draw
};

const void* Line = &_Line;
