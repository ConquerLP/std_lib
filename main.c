#include "std_lib.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(void) {
	/* DO NOT DELETE THESE MACROS:
	* DEF_START_UP
	* _PRINT_DEBUG_MEMORY
	* DEF_CLEAR_MEM
	*/
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	DEF_START_UP;
	/* Your actual program */

	List* list = List_ctor(DEF_STRING);
	String* str = String_ctor("-3.141592654");
	for (size_t i = 0; i < 10000; ++i) {
		list->_ListIF->append(list, str);
	}
	printf("%s", list->o_IF->toString(list));

	delete(list);
	delete(str);

	/* End of your actual program */
	DEF_PRINT_DEBUG_MEMORY;
	DEF_CLEAR_MEM;
	_CrtDumpMemoryLeaks();

	return 0;
}