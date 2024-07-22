#include "json.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "d4t4-5tructur35/buffer.h"
#include "d4t4-5tructur35/skip_list_map.h"

JSONField
JO_GetField(char* key, JSONObject o) {
	size_t keylen = strlen(key);
	Buffer value = SLM_Get(o.slm, AsBuffer(key, keylen));
	return *((JSONField *) value.data);
}

JSONObject
JO_GetObject(char* key, JSONObject o) {
	JSONField field = JO_GetField(key, o);
	if (field.type != JSON_OBJECT) {
		fprintf(stderr, "Value by key %s is not an object\n", key);
		return (JSONObject){};
	}

	return field.object;

}

JSONArray
JO_GetArray(char* key, JSONObject o) {
	JSONField field = JO_GetField(key, o);
	if (field.type != JSON_ARRAY) {
		fprintf(stderr, "Value by key %s is not an array\n", key);
		return (JSONArray){};
	}

	return field.array;
}

int
JO_GetInt(char* key, JSONObject o) {
	JSONField field = JO_GetField(key, o);
	if (field.type != JSON_INT) {
		fprintf(stderr, "Value by key %s is not an integer\n", key);
		return 0;
	}

	return field.integer;
}

float
JO_GetFloat(char* key, JSONObject o) {
	JSONField field = JO_GetField(key, o);
	if (field.type != JSON_FLOAT) {
		fprintf(stderr, "Value by key %s is not an float\n", key);
		return 0;
	}

	return field.floating;
}


char*
JO_GetString(char* key, JSONObject o) {
	JSONField field = JO_GetField(key, o);
	if (field.type != JSON_STRING) {
		fprintf(stderr, "Value by key %s is not a string\n", key);
		return 0;
	}

	return field.str;
}

bool
JO_GetBoolean(char* key, JSONObject o) {
	JSONField field = JO_GetField(key, o);
	if (field.type != JSON_BOOL) {
		fprintf(stderr, "Value by key %s is not a boolean\n", key);
		return 0;
	}

	return field.boolean;
}
