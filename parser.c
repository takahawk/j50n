#include "json.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "d4t4-5tructur35/array_list.h"
#include "d4t4-5tructur35/buffer.h"
#include "d4t4-5tructur35/skip_list_map.h"

static inline void
_Push(ArrayList *stack, JSONValue value) {
	AL_Add(stack, &value);	
}

static inline JSONValue
_Peek(ArrayList stack) {
	return *((JSONValue*) AL_Get(&stack, stack.len - 1));
}

static inline JSONValue
_Pop(ArrayList *stack) {
	JSONValue value = _Peek(*stack);
	AL_RemoveAt(stack, stack->len - 1);
	return value;
}

JSONValue*
ParseJSON(Buffer buffer) {
	char *str = buffer.data;
	size_t len = buffer.len;
	enum {
		START, 
		BEFORE_KEY,
		KEY, 
		COLON, 
		BEFORE_VALUE, 
		VALUE,
       		STRING_VALUE,
		FIELD_END,
	} state = START;

	ArrayList stack = AllocArrayList(sizeof(JSONValue), 2);
	size_t mark = 0;
	Buffer key;

	for (int i = 0; i < len; i++) {
		char c = str[i];
		switch (state) {
		case START:
			if (isspace(c))
				continue;
			switch (c) {
			case '{':
				JSONObject object = AllocJSONObject();
				JSONValue value = {
					.type = JSON_OBJECT,
					.object = object,
				};

				_Push(&stack, value);
				state = BEFORE_KEY;
				continue;
			case '[':
				JSONArray array = AllocJSONArray();
				value = (JSONValue) {
					.type = JSON_ARRAY,
					.array = array
				};
				state = BEFORE_VALUE;
				continue;
			default:
				fprintf(stderr, "Unexpected symbol in the beginning: %c\n", str[i]);
				goto end;
			}

		case BEFORE_KEY:
			if (isspace(c))
				continue;
			switch (c) {
			case '"':
				state = KEY;
				mark = i + 1;
				continue;
			default:
				fprintf(stderr, "Unexpected symbol: %c; expected \"\n", str[i]);
				goto end;
			}

		case KEY:
			switch (c) {
			case '\n':
				fprintf(stderr, "Unexpected newline inside quotes\n");
				goto end;
			case '"':
				key = AsBuffer(str + mark, i - mark);
				state = COLON;
				// FALLTHROUGH
			default:
				continue;
			}
		case COLON:
			if (isspace(c))
				continue;
			switch (c) {
			case ':':
				state = BEFORE_VALUE;
				continue;
			default:
				fprintf(stderr, "Unexpected symbol: %c; colon (:) expected\n");
				goto end;
			}
		case BEFORE_VALUE:
			if (isspace(c))
				continue;
			switch (c) {
			case '"':
				state = STRING_VALUE;
				continue;
			case '{':
				// TODO: object, recursive call
				continue;
			case '[':
				// TODO: array, function call
				continue;
			case ',':
				fprintf(stderr, "Unexpected comma(,); field value expected\n");
				goto end;
			default:
				mark = i;
				state = VALUE;
				continue;
			}
		case STRING_VALUE:
			switch (c) {
			case '\n':
				fprintf(stderr, "Unexpected newline inside quotes\n");
				goto end;
			case '"':
				JSONValue value = {
					.type = JSON_STRING,
					.str = strndup(str + mark, i - mark)
				};

				JSONValue top = _Peek(stack);
				if (top.type == JSON_OBJECT) {
					Buffer value = AsBuffer(&value, sizeof(JSONValue));
					SLM_Set(&top.object.slm, key, value);
				} else {
					// array
					AL_Add(&top.array.al, &value);  
				}

				state = FIELD_END;
				// FALLTHROUGH
			default:
				continue;
			}
		case VALUE:
			if (isalnum(c) || c == '.')
				continue;

			
			switch (c) {
			case ',':
			}
		case FIELD_END:
			if (isspace(c))
				continue;
			switch (c) {
			case ',':
				// TODO:
			}

		}
	}

end:
	// TODO: free all objects, arrays and strings in stack!
	FreeArrayList(&stack);
	return NULL;
}
