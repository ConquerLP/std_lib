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
	Array* a = Array_ctor(DEF_STRING, 10);
	String* tmp = String_ctor("test");
	a->_ArrayIF->fill(a, tmp);
	delete(a);

	/* End of your actual program */
	_PRINT_DEBUG_MEMORY;
	DEF_CLEAR_MEM;
	return 0;
}