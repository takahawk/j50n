#include "json.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "w/d4t4-5tructur35/buffer.h"
#include "w/d4t4-5tructur35/skip_list_map.h"

JSONObject
AllocJSONObject() {
	JSONObject o;
	o.slm = SLM_Create();
	return o;
}

JSONValue
JO_GetValue(char* key, JSONObject o) {
	size_t keylen = strlen(key);
	Buffer value = SLM_Get(o.slm, B_Wrap(key, keylen));
	return *((JSONValue *) value.data);
}

JSONObject
JO_GetObject(char* key, JSONObject o) {
	JSONValue value = JO_GetValue(key, o);
	if (value.type != JSON_OBJECT) {
		fprintf(stderr, "Value by key %s is not an object\n", key);
		return (JSONObject){};
	}

	return value.object;

}

JSONArray
JO_GetArray(char* key, JSONObject o) {
	JSONValue value = JO_GetValue(key, o);
	if (value.type != JSON_ARRAY) {
		fprintf(stderr, "Value by key %s is not an array\n", key);
		return (JSONArray){};
	}

	return value.array;
}

int
JO_GetInt(char* key, JSONObject o) {
	JSONValue value = JO_GetValue(key, o);
	if (value.type != JSON_INT) {
		fprintf(stderr, "Value by key %s is not an integer\n", key);
		return 0;
	}

	return value.integer;
}

float
JO_GetFloat(char* key, JSONObject o) {
	JSONValue value = JO_GetValue(key, o);
	if (value.type != JSON_FLOAT) {
		fprintf(stderr, "Value by key %s is not an float\n", key);
		return 0;
	}

	return value.floating;
}

String
JO_GetString(char* key, JSONObject o) {
	JSONValue value = JO_GetValue(key, o);
	if (value.type != JSON_STRING) {
		fprintf(stderr, "Value by key %s is not a string\n", key);
		return S_Null(); 
	}

	return value.str;
}

bool
JO_GetBoolean(char* key, JSONObject o) {
	JSONValue value = JO_GetValue(key, o);
	if (value.type != JSON_BOOL) {
		fprintf(stderr, "Value by key %s is not a boolean\n", key);
		return 0;
	}

	return value.boolean;
}

static void
_FreeObjectField(Buffer key, Buffer value, void* arg) {
	JSONValue *jsonValue = ((JSONValue*) value.data);
	FreeJSONValue(jsonValue);
}

void
FreeJSONObject(JSONObject *o) {
	SLM_Iterate(o->slm, _FreeObjectField, NULL);
	SLM_Free(&o->slm);
}
