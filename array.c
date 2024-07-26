#include "json.h"

#include <stdbool.h>
#include <stdio.h>

#include "d4t4-5tructur35/array_list.h"

#define AL_INITIAL_CAPACITY 10

JSONArray
AllocJSONArray() {
	JSONArray a;
	a.al = AllocArrayList(sizeof(JSONValue), AL_INITIAL_CAPACITY);
	return a;
}

JSONValue
JA_GetValue(int i, JSONArray a) {
	void* data = AL_Get(a.al, i);
	return *((JSONValue *) data);
}

JSONObject
JA_GetObject(int i, JSONArray a) {
	JSONValue value = JA_GetValue(i, a);
	if (value.type != JSON_OBJECT) {
		fprintf(stderr, "Value at index %d is not an object\n", i);
		return (JSONObject){};
	}

	return value.object;

}

JSONArray
JA_GetArray(int i, JSONArray a) {
	JSONValue value = JA_GetValue(i, a);
	if (value.type != JSON_ARRAY) {
		fprintf(stderr, "Value at index %d is not an array\n", i);
		return (JSONArray){};
	}

	return value.array;
}

int
JA_GetInt(int i, JSONArray a) {
	JSONValue value = JA_GetValue(i, a);
	if (value.type != JSON_INT) {
		fprintf(stderr, "Value at index %d is not an integer\n", i);
		return 0;
	}

	return value.integer;
}

float
JA_GetFloat(int i, JSONArray a) {
	JSONValue value = JA_GetValue(i, a);
	if (value.type != JSON_FLOAT) {
		fprintf(stderr, "Value at index %d is not an float\n", i);
		return 0;
	}

	return value.floating;
}

String
JA_GetString(int i, JSONArray a) {
	JSONValue value = JA_GetValue(i, a);
	if (value.type != JSON_STRING) {
		fprintf(stderr, "Value at index %d is not a string\n", i);
		return S_Null(); 
	}

	return value.str;
}

bool
JA_GetBoolean(int i, JSONArray a) {
	JSONValue value = JA_GetValue(i, a);
	if (value.type != JSON_BOOL) {
		fprintf(stderr, "Value at index %d is not a boolean\n", i);
		return 0;
	}

	return value.boolean;
}

static void
_FreeJSONArrayElem(size_t i, void *elem, void *arg) {
	JSONValue *value = ((JSONValue*) elem);
	FreeJSONValue(value);
}

void
FreeJSONArray(JSONArray* a) {
	AL_Iterate(a->al, _FreeJSONArrayElem, NULL);
	FreeArrayList(&a->al);
}
