#include "def.h"

#include <stdlib.h>
#include <stdio.h>

void def_critical_error(const char* err_msg)
{
	fprintf(stdout, "An critical error occured: %s.\nExit programm (exit(1))\n", err_msg);
	DEF_CLEAR_MEM;
	exit(1);
}

Def_Hashtable* DEF_GLOBAL_HASHTABLE = NULL;
FILE* DEF_GLOBAL_DEBUG_OUTPUT = NULL;
char* def_mem_fail = "Could not allocate memory";

/* hash functions */
size_t def_hash_ptr(void* ptr)
{
	if (!ptr) return 0;
	return (size_t)ptr % DEF_HASH_TABLE_SIZE;
}

Def_Hashtable* def_hashtable_create(void)
{
	Def_Hashtable* table = malloc(sizeof(Def_Hashtable));
	if (!table) def_critical_error(def_mem_fail);
	table->entries = malloc(sizeof(Def_Hashentry*) * DEF_HASH_TABLE_SIZE);
	if (!table->entries) def_critical_error(def_mem_fail);
	table->allocations = 0;
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
	const char* type, char* file, size_t line, const char* func)
{
	if (!key) return NULL;
	if (!type) return NULL;
	if (!func) return NULL;
	Def_Hashentry* entry = malloc(sizeof(Def_Hashentry));
	if (!entry) def_critical_error(def_mem_fail);
	entry->key = key;
	entry->is_object = is_obj;
	entry->freed = freed;
	char* entry_type = malloc(sizeof(char) * strlen(type) + 1);
	if (!entry_type) def_critical_error(def_mem_fail);
	strcpy(entry_type, type);
	char* entry_file = malloc(sizeof(char) * strlen(def_trim_filename(file)) + 1);
	if (!entry_file) def_critical_error(def_mem_fail);
	strcpy(entry_file, def_trim_filename(file));
	char* entry_func = malloc(sizeof(char) * strlen(func) + 1);
	if (!entry_func) def_critical_error(def_mem_fail);
	strcpy(entry_func, func);
	entry->type = entry_type;
	entry->file = entry_file;
	entry->func = entry_func;
	entry->line = line;
	entry->next = NULL;
	return entry;
}

void def_hashtable_set(
	Def_Hashtable* table, void* key, boolean is_obj, boolean freed,
	const char* type, char* file, size_t line, const char* func)
{
	if (!table) return;
	if (!key) return;
	//calc slot for this key
	size_t slot = def_hash_ptr(key);
	Def_Hashentry* entry = table->entries[slot];
	//check if the entry at this slot is NULL
	//if so "place" the key there
	if (entry == NULL) {
		table->entries[slot] = def_hashentry_create(key, is_obj, freed, type, file, line, func);
		table->allocations++;
		return;
	}
	//else traverse through each entry until the end is
	//reached or a matching key is found
	Def_Hashentry* prev = NULL;
	while (entry != NULL) {
		if (entry->key == key) {
			def_hashentry_update(entry, is_obj, freed, type, file, line, func);
			return;
		}
		prev = entry;
		entry = prev->next;
	}
	//end of chain reached without a match, create a new entry
	prev->next = def_hashentry_create(key, is_obj, freed, type, file, line, func);
	table->allocations++;
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
			return entry->is_object;
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

void def_hashentry_update(Def_Hashentry* entry, boolean is_obj, boolean freed,
	const char* type, char* file, size_t line, const char* func)
{
	if (!entry) def_critical_error("Nullptr: Def_Hashentry");
	if (!type) def_critical_error("Nullptr: Hashtable: type");
	if (!file) def_critical_error("Nullptr: Hashtable: file");
	if (!func) def_critical_error("Nullptr: Hashtable: func");

	entry->line = line;
	entry->is_object = is_obj;
	entry->freed = freed;

	char* entry_type = malloc(sizeof(char) * strlen(type) + 1);
	if (!entry_type) def_critical_error(def_mem_fail);
	strcpy(entry_type, type);
	char* entry_file = malloc(sizeof(char) * strlen(def_trim_filename(file)) + 1);
	if (!entry_file) def_critical_error(def_mem_fail);
	strcpy(entry_file, def_trim_filename(file));
	char* entry_func = malloc(sizeof(char) * strlen(func) + 1);
	if (!entry_func) def_critical_error(def_mem_fail);
	strcpy(entry_func, func);

	free(entry->file);
	entry->file = NULL;
	free(entry->type);
	entry->type = NULL;
	free(entry->func);
	entry->func = NULL;

	entry->type = entry_type;
	entry->file = entry_file;
	entry->func = entry_func;
}

void def_hashtable_print(Def_Hashtable* table, FILE* stream)
{
	if (!table) return;
	if (!stream) stream = stdout;
	char line[] = { "------------------------------------------------------------------------------------------------" };
	char blank[] = { "                                                                                          " };
	size_t mod = 5;
	size_t freed = 0;
	fprintf(stream, "\n%s%s\nMemorymap:%s%s |\n", line, line, blank, blank);
	fprintf(stream, "%s%s\n", line, line);
	fprintf(stream, "Slot[*******] |");
	fprintf(stream, " Address[0x****************] |");
	fprintf(stream, " Object[y/n] |");
	fprintf(stream, " Datatype[********************] |");
	fprintf(stream, " Line#[*****] |");
	fprintf(stream, " File[................\\*.c] |");
	fprintf(stream, " Function[******************************] |");
	fprintf(stream, " Freed[y/n] |\n");
	
	for (size_t i = 0, j = 0; i < DEF_HASH_TABLE_SIZE; ++i) {
		Def_Hashentry* entry = table->entries[i];
		if (!entry) continue;
		else j++;
		fprintf(stream, "Slot[%*zu] |", 7, i);
		size_t k = 0;
		while (true) {
			k++;
			char* flag0 = "yes";
			char* flag1 = "yes";
			if (!entry->is_object) flag0 = " no";
			if (!entry->freed) flag1 = " no";
			else freed++;
			fprintf(stream,
				"        [0x%*p] |       [%3s] |         [%20s] |      [%5zu] |     [%20s] |         [%30s] |      [%s] |",
				16,
				entry->key,
				flag0,
				entry->type,
				entry->line,
				entry->file,
				entry->func,
				flag1
			);
			if (!entry->next) {
				if (k > 1) fprintf(stream, "\n%s%s", line, line);
				else if (j % mod == 0) fprintf(stream, "\n%s%s", line, line);
				break;
			} 
			fprintf(stream, "\n              |");
			entry = entry->next;
		}
		fprintf(stream, "\n");
	}
	fprintf(stream, "%s%s\n", line, line);
	fprintf(stream, "[%10zu] of [%10zu] pointers were freed.%142s|\n", freed, table->allocations, " ");
	fprintf(stream, "%s%s", line, line);
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
				free(entry->func);
				free(entry);
				break;
			}
			head = entry->next;
			free(entry->type);
			free(entry->file);
			free(entry->func);
			free(entry);
			entry = head;
		}
	}
	free(table->entries);
	free(table);
}
