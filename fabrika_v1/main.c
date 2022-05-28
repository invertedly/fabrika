#include "new.h"

#include "parse.h"

#include "create_obj.h"

#include "global_const.h"

#include "obj_info.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Error: found %d arguments. Needs exactly 1 - filename.\n", argc - 1);
		return ERROR_ARGS;
	}

	FILE* file;
	const char* file_name = argv[1];
	fopen_s(&file, file_name, &READ_ONLY);

	if (file == NULL)
	{
		printf("Error: cannot open file.\n");
		return ERROR_FILE;
	}

	char* str = malloc(sizeof(char) * MAX_BUFFER_SIZE);

	if (str == NULL)
	{
		return ERROR_MEMORY_ALLOC;
	}

	int capacity = 1, i = 0;

	int** objects = malloc(sizeof(int*) * capacity);

	while (fgets(str, MAX_BUFFER_SIZE, file))
	{
		struct obj_info obj_info = parse_line(str);

		int* obj_params = obj_info.params_int;

		if (obj_params == NULL)
		{
			printf("Error getting parameters from line: %s", str);
			continue;
		}

		int* obj = create_obj(&obj_info);

		if (obj == NULL)
		{
			printf("Error creating object from line: %s", str);
			continue;
		}

		i++;

		if (i > capacity)
		{
			capacity *= 2;
			void* tmp = realloc(objects, sizeof(int*) * capacity);
			if (tmp == NULL)
			{
				break;
			}
			objects = tmp;
		}

		objects[i - 1] = obj;
	}

	void* tmp = realloc(objects, sizeof(int*) * i);
	if (tmp == NULL)
	{
		return ERROR_MEMORY_ALLOC;
	}
	objects = tmp;

	for (int j = 0; j < i; j++)
	{
		draw(objects[j]);
		delete(objects[j]);
	}

	free(objects);
	free(str);
	fclose(file);

	return SUCCESS;
}