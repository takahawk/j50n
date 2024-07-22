#include "json.h"

#include <stddef.h>
#include <stdio.h>

JSONObject*
ParseJSONObject(Buffer buffer) {
	char *str = buffer.data;
	size_t len = buffer.len;
	enum {START, OBJECT, FIELD_NAME } state = START;

	for (int i = 0; i < len; i++) {
		switch (state) {
		case START:
			switch (str[i]) {
			case ' ':
			case '\n':
			case '\t':
				continue;
			case '{':
				state = OBJECT;
				continue;
			default:
				// TODO: error handling!
				fprintf(stderr, "Unexpected symbol in the beginning: %c\n", str[i]);
				return NULL;
			}

		case OBJECT:
			switch (str[i]) {
			case ' ':
			case '\n':
			case '\t':
				continue;
			case '"':
				state = FIELD_NAME;
				continue;
			default:
				fprintf(stderr, "Unexpected symbol: %c; expected \"\n", str[i]);
				return NULL;
			}

		case FIELD_NAME:
			switch (str[i]) {
			}
		}
	}
}

JSONArray*
ParseJSONArray(Buffer) {
}
