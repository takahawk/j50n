#include "json.h"

#include <stdarg.h>
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
		S_Free(&value->str);
		return;
	default:
		return;
		// do nothing for other types
	}
}


static void
_DescribeToResizableBuffer(JSONValue value, ResizableBuffer* rb, int depth);

typedef struct {
	bool isFirst;
	int depth;
	ResizableBuffer *rb;
} _CB_Args;

static void
_CB_AL_Describe(size_t index, void* value, void* args) {
	_CB_Args* cbArgs = (_CB_Args*) args;
	ResizableBuffer *rb = (ResizableBuffer*) cbArgs->rb;
		
	if (!cbArgs->isFirst) {
		RB_Append(rb, ", ");
		cbArgs->isFirst = false;
	}

	RB_Append(rb, "\n");
	for (int i = 0; i < cbArgs->depth; i++) {
		RB_Append(rb, "\t");
	}

	JSONValue jsonValue = *((JSONValue*) value);
	_DescribeToResizableBuffer(jsonValue, rb, cbArgs->depth + 1);
}

static void
_CB_SLM_Describe(Buffer key, Buffer value, void* args) {
	_CB_Args* cbArgs = (_CB_Args*) args;
	ResizableBuffer *rb = (ResizableBuffer*) cbArgs->rb;
		
	if (!cbArgs->isFirst) {
		RB_Append(rb, ", ");
		cbArgs->isFirst = false;
	}

	RB_Append(rb, "\n");
	for (int i = 0; i < cbArgs->depth; i++) {
		RB_Append(rb, "\t");
	}
	RB_Append(rb, "\"");
	RB_Append(rb, key);
	RB_Append(rb, "\"");
	RB_Append(rb, ": ");

	JSONValue jsonValue = *((JSONValue*) value.data);
	_DescribeToResizableBuffer(jsonValue, rb, cbArgs->depth + 1);
}

static void
_DescribeToResizableBuffer(JSONValue value, ResizableBuffer* rb, int depth) {
	switch (value.type) {
	case JSON_STRING:
		RB_Append(rb, "(string) ");
		RB_Append(rb, "\"");
		RB_Append(rb, value.str);
		RB_Append(rb, "\"");
		break;
	case JSON_INT:
		RB_Append(rb, "(int) ");
		RB_Append(rb, S_From(value.integer));
		break;
	case JSON_FLOAT:
		RB_Append(rb, "(float) ");
		RB_Append(rb, S_From(value.floating));
		break;
	case JSON_BOOL:
		RB_Append(rb, "(bool) ");
		RB_Append(rb, S_From(value.boolean));
		break;
	case JSON_OBJECT:
		RB_Append(rb, "(object) {");
		_CB_Args args = {
			.isFirst = true,
			.rb = rb,
			.depth = depth
		};
		SLM_Iterate(value.object.slm, _CB_SLM_Describe, &args);
		RB_Append(rb, "}\n");
		break;
	case JSON_ARRAY:
		RB_Append(rb, "(array) {");
		args = (_CB_Args) {
			.isFirst = true,
			.rb = rb,
			.depth = depth
		};
		AL_Iterate(value.array.al, _CB_AL_Describe, &args);
		RB_Append(rb, "}\n");
		break;
	case JSON_NULL:
		RB_Append(rb, "null");
		break;
	}
}


Buffer
JV_Describe(JSONValue value) {
	ResizableBuffer rb = RB_Create(JSON_BUFFER_CAPACITY);
	_DescribeToResizableBuffer(value, &rb, 0);

	return RB_ToBuffer(&rb);
}

void
JV_DescribeToBuffer(JSONValue value, Buffer* buffer) {
	*buffer = JV_Describe(value);
}


// encodes JSON structure to JSON string
Buffer
JV_Stringify(JSONValue value) {
	// TODO:
}

void
JV_StringifyToBuffer(JSONValue value, Buffer *buffer) {
	// TODO:
}
