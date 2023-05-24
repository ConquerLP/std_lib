#include "def.h"

#include <stdlib.h>
#include <stdio.h>

void mem_fail(void)
{
	fprintf(stdout, "Memory allocation failed.\n");
	exit(1);
}

Def_Hashtable* DEF_GLOBAL_HASHTABLE = NULL;
static size_t counter = 0;

/* hash functions */
size_t def_counter(void)
{
	return ++counter;
}

size_t def_hash_ptr(void* ptr)
{
	if (!ptr) return 0;
	return (size_t)ptr % DEF_HASH_TABLE_SIZE;
}

Def_Hashtable* def_hashtable_create(void)
{
	Def_Hashtable* table = malloc(sizeof(Def_Hashtable));
	if (!table) mem_fail();
	table->entries = malloc(sizeof(Def_Hashentry*) * DEF_HASH_TABLE_SIZE);
	if (!table->entries) mem_fail();
	for (size_t i = 0; i < DEF_HASH_TABLE_SIZE; ++i) {
		table->entries[i] = NULL;
	}
	return table;
}

char* def_trim_filename(char* filename)
{
	if (!filename) return NULL;
	size_t i = 0, j = 0;
	while (*(filename + i) != '\0') {
		if (*(filename + i) == 92) j = i;
		i++;
	}
	return (filename + j);
}

Def_Hashentry* def_hashentry_create(void* key, boolean is_obj, boolean freed, 
	const char* type, char* file, size_t line, size_t count)
{
	if (!key) return NULL;
	if (!type) return NULL;
	Def_Hashentry* entry = malloc(sizeof(Def_Hashentry));
	if (!entry) mem_fail();
	entry->key = key;
	entry->part_of_object = is_obj;
	entry->freed = freed;
	char* entry_type = malloc(sizeof(char) * strlen(type) + 1);
	if (!entry_type) mem_fail();
	strcpy(entry_type, type);
	char* entry_file = malloc(sizeof(char) * strlen(def_trim_filename(file)) + 1);
	if (!entry_file) mem_fail();
	strcpy(entry_file, def_trim_filename(file));
	entry->type = entry_type;
	entry->file = entry_file;
	entry->line = line;
	entry->count = count;
	entry->next = NULL;
	return entry;
}

void def_hashtable_set(
	Def_Hashtable* table, void* key, boolean is_obj, boolean freed,
	const char* type, char* file, size_t line, size_t count)
{
	if (!table) return;
	if (!key) return;
	//calc slot for this key
	size_t slot = def_hash_ptr(key);
	Def_Hashentry* entry = table->entries[slot];
	//check if the entry at this slot is NULL
	//if so "place" the key there
	if (entry == NULL) {
		table->entries[slot] = def_hashentry_create(key, is_obj, freed, type, file, line, count);
		return;
	}
	//else traverse through each entry until the end is
	//reached or a matching key is found
	Def_Hashentry* prev = NULL;
	while (entry != NULL) {
		if (entry->key == key) {
			entry->part_of_object = is_obj;
			entry->freed = freed;
			return;
		}
		prev = entry;
		entry = prev->next;
	}
	//end of chain reached without a match, create a new entry
	prev->next = def_hashentry_create(key, is_obj, freed, type, file, line, count);
}

boolean def_hashtable_is_object(Def_Hashtable* table, void* key)
{
	if (!table) return false;
	if (!key) return false;
	size_t slot = def_hash_ptr(key);
	Def_Hashentry* entry = table->entries[slot];
	if (!entry) return false;
	while (entry != NULL) {
		if (entry->key == key) {
			return entry->part_of_object;
		}
		entry = entry->next;
	}
	return false;
}

char* def_hashtable_get_type(Def_Hashtable* table, void* key)
{
	if (!table) return NULL;
	if (!key) return NULL;
	size_t slot = def_hash_ptr(key);
	Def_Hashentry* entry = table->entries[slot];
	if (!entry) return NULL;
	while (entry != NULL) {
		if (entry->key == key) {
			return entry->type;
		}
		entry = entry->next;
	}
	return NULL;
}

size_t def_hashtable_get_count(Def_Hashtable* table, void* key)
{
	if (!table) return 0;
	if (!key) return 0;
	size_t slot = def_hash_ptr(key);
	Def_Hashentry* entry = table->entries[slot];
	if (!entry) return 0;
	while (entry != NULL) {
		if (entry->key == key) {
			return entry->count;
		}
		entry = entry->next;
	}
	return 0;
}

void def_hashtable_print(Def_Hashtable* table)
{
	if (!table) return;
	char line[] = { "-----------------------------------------------------------------------------" };
	char blank[] = { "                                                                       " };
	size_t mod = 5;
	size_t freed = 0;
	fprintf(stdout, "\n%s%s\nMemorymap:%s%s|\n", line, line, blank, blank);
	fprintf(stdout, "%s%s\n", line, line);
	fprintf(stdout, "Slot[       ] |");
	fprintf(stdout, " Address[                  ] |");
	fprintf(stdout, " When[     ] |");
	fprintf(stdout, " Object[   ] |");
	fprintf(stdout, " Datatype[          ] |");
	fprintf(stdout, " Line#[     ] |");
	fprintf(stdout, " File[                    ] |");
	fprintf(stdout, " Freed[   ] |\n");
	
	for (size_t i = 0, j = 0; i < DEF_HASH_TABLE_SIZE; ++i) {
		Def_Hashentry* entry = table->entries[i];
		if (!entry) continue;
		else j++;
		fprintf(stdout, "Slot[%*zu] |", 7, i);
		size_t k = 0;
		while (true) {
			k++;
			char* flag0 = "yes";
			char* flag1 = "yes";
			if (!entry->part_of_object) flag0 = " no";
			if (!entry->freed) flag1 = " no";
			else freed++;
			fprintf(stdout, "        [0x%p] |     [%5zu] |       [%3s] |         [%10s] |      [%5zu] |     [%20s] |      [%s] |", 
				 entry->key,
				 entry->count,
				 flag0,
				 entry->type,
				 entry->line,
				 entry->file,
				 flag1
			);
			if (!entry->next) {
				if(k > 1) fprintf(stdout, "\n%s%s\n", line, line);
				else if(j % mod == 0) fprintf(stdout, "\n%s%s\n", line, line);
				break;
			} 
			fprintf(stdout, "\n\t      |");
			entry = entry->next;
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "%s%s\n", line, line);
	fprintf(stdout, "[%5zu] of [%5zu] pointers were freed and [%5zu] allocations were made.\n", freed, def_counter() - 2, def_counter() - 1);
	fprintf(stdout, "%s%s", line, line);
}

void def_hashtable_delete(Def_Hashtable* table)
{
	if (!table) return;
	for (size_t i = 0; i < DEF_HASH_TABLE_SIZE; ++i) {
		Def_Hashentry* entry = table->entries[i];
		Def_Hashentry* head = entry;
		if (!entry) continue;
		while (true) {
			if (!entry->freed) free(entry->key);
			if (!entry->next) {
				free(entry->type);
				free(entry->file);
				free(entry);
				break;
			}
			head = entry->next;
			free(entry->type);
			free(entry->file);
			free(entry);
			entry = head;
		}
	}
	free(table);
}

