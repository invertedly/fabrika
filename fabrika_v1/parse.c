#include "parse.h"

#include "point.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"

#include "new.h"

#include "global_const.h"

#include "obj_info.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static int get_params_count(enum obj_name obj_name)
{
	switch (obj_name)
	{
	case POINT:
	{
		return POINT_PARAMS_COUNT;
	}
	case CIRCLE:
	{
		return CIRCLE_PARAMS_COUNT;
	}
	case LINE:
	{
		return LINE_PARAMS_COUNT;
	}
	case RECT:
	{
		return RECT_PARAMS_COUNT;
	}
	default:
	{
		return NO_PARAMS;
	}
	}
}

static int get_params_point(const char* buffer, char* name, int** obj_params)
{
	int* p = *obj_params;

	return sscanf_s(buffer, "%s%d%d", name, MAX_BUFFER_SIZE, 
					&p[0], &p[1]);
}

static int get_params_circle(const char* buffer, char* name, int** obj_params)
{
	int* p = *obj_params;

	return sscanf_s(buffer, "%s%d%d%d", name, MAX_BUFFER_SIZE,
					&p[0], &p[1], &p[2]);
}

static int get_params_line(const char* buffer, char* name, int** obj_params)
{
	int* p = *obj_params;

	return sscanf_s(buffer, "%s%d%d%d%d", name, MAX_BUFFER_SIZE,
					&p[0], &p[1], &p[2], &p[3]);
}

static int get_params_rect(const char* buffer, char* name, int** obj_params)
{
	int* p = *obj_params;

	return sscanf_s(buffer, "%s%d%d%d%d", name, MAX_BUFFER_SIZE,
					&p[0], &p[1], &p[2], &p[3]);
}

static void* get_params(const char* buffer, enum obj_name obj_name,
	int (*get_par) (const char*, char*, int**))
{
	char* name = malloc(sizeof(char) * MAX_BUFFER_SIZE);

	if (name == NULL || get_par == NULL)
	{
		return NULL;
	}

	int params_count = get_params_count(obj_name);

	int* obj_params = (int*)malloc(sizeof(int) * params_count);

	if (obj_params == NULL)
	{
		free(name);
		return NULL;
	}

	if (get_par(buffer, name, &obj_params) != params_count + 1)
	{
		free(obj_params);
		obj_params = NULL;
	}

	free(name);
	return obj_params;
}

typedef int (*parsing_func)(const char*, char*, int**);

parsing_func get_parsing_func(enum obj_name obj_name)
{
	if (obj_name == POINT)
	{
		return get_params_point;
	}
	else if (obj_name == CIRCLE)
	{
		return get_params_circle;
	}	
	else if (obj_name == RECT)
	{
		return get_params_rect;
	}	
	else if (obj_name == LINE)
	{
		return get_params_line;
	}

	return NULL;
}

static int get_obj_name(const char* buffer, char* name)
{
	if (buffer == NULL || name == NULL)
	{
		return ERROR_ARGS;
	}

	int i = 0;
	for (; i < MAX_BUFFER_SIZE; i++)
	{
		char c = buffer[i];
		if (c != '\0' && c != ' ' && c != '\n')
		{
			name[i] = c;
		}
		else
		{
			name[i] = '\0';
			break;
		}
	}

	if (i == MAX_BUFFER_SIZE)
	{
		free(name);
		return ERROR_PARAMS;
	}

	return SUCCESS;
}

static int convert_obj_name(const char* name, enum obj_name* obj_name)
{
	if (name == NULL)
	{
		return ERROR_ARGS;
	}

	if (!strcmp(name, "point"))
	{
		*obj_name = POINT;
	}
	else if (!strcmp(name, "circle"))
	{
		*obj_name = CIRCLE;
	}
	else if (!strcmp(name, "rect"))
	{
		*obj_name = RECT;
	}
	else if (!strcmp(name, "line"))
	{
		*obj_name = LINE;
	}
	else 
	{
		*obj_name = UNKNWN;
	}

	return SUCCESS;
}

struct obj_info parse_line(const char* buffer)
{
	struct obj_info info = {UNKNWN, 0, NULL};

	if (buffer == NULL)
	{
		return info;
	}

	char* name = malloc(sizeof(char) * MAX_BUFFER_SIZE);

	if (name == NULL)
	{
		return info;
	}

	if (get_obj_name(buffer, name) != SUCCESS)
	{
		free(name);
		return info;
	}

	if (convert_obj_name(name, &info.name) != SUCCESS)
	{
		free(name);
		return info;
	}

	free(name);

	parsing_func parsing_func = get_parsing_func(info.name);

	info.params_count = get_params_count(info.name);

	info.params_int = get_params(buffer, info.name, parsing_func);

	return info;
}
