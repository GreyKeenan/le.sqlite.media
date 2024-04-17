
#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

const char* DATABASE = "../media.db";

int main(int argc, char **argv) {
	printf("\n| Running program with %d parameters ... |\n\n", argc);

	sqlite3 *db = NULL;
	char *zErrMsg = 0;
	int rc = 0;

	rc = sqlite3_open_v2(DATABASE, &db, SQLITE_OPEN_READWRITE, ""); //https://sqlite.org/c3ref/open.html
	if (rc) {
		printf("| Unable to open database. Terminating. |\n\n");
		exit(1);
	}



	sqlite3_close(db);

	printf("\n| ... ending program. |\n\n");
	return 0;
}
