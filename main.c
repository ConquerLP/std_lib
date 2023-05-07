#include "std_lib.h"

int main(void) {

	String* string0 = String_ctor("test");
	
	printf("%s\n", string0->objectIF->toString(string0));

	string0->stringIF->setText(string0, "Changed");
	printf("%s\n", string0->objectIF->toString(string0));

	printf("%c\n", string0->stringIF->charAt(string0, 6));

	String* string1 = string0->stringIF->stringAt(string0, 2);
	printf("%s\n", string1->objectIF->toString(string1));

	String* string2 = string0->stringIF->substring(string0, 1, 5);
	printf("%s\n", string2->objectIF->toString(string2));

	printf("%zu\n", string0->stringIF->length(string0));
	printf("%zu\n", string1->stringIF->length(string1));
	printf("%zu\n", string2->stringIF->length(string2));

	string0->stringIF->toUpperCase(string0);
	printf("%s\n", string0->objectIF->toString(string0));

	string0->stringIF->toLowerCase(string0);
	printf("%s\n", string0->objectIF->toString(string0));

	char test = 'x';
	if (string0->stringIF->containsChar(string0, test)) {
		printf("has '%c'\n", test);
	}
	else printf("has not '%c'\n", test);

	test = 'h';
	if (string0->stringIF->containsCharOffset(string0, test, 3)) {
		printf("has '%c'\n", test);
	}
	else printf("has not '%c'\n", test);

	string0->stringIF->setText(string0, "aaabbbaaa");
	printf("%zu\n", string0->stringIF->countOccurencesChar(string0, 'b'));
	printf("%zu\n", string0->stringIF->countOccurencesChar(string0, 'a'));

	printf("%zu\n", string0->stringIF->countOccurencesCharOffset(string0, 'b', 4));
	printf("%zu\n", string0->stringIF->countOccurencesCharOffset(string0, 'a', 7));



	delete(string0);
	delete(string1);
	delete(string2);


	PRINT_DEBUG_MEMORY;

	return 0;
}