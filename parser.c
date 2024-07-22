#include "json.h"

#include <stddef.h>
#include <stdio.h>

JSONObject*
ParseJSONObject(Buffer buffer) {
	char *str = buffer.data;
	size_t len = buffer.len;
	enum {START, OBJECT, KEY, COLON } state = START;

	size_t mark = 0;
	Buffer key;

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
				goto end;
			}

		case OBJECT:
			switch (str[i]) {
			case ' ':
			case '\n':
			case '\t':
				continue;
			case '"':
				state = FIELD_NAME;
				mark = i + 1;
				continue;
			default:
				fprintf(stderr, "Unexpected symbol: %c; expected \"\n", str[i]);
				goto end;
			}

		case KEY:
			switch (str[i]) {
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
			switch (str[i]) {
			case ' ':
			case '\t':
			case '\n':
				continue;
			case ':':
				// TODO:
			}
		}
	}

end:
}

JSONArray*
ParseJSONArray(Buffer) {
}
