#include "std_lib.h"

int main(void) {
	/* DO NOT DELETE THESE MACROS:
	* DEF_START_UP
	* _PRINT_DEBUG_MEMORY
	* DEF_CLEAR_MEM
	*/
	DEF_START_UP;
	/* Your actual program */

	Vector* vec = Vector_ctor(DEF_DOUBLE, 2, 1.0, -2.3);
	printf("%s", vec->o_IF->toString(vec));

	/* End of your actual program */
	DEF_PRINT_DEBUG_MEMORY;
	DEF_CLEAR_MEM;

	return 0;
}