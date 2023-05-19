#include "std_lib.h"

int main(void) {

	String* str = String_doubleToString(3.63214, 3);
	
	printf("%s", str->objectIF->toString(str));

	delete(str);

	PRINT_DEBUG_MEMORY;

	return 0;
}