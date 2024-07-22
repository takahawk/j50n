#include "json_array.h"

#include <stdbool.h>

#include "json_object.h"
#include "d4t4-5tructur35/array_list.h"

// TODO: typecheck in general
// TODO: different types in array? array list will not work good with them
//       for now

JSONObject
JA_GetObject(int i, JSONArray a) {
	void* data = AL_Get(&a.al, i);
	return *((JSONObject*) data);
}

JSONArray
JA_GetArray(int i, JSONArray a) {
	void* data = AL_Get(&a.al, i);
	return *((JSONArray *) data);
}

int
JA_GetInt(int i, JSONArray a) {
	void* data = AL_Get(&a.al, i);
	return *((int *) data);
}

char*
JA_GetString(int i, JSONArray a) {
	void* data = AL_Get(&a.al, i);
	return *((char**) data);
}

bool
JA_GetBoolean(int i, JSONArray a) {
	void* data = AL_Get(&a.al, i);
	return *((bool*) data);
}
