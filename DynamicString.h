#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////

// dynamic string structure
typedef struct
{
	char   *String;  // address of the string
	size_t Length;   // current string length
	size_t Capacity; // maximum string length
}
*dyn_str_t;

///////////////////////////////////////////////////////////////////////////////

// initialise dynamic string
// set its attributes according to the provided string
dyn_str_t dyn_str_init(char *s)
{
	// allocate memory for struct
	dyn_str_t dyn_str = malloc(sizeof *dyn_str);
	if(dyn_str == NULL)
	{
		printf("Failed to initialise dynamic string.\n");
		return NULL;
	}

	// calculate least power of 2 which is greater than length of string
	int power = 0;
	size_t s_length = strlen(s);
	size_t s_length_backup = s_length;
	while(s_length)
	{
		s_length >>= 1;
		++power;
	}

	// set attributes of struct
	// 'Capacity' shall always be greater than 'Length'
	// because an extra slot is required for '\0'
	dyn_str->Capacity = 1 << power;
	dyn_str->Length = s_length_backup;
	dyn_str->String = malloc(dyn_str->Capacity * sizeof *(dyn_str->String));
	memcpy(dyn_str->String, s, s_length_backup + 1);

	return dyn_str;
}

///////////////////////////////////////////////////////////////////////////////

// show all attributes
void dyn_str_show(dyn_str_t dyn_str)
{
	printf("String:   %s\n", dyn_str->String);
	printf("Length:   %zd\n", dyn_str->Length);
	printf("Capacity: %zd\n\n", dyn_str->Capacity);
	return;
}

///////////////////////////////////////////////////////////////////////////////

// string pointer getter
char *dyn_str_get(dyn_str_t dyn_str)
{
	return dyn_str->String;
}

///////////////////////////////////////////////////////////////////////////////

// string length getter
size_t dyn_str_len(dyn_str_t dyn_str)
{
	return dyn_str->Length;
}

///////////////////////////////////////////////////////////////////////////////

// extend dynamic string
_Bool dyn_str_extend(dyn_str_t dyn_str, char *s)
{
	// check whether there is enough space available to extend
	size_t s_length = strlen(s);
	size_t required = dyn_str->Length + s_length + 1;
	if(required > dyn_str->Capacity)
	{
		// not enough space
		// double the capacity of the dynamic array
		dyn_str->Capacity <<= 1;
		char *temp = realloc(dyn_str->String, dyn_str->Capacity * sizeof *temp);
		if(temp == NULL)
		{
			printf("Failed to extend dynamic string.\n");
			return 0;
		}
		dyn_str->String = temp;

		// append the characters of the second string to the first
		char *ptr = dyn_str->String + dyn_str->Length;
		memcpy(ptr, s, s_length + 1);
		dyn_str->Length = required - 1;

		return 1;
	}

}
	// // set the lenth of the array
	// // 'size' is unsigned, so no need to check for negative value
	// // it is your responsibility to provide a sane input
	// a->length = size;

	// // try to allocate space for array
	// // keep some space to allow the array to grow
	// size = (size + 1) << 1;
	// if(clear)
	// {
	// 	a->array = calloc(size, sizeof *a->array);
	// }
	// else
	// {
	// 	a->array = malloc(size * sizeof *a->array);
	// }
	// if(a->array == NULL)
	// {
	// 	printf("Failed to initialise dynamic array!\n");
	// 	return 0;
	// }

	// // allow the array to grow till this length
	// a->capacity = size;

	// return 1;
// }

// ///////////////////////////////////////////////////////////////////////////////
// 
// // return the length of the dynamic array
// size_t dyn_arr_len(Array *a)
// {
// 	return a->length;
// }
// 
// ///////////////////////////////////////////////////////////////////////////////
// 
// // append an element to the end of the array
// _Bool dyn_arr_append(Array *a, char element)
// {
// 	// check whether the array is full
// 	if(a->length == a->capacity)
// 	{
// 		// array is full
// 		// double the array capacity
// 		a->capacity <<= 1;
// 
// 		// create temporary pointer in case reallocation fails
// 		char *temp;
// 		temp = realloc(a->array, a->capacity * sizeof *temp);
// 		if(temp == NULL)
// 		{
// 			printf("Failed to append to dynamic array!\n");
// 			return 0;
// 		}
// 		a->array = temp;
// 	}
// 
// 	// append the element
// 	// also increase the element counter
// 	a->array[a->length++] = element;
// 
// 	return 1;
// }
// 
// ///////////////////////////////////////////////////////////////////////////////
// 
// // delete the dynamic array
// void dyn_arr_delete(Array *a, _Bool clear)
// {
// 	// erase the contents of the array if required
// 	if(clear)
// 	{
// 		memset(a->array, 0, a->capacity);
// 	}
// 
// 	// release memory used by the array as well as the structure
// 	free(a->array);
// }
// 
// ///////////////////////////////////////////////////////////////////////////////
// 
// // pop the last element in the array
// char dyn_arr_pop(Array *a, _Bool clear)
// {
// 	// cannot pop an empty array
// 	if(a->length == 0)
// 	{
// 		printf("Cannot pop an empty dynamic array!\n");
// 		return 0;
// 	}
// 
// 	// decrement the array length
// 	// but do not decrease the capacity of the array
// 	char popped_element;
// 	popped_element = a->array[--a->length];
// 
// 	// erase the element if required
// 	if(clear)
// 	{
// 		a->array[a->length] = 0;
// 	}
// 
// 	return popped_element;
// }
