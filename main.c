#include "std_lib.h"

int main(void) {
	/* DO NOT DELETE:
	* DEF_START_UP
	* and
	* _PRINT_DEBUG_MEMORY
	* and
	* DEF_CLEAR_MEM
	*/
	DEF_START_UP;
	/* Your actual program */

	Filemanager* in = Filemanager_ctor("test.txt", "r");
	Array* a = in->_FilemanagerIF->scanCompleteFile(in);
	for (size_t i = 0; i < a->_ArrayIF->length(a); ++i) {
		//String* tmp = a->_ArrayIF->get(a, i);
		//printf("%s", _printS(tmp));
	}

	/* End of your actual program */
	_PRINT_DEBUG_MEMORY;
	DEF_CLEAR_MEM;
	return 0;
}