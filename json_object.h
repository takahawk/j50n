#ifndef JSON_OBJECT_H_
#define JSON_OBJECT_H_
#include "d4t4-5tructur35/skip_list_map.h"
struct _JSONArray;

typedef struct _JSONObject {
	SkikListMap slm;
} JSONObject;

JSONObject
JO_GetObject(char*, JSONObject);

_JSONArray
JO_GetArray(char*, JSONObject);

int
JO_GetInt(char*, JSONObject);

char*
JO_GetString(char*, JSONObject);

bool
JO_GetBoolean(char*, JSONObject);


#endif
