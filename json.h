#ifndef JSON_H_
#define JSON_H_
#include <stdbool.h>

#include "w/d4t4-5tructur35/array_list.h"
#include "w/d4t4-5tructur35/skip_list_map.h"
#include "w/d4t4-5tructur35/string_.h"

typedef enum {
	JSON_NULL,
	JSON_INT,
	JSON_STRING,
	JSON_FLOAT,
	JSON_BOOL,
	JSON_OBJECT,
	JSON_ARRAY
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
		String str;
		float floating;
		bool boolean;
		JSONObject object;
		JSONArray array;
	};
} JSONValue;

// array getters

JSONArray
JA_Alloc();

static inline void
JA_AddValue(JSONArray*, JSONValue);

JSONValue
JA_GetValue(int, JSONArray);

JSONObject
JA_GetObject(int, JSONArray);

JSONArray
JA_GetArray(int, JSONArray);

int
JA_GetInt(int, JSONArray);

String
JA_GetString(int, JSONArray);

bool
JA_GetBoolean(int, JSONArray);

void
JA_Free(JSONArray*);

// object getters
JSONObject
JO_Alloc();

static inline void
JO_AddValue(JSONObject*, String, JSONValue);

JSONValue
JO_GetValue(char*, JSONObject);

JSONObject
JO_GetObject(char*, JSONObject);

JSONArray
JO_GetArray(char*, JSONObject);

int
JO_GetInt(char*, JSONObject);

String
JO_GetString(char*, JSONObject);

bool
JO_GetBoolean(char*, JSONObject);

void
JO_Free(JSONObject*);

// value functions
void
JV_Free(JSONValue*);

// parse functions
bool
JSON_Parse(Buffer, JSONValue*);

// encoding functions
// describe internal structure of parsed JSON, with types
Buffer
JV_Describe(JSONValue);

void
JV_DescribeToBuffer(JSONValue,Buffer*);

// encodes JSON structure to JSON string
Buffer
JV_Stringify(JSONValue);

void
JV_StringifyToBuffer(JSONValue,Buffer*);


static inline void
JA_AddValue(JSONArray *a, JSONValue v) {
	AL_Add(&a->al, &v);
}

static inline void
JO_AddValue(JSONObject *o, String s, JSONValue v) {
	SLM_Set(&o->slm, B_Wrap(s.str, s.len), B_Wrap(&v, sizeof(v)));
}
#endif
