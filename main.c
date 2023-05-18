#include "std_lib.h"

int main(void) {

	Filemanager* input = Filemanager_ctor("test.txt", "r+");

	String* str = String_ctor("Test\n");

	for (size_t i = 0; i < 10; ++i) {
		printf("%i\n", input->filemanagerIF->getLineAsInt(input));
	}

	delete(input);
	delete(str);

	PRINT_DEBUG_MEMORY;

	return 0;
}