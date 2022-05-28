#include "create_obj.h"

#include "obj_info.h"

#include "parse.h"

#include "point.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"

#include "new.h"

#include "global_const.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void* create_obj(const struct obj_info* info)
{
	int* p = info->params_int;
	int p_count = info->params_count;
	enum obj_name obj_name = info->name;

	if (p == NULL)
	{
		return NULL;
	}

	int* obj = malloc(sizeof(int) * p_count);

	if (obj == NULL)
	{
		return NULL;
	}

	switch (obj_name)
	{
	case POINT:
		if (p_count >= 2)
		{
			obj = new(Point, p[0], p[1]);
		}
		break;
	case CIRCLE:
		if (p_count >= 3)
		{
			obj = new(Circle, p[0], p[1], p[2]);
		}
		break;
	case LINE:
		if (p_count >= 4)
		{
			obj = new(Line, p[0], p[1], p[2], p[3]);
		}
		break;
	case RECT:
		if (p_count >= 4)
		{
			obj = new(Rectangle, p[0], p[1], p[2], p[3]);
		}
		break;
	case UNKNWN:
		free(obj);
		obj = NULL;
		break;
	default:
		free(obj);
		obj = NULL;
		break;
	}

	return obj;
}