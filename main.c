#include "std_lib.h"

int main(void) {
	DEF_START_UP;

	String* str = String_ctor("test");

	if (str->stringIF->startsWithString(str, "test")) {
		printf("yes");
	}

	//Array* arr = Array_ctor("String", 200);
	//arr->arrayIF->fill(arr, str);

	//delete(str);

	_PRINT_DEBUG_MEMORY;
	DEF_CLEAR_MEM;
	return 0;
}