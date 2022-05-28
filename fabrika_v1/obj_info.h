#pragma once

enum obj_name {
	POINT,
	CIRCLE,
	LINE,
	RECT,
	UNKNWN
};

struct obj_info
{
	enum obj_name name;
	int params_count;
	int* params_int;
};