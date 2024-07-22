#include "json_structures.h"

#include <stdbool.h>
#include <stdio.h>

#include "d4t4-5tructur35/array_list.h"

JSONField
JA_GetField(int i, JSONArray a) {
	void* data = AL_Get(&a.al, i);
	return *((JSONField *) data);
}

JSONObject
JA_GetObject(int i, JSONArray a) {
	JSONField field = JA_GetField(i, a);
	if (field.type != JSON_OBJECT) {
		fprintf(stderr, "Value at index %d is not an object\n", i);
		return (JSONObject){};
	}

	return field.object;

}

JSONArray
JA_GetArray(int i, JSONArray a) {
	JSONField field = JA_GetField(i, a);
	if (field.type != JSON_ARRAY) {
		fprintf(stderr, "Value at index %d is not an array\n", i);
		return (JSONArray){};
	}

	return field.array;
}

int
JA_GetInt(int i, JSONArray a) {
	JSONField field = JA_GetField(i, a);
	if (field.type != JSON_INT) {
		fprintf(stderr, "Value at index %d is not an integer\n", i);
		return 0;
	}

	return field.integer;
}

float
JA_GetFloat(int i, JSONArray a) {
	JSONField field = JA_GetField(i, a);
	if (field.type != JSON_FLOAT) {
		fprintf(stderr, "Value at index %d is not an float\n", i);
		return 0;
	}

	return field.floating;
}


char*
JA_GetString(int i, JSONArray a) {
	JSONField field = JA_GetField(i, a);
	if (field.type != JSON_STRING) {
		fprintf(stderr, "Value at index %d is not a string\n", i);
		return 0;
	}

	return field.str;
}

bool
JA_GetBoolean(int i, JSONArray a) {
	JSONField field = JA_GetField(i, a);
	if (field.type != JSON_BOOL) {
		fprintf(stderr, "Value at index %d is not a boolean\n", i);
		return 0;
	}

	return field.boolean;
}
