#ifndef JSON_PARSER_H_
#define JSON_PARSER_H_

#include "json_array.h"
#include "json_object.h"

JSONObject*
ParseJSONObject(Buffer);

JSONArray*
ParseJSONArray(Buffer);

#endif
