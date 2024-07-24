#include "json.h"

#include <ctype.h>
#include <math.h>
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

static inline void
_AppendToTop(ArrayList stack, Buffer key, JSONValue jsonValue) {
	// we assume that stack is not empty at this stage
	JSONValue top = _Peek(stack);
	if (top.type == JSON_OBJECT) {
		Buffer value = AsBuffer(&jsonValue, sizeof(JSONValue));
		SLM_Set(&top.object.slm, key, value);
	} else {
		// array
		AL_Add(&top.array.al, &jsonValue);  
	}
}

static inline bool
_isInteger(char *str, size_t len) {
	if (len == 0)
		return false;
	int i = 0;
	if (str[0] == '-')
		i++;

	for (; i < len; i++)
		if (!isdigit(str[i]))
			return false;

	return true;
}

static inline int
_ParseInt(char *str, int len) {
	int result = 0;
	for (int i = 0; i < len; i++) {
		// we assume that check is already done and we have correct
		// value here
		result *= 10;
		result += str[i] - 48;
	}

	return result;
}

static inline bool
_isFloating(char *str, size_t len) {
	// TODO: e notation
	bool dotFound = false;
	int i = 0;
	if (str[0] == '-')
		i++;
	for (; i < len; i++) {
		if (str[i] == '.') {
			if (dotFound)
				return false;
			dotFound = true;
		}
		if (!isdigit(str[i]))
			return false;
	}

	return true;
}

static inline float
_ParseFloat(char *str, size_t len) {
	int intPart = 0, fractPart = 0;
	
	size_t i = 0;

	for (; i < len; i++) {
		// we assume that check is already done and we have correct
		// value here
		if (str[i] == '.')
			break;
		intPart *= 10;
		intPart += str[i] - 48;
	}

	int point = i;
	
	for (i = i + 1; i < len; i++) {
		fractPart *= 10;
		fractPart += str[i] - 48;
	}

	return intPart + (float) fractPart * pow(0.1, len - point);
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

				_AppendToTop(stack, key, value);

				state = FIELD_END;
				// FALLTHROUGH
			default:
				continue;
			}
		case VALUE:
			if (isalnum(c) || c == '.')
				continue;

			bool valueFound = false;
			JSONValue value;
			// is it bool value?
			if (strncmp(str + mark, "true", 4) == 0) {
				value = (JSONValue) {
					.type = JSON_BOOL,
					.boolean = true
				};
				valueFound = true;
			}

			if (strncmp(str + mark, "false", 5) == 0) {
				value = (JSONValue) {
					.type = JSON_BOOL,
					.boolean = false
				};
				valueFound = true;
			}

			// is it null?
			if (strncmp(str + mark, "null", 4) == 0) {
				value = (JSONValue) {
					.type = JSON_NULL,
					.integer = 0,
				};
				valueFound = true;
			}

			// is it integer?
			if (_isInteger(str + mark, i - mark)) {
				
				value = (JSONValue) {
					.type = JSON_INT,
					.integer = _ParseInt(str + mark, i - mark)
				};
				valueFound = true;
			}

			// is it float 
			if (_isFloating(str + mark, i - mark)) {
				
				value = (JSONValue) {
					.type = JSON_FLOAT,
					.floating = _ParseFloat(str + mark, i - mark)
				};
				valueFound = true;
			}

			if (!valueFound) {
				fprintf(stderr, "invalid value: %.*s\n", i - mark, str + mark);
				goto end;

			}

			if (AL_IsEmpty(stack)) {
				// shouldn't happen at all
				printf("stack is empty at VALUE state\n");
				goto end;
			}

			_AppendToTop(stack, key, value);
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
