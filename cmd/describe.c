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

	if (!ParseJSON(json, &parsedJSON)) {
		fprintf(stderr, "error parsing JSON\n");
		return -1;
	}

	// TODO: printing!

	return 0;
}

void 
printUsage() {
	printf("parses and decribes JSON file with types\n");
	printf("Usage: describe <json_file>\n");
}
