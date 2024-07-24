#include "json.h"

void
FreeJSONValue(JSONValue* value) {
	switch (value.type) {
	case JSON_OBJECT:
		FreeJSONObject(value.object);
		return;
	case JSON_ARRAY:
		FreeJSONArray(value.array);
		return;
	default:
		// do nothing
	}
}
