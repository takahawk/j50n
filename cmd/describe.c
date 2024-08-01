#include <stdio.h>

#include "../ut1l5/files.h"

#include "json.h"

void 
printUsage();

int main(int argc, char **argv) {
	if (argc < 2) {
		printUsage();
		return -1;
	}

	char* filename = argv[1];

	Buffer json = uF_ReadFileByName(filename);
	JSONValue parsedJSON;

	if (!JSON_Parse(json, &parsedJSON)) {
		fprintf(stderr, "error parsing JSON\n");
		return -1;
	}

	String described = S_From(JV_Describe(parsedJSON));
	printf(described.str);

	// TODO: memory cleanup!
	return 0;
}

void 
printUsage() {
	printf("parses and decribes JSON file with types\n");
	printf("Usage: describe <json_file>\n");
}
