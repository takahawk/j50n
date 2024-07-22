#include "json_object.h"

#include <stdbool.h>
#include <string.h>

#include "d4t4-5tructur35/buffer.h"
#include "d4t4-5tructur35/skip_list_map.h"
#include "json_array.h"

// TODO: typecheck!

static void*
_Get(JSONObject o, char* key) {
	int keyLen = strlen(key);
	Buffer value = SLM_Get(o.slm, AsBuffer(key, keyLen));
	return value.data;
}

JSONObject
JO_GetObject(char* key, JSONObject o) {
	return *((JSONObject*) _Get(o, key));
}

JSONArray
JO_GetArray(char* key, JSONObject o) {
	return *((JSONArray*) _Get(o, key));
}

int
JO_GetInt(char* key, JSONObject o) {
	return *((int*) _Get(o, key));
}

char*
JO_GetString(char* key, JSONObject o) {
	return *((char**) _Get(o, key));
}

bool
JO_GetBoolean(char* key, JSONObject o) {
	return *((bool*) _Get(o, key));
}
