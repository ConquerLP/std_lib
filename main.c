#include "std_lib.h"

int main(void) {

	List* l = List_ctor("double");

	double b = 4.0;

	l->listIF->append(l, &b);

	for (size_t i = 0; i < l->listIF->size(l); ++i) {
		double* bb = l->listIF->get(l, i);
		printf("%lf\n", *bb);
	}
	
	delete(l);

	PRINT_DEBUG_MEMORY;

	return 0;
}