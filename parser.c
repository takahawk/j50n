#include "json.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

#include "d4t4-5tructur35/array_list.h"
#include "d4t4-5tructur35/buffer.h"
#include "d4t4-5tructur35/skip_list_map.h"

JSONValue*
ParseJSON(Buffer buffer) {
	char *str = buffer.data;
	size_t len = buffer.len;
	enum {
		START, 
		OBJECT, 
		KEY, 
		COLON, 
		BEFORE_VALUE, 
		VALUE,
       		STRING_VALUE,
		FIELD_END,
	} state = START;

	size_t mark = 0;
	Buffer key;
	Buffer value;

	for (int i = 0; i < len; i++) {
		char c = str[i];
		switch (state) {
		case START:
			if (isspace(c))
				continue;
			switch (c) {
			case '{':
				state = OBJECT;
				continue;
			default:
				// TODO: error handling!
				fprintf(stderr, "Unexpected symbol in the beginning: %c\n", str[i]);
				goto end;
			}

		case OBJECT:
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
				state = VALUE;
				continue;
			}
		case STRING_VALUE:
			switch (c) {
			case '\n':
				fprintf(stderr, "Unexpected newline inside quotes\n");
				goto end;
			case '"':
				value = AsBuffer(str + mark, i - mark);
				state = FIELD_END;
				// FALLTHROUGH
			default:
				continue;
			}
		case FIELD_END:
			if (isspace(c))
				continue;
			switch (c) {
			case ',':
				state = OBJECT;
			}

		}
	}

end:
	return NULL;
}
