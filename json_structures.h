#ifndef JSON_STRUCTURES_H_
#define JSON_STRUCTURES_H_
#include <stdbool.h>

#include "d4t4-5tructur35/array_list.h"
#include "d4t4-5tructur35/skip_list_map.h"

typedef enum {
	JSON_INT,
	JSON_STRING,
	JSON_FLOAT,
	JSON_BOOL,
	JSON_OBJECT,
	JSON_ARRAY,
	JSON_NULL
} JSONFieldType;


typedef struct {
	JSONFieldType type;
	union {
		int integer;
		char *str;
		float floating;
		bool boolean;
		struct _JSONObject* object;
		struct _JSONArray* array;
	};
} JSONField;

typedef struct {
	SkipListMap slm;
} JSONObject;

typedef struct {
	ArrayList al;
} JSONArray;

// array getters
JSONObject
JA_GetObject(int, JSONArray);

JSONArray
JA_GetArray(int, JSONArray);

int
JA_GetInt(int, JSONArray);

char*
JA_GetString(int, JSONArray);

bool
JA_GetBoolean(int, JSONArray);


// object getters
JSONObject
JO_GetObject(char*, JSONObject);

JSONArray
JO_GetArray(char*, JSONObject);

int
JO_GetInt(char*, JSONObject);

char*
JO_GetString(char*, JSONObject);

bool
JO_GetBoolean(char*, JSONObject);

#endif
