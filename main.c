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
	
	printf("%zu\n", string0->stringIF->findFirstChar(string0, 'a'));
	printf("%zu\n", string0->stringIF->findLastChar(string0, 'a'));

	printf("%zu\n", string0->stringIF->findFirstCharOffset(string0, 'a', 5));
	printf("%zu\n", string0->stringIF->findLastCharOffset(string0, 'a', 5));
	printf("%zu\n", string0->stringIF->findLastCharOffset(NULL, 'a', 5));

	Array* a = string0->stringIF->findAllChar(string0, 'a');

	for (size_t i = 0; i < a->arrayIF->length(a); ++i) {
		printf("*%zu\n", *((size_t*)a->arrayIF->get(a, i)));
	}

	delete(a);

	Array* b = string0->stringIF->findAllCharOffset(string0, 'a', 5);

	for (size_t i = 0; i < b->arrayIF->length(b); ++i) {
		printf("#%zu\n", *((size_t*)b->arrayIF->get(b, i)));
	}

	delete(b);


	printf("%s\n", string0->objectIF->toString(string0));
	string0->stringIF->replaceFirstChar(string0, 'a', 'u');
	printf("%s\n", string0->objectIF->toString(string0));

	string0->stringIF->replaceLastChar(string0, 'b', 'i');
	printf("%s\n", string0->objectIF->toString(string0));

	string0->stringIF->replaceAllChar(string0, 'a', 'u');
	printf("%s\n", string0->objectIF->toString(string0));


	printf("%s\n", string0->objectIF->toString(string0));
	string0->stringIF->replaceFirstCharOffset(string0, 'u', 'a', 5);
	printf("%s\n", string0->objectIF->toString(string0));

	string0->stringIF->replaceLastCharOffset(string0, 'i', 'b', 4);
	printf("%s\n", string0->objectIF->toString(string0));

	string0->stringIF->replaceAllCharOffset(string0, 'u', 'a', 5);
	printf("%s\n", string0->objectIF->toString(string0));

	string0->stringIF->setText(string0, "Tesssst");
	printf("%s\n", string0->objectIF->toString(string0));
	string0->stringIF->removeFirstChar(string0, 's');
	printf("%s\n", string0->objectIF->toString(string0));
	string0->stringIF->removeLastChar(string0, 's');
	printf("%s\n", string0->objectIF->toString(string0));
	string0->stringIF->removeAllChar(string0, 's');
	printf("%s\n", string0->objectIF->toString(string0));

	string0->stringIF->setText(string0, "Tesssst");
	printf("%s\n", string0->objectIF->toString(string0));
	string0->stringIF->removeFirstCharOffset(string0, 's', 4);
	printf("%s\n", string0->objectIF->toString(string0));
	string0->stringIF->removeLastCharOffset(string0, 's', 1);
	printf("%s\n", string0->objectIF->toString(string0));
	string0->stringIF->removeAllCharOffset(string0, 's', 100);
	printf("%s\n", string0->objectIF->toString(string0));

	string1->stringIF->setText(string1, "find");
	string2->stringIF->setText(string2, "FIND");
	string0->stringIF->setText(string0, "findMEfindMEfindME");
	if (string0->stringIF->containsSubstring(string0, string1)) {
		printf("found\n");
	}
	if (string0->stringIF->containsSubstringOffset(string0, string1, 4)) {
		printf("found\n");
	}
	if (!string0->stringIF->containsSubstring(string0, string2)) {
		printf("not found\n");
	}
	if (!string0->stringIF->containsSubstringOffset(string0, string2, 4)) {
		printf("not found\n");
	}

	printf("%zu\n", string0->stringIF->countSubstringOccurences(string0, string1));
	printf("%zu\n", string0->stringIF->countSubstringOccurencesOffset(string0, string1, 2));
	printf("%zu\n", string0->stringIF->countSubstringOccurences(string0, string2));

	printf("*%zu\n", string0->stringIF->findFirstString(string0, string1));
	printf("*%zu\n", string0->stringIF->findLastString(string0, string1));
	printf("*%zu\n", string0->stringIF->findFirstStringOffset(string0, string1, 2));
	printf("**%zu\n", string0->stringIF->findLastStringOffset(string0, string1, 20));


	Array* c = string0->stringIF->findAllSubstrings(string0, string1);

	for (size_t i = 0; i < c->arrayIF->length(c); ++i) {
		printf("#%zu\n", *((size_t*)c->arrayIF->get(c, i)));
	}
	delete(c);

	Array* d = string0->stringIF->findAllSubstringsOffset(string0, string1, 6);

	for (size_t i = 0; i < d->arrayIF->length(d); ++i) {
		printf("*%zu\n", *((size_t*)d->arrayIF->get(d, i)));
	}
	delete(d);

	string0->stringIF->replaceAllSubstring(string0, string1, string2);
	printf("%s\n", string0->objectIF->toString(string0));

	string2->stringIF->setText(string2, "u");
	string0->stringIF->setText(string0, "findMEfindMEfindME");
	string0->stringIF->replaceAllSubstring(string0, string1, string2);
	printf("%s\n", string0->objectIF->toString(string0));
	string0->stringIF->setText(string0, "findMEfindMEfindME");
	string0->stringIF->replaceAllSubstringOffset(string0, string1, string2, 6);
	printf("%s\n", string0->objectIF->toString(string0));

	string2->stringIF->setText(string2, "banane");
	string0->stringIF->setText(string0, "findMEfindMEfindME");
	string0->stringIF->replaceAllSubstringOffset(string0, string1, string2, 0);
	printf("%s\n", string0->objectIF->toString(string0));

	string2->stringIF->setText(string2, "banane");
	string2->stringIF->setText(string1, "find");
	string0->stringIF->setText(string0, "findMEfindMEfindME");
	string0->stringIF->replaceFirstSubstringOffset(string0, string1, string2, 0);
	printf("%s\n", string0->objectIF->toString(string0));

	string2->stringIF->setText(string2, "banane");
	string2->stringIF->setText(string1, "find");
	string0->stringIF->setText(string0, "findMEfindMEfindME");
	string0->stringIF->replaceLastSubstringOffset(string0, string1, string2, 0);
	printf("%s\n", string0->objectIF->toString(string0));


	string2->stringIF->setText(string2, "banane");
	string2->stringIF->setText(string1, "find");
	string0->stringIF->setText(string0, "findMEfindMEfindME");
	string0->stringIF->removeAllSubstringOffset(string0, string1, 0);
	printf("%s\n", string0->objectIF->toString(string0));


	string2->stringIF->setText(string2, "banane");
	string2->stringIF->setText(string1, "find");
	string0->stringIF->setText(string0, "findMEfindMEfindME");
	string0->stringIF->removeFirstSubstringOffset(string0, string1, 0);
	printf("%s\n", string0->objectIF->toString(string0));

	string2->stringIF->setText(string2, "banane");
	string2->stringIF->setText(string1, "find");
	string0->stringIF->setText(string0, "findMEfindMEfindME");
	string0->stringIF->removeLastSubstringOffset(string0, string1, 13);
	printf("%s\n", string0->objectIF->toString(string0));

	string2->stringIF->setText(string2, "find");
	string2->stringIF->setText(string1, "find");

	if (string2->stringIF->compare(string2, string1)) {
		printf("string1 is equal to string2\n");
	}

	string2->stringIF->setText(string2, "FiNd");
	string2->stringIF->setText(string1, "find");

	if (string2->stringIF->compareIgnCase(string2, string1)) {
		printf("string1 is equal to string2\n");
	}

	string0->stringIF->setText(string0, "");
	if (string0->stringIF->isEmpty(string0)) {
		printf("This string is empty\n");
	}

	string0->stringIF->setText(string0, "  ,,,   Fhi");
	string0->stringIF->trim(string0, " ,");
	printf("%s\n", string0->objectIF->toString(string0));

	String* string3 = String_doubleToString(3.4);
	printf("%s\n", string3->objectIF->toString(string3));

	String* string4 = String_floatToString(6.2f);
	printf("%s\n", string4->objectIF->toString(string4));

	String* string5 = String_intToString(-2);
	printf("%s\n", string5->objectIF->toString(string5));

	String* string6 = String_size_tToString(9);
	printf("%s\n", string6->objectIF->toString(string6));

	String* string7 = String_ctor("2");
	printf("%zu", string7->stringIF->parseSize_t(string7));

	delete(string0);
	delete(string1);
	delete(string2);
	delete(string3);
	delete(string4);
	delete(string5);
	delete(string6);
	delete(string7);

	PRINT_DEBUG_MEMORY;

	return 0;
}