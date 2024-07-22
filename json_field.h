#ifndef JSON_FIELD_H_
#define JSON_FIELD_H_

#include <stdbool.h>

struct _JSONObject;
struct _JSONArray;

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

#endif
