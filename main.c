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


	/* End of your actual program */
	DEF_PRINT_DEBUG_MEMORY;
	DEF_CLEAR_MEM;

	return 0;
}