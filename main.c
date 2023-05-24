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

	String* tmp = String_ctor("test");
	tmp->_StringIF->replaceAllChar(tmp, 't', 'f');

	printf("%s\n", _printS(tmp));

	/* End of your actual program */
	_PRINT_DEBUG_MEMORY;
	DEF_CLEAR_MEM;
	return 0;
}