#include "std_lib.h"

int main(void) {

	Filemanager* input = Filemanager_ctor("test.txt", "r+");

	String* str = String_ctor("Test\n");

	for (size_t i = 0; i < 10; ++i) {
		//input->filemanagerIF->writeAsDouble(input, 2.5);

		printf("%lf\n", input->filemanagerIF->getLineAsDouble(input));
	}

	delete(input);
	delete(str);

	PRINT_DEBUG_MEMORY;

	return 0;
}