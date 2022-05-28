#include <stdio.h>
#include "rectangle.h"
#include "new.h"

static void* Rectangle_ctor(void* _self, va_list* app)
{
	struct Rectangle* self = _self;

	void* p1 = &(self->p1);
	void* p2 = &(self->p2);

	((const struct Class*)Point)->ctor(p1, app);
	((const struct Class*)Point)->ctor(p2, app);

	return self;
}

#define x(p) (((const struct Point *)(p)) -> x)
#define y(p) (((const struct Point *)(p)) -> y)

static void Rectangle_draw(const void* _self)
{
	const struct Rectangle* self = _self;

	printf("rect at (%d,%d), (%d,%d)\n", x(&self->p1), y(&self->p1), x(&self->p2), y(&self->p2));
}

static const struct Class _Rectangle = {
	sizeof(struct Rectangle),
	Rectangle_ctor,
	0,
	Rectangle_draw
};

const void* Rectangle = &_Rectangle;