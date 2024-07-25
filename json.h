#ifndef JSON_H_
#define JSON_H_
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
} JSONValueType;


typedef struct {
	SkipListMap slm;
} JSONObject;

typedef struct {
	ArrayList al;
} JSONArray;

typedef struct {
	JSONValueType type;
	union {
		int integer;
		char *str;
		float floating;
		bool boolean;
		JSONObject object;
		JSONArray array;
	};
} JSONValue;

// array getters

JSONArray
AllocJSONArray();

JSONValue
JA_GetValue(int, JSONArray);

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

void
FreeJSONArray(JSONArray*);

// object getters
JSONObject
AllocJSONObject();

JSONValue
JO_GetValue(char*, JSONObject);

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

void
FreeJSONObject(JSONObject*);

// value functions
void
FreeJSONValue(JSONValue*);

// parse functions
bool
ParseJSON(Buffer, JSONValue*);

// encoding functions
// describe internal structure of parsed JSON, with types
void
JV_Describe(JSONValue,Buffer*);

// encodes JSON structure to JSON string
void
JV_Stringify(JSONValue,Buffer*);
#endif
