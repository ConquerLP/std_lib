#include "std_lib.h"

int main(void) {

	Filemanager* input = Filemanager_ctor("test.txt", "r");

	Array* arr = input->filemanagerIF->scanCompleteFile(input);

	for (size_t i = 0; i < arr->arrayIF->length(arr); ++i) {
		String* tmp = arr->arrayIF->get(arr, i);
		printf("%s", tmp->objectIF->toString(tmp));
	}

	PRINT_DEBUG_MEMORY;

	return 0;
}