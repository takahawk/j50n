#ifndef JSON_ARRAY_H_
#define JSON_ARRAY_H_
#include <stdbool.h>

#include "d4t4-5tructur35/array_list.h"

struct _JSONObject;

typedef struct _JSONArray {
	ArrayList al;
} JSONArray;

struct _JSONObject
JA_GetObject(int, JSONArray);

JSONArray
JA_GetArray(int, JSONArray);

int
JA_GetInt(int, JSONArray);

char*
JA_GetString(int, JSONArray);

bool
JA_GetBoolean(int, JSONArray);

#endif
