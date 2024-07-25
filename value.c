#include "json.h"

#include <stdlib.h>

void
FreeJSONValue(JSONValue* value) {
	switch (value->type) {
	case JSON_OBJECT:
		FreeJSONObject(&value->object);
		return;
	case JSON_ARRAY:
		FreeJSONArray(&value->array);
		return;
	case JSON_STRING:
		free(value->str);
		return;
	default:
		// do nothing
	}
}

void
JV_Describe(JSONValue value, Buffer* buffer) {
	// TODO:
	switch (value.type) {
	}
}

// encodes JSON structure to JSON string
void
JV_Stringify(JSONValue value, Buffer* buffer) {
	// TODO:
	switch (value.type) {
	}
}
