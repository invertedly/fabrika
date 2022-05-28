#pragma once

#include "point.h"

struct Rectangle
{
	const void* class;
	struct Point p1;
	struct Point p2;
};

extern const void* Rectangle;