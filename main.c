#include "std_lib.h"

int main(void) {

	String* str = String_ctor("test");
	String* str1 = String_ctor("trains");

	//str->stringIF->insertCharAt(str, 'u', 1);
	str->stringIF->insertStringAt(str, str1, 1);

	delete(str);
	delete(str1);

	PRINT_DEBUG_MEMORY;

	return 0;
}