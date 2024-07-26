#include "json.h"

#include <stdlib.h>

#include "d4t4-5tructur35/buffer.h"
#include "d4t4-5tructur35/resizable_buffer.h"
#include "d4t4-5tructur35/string_.h"

#define JSON_BUFFER_CAPACITY 1000

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
	ResizableBuffer rb = RB_Create(JSON_BUFFER_CAPACITY);
	switch (value.type) {
	case JSON_STRING:
		RB_Append(&rb, S_As("(string) "));
		
		//TODO: complete
	}
}

// encodes JSON structure to JSON string
void
JV_Stringify(JSONValue value, Buffer* buffer) {
	// TODO:
	switch (value.type) {
	}
}
