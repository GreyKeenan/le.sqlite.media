
#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

const char* DATABASE = "media.db";

int main(int argc, char **argv) {
	printf("\n| Running program with %d parameters ... |\n\n", argc);

	sqlite3 *db = NULL;
	char *zErrMsg = NULL;
	int rc = 0;

	//rc = sqlite3_open_v2(DATABASE, &db, SQLITE_OPEN_READWRITE, ""); //https://sqlite.org/c3ref/open.html
	rc = sqlite3_open(DATABASE, &db);
	if (rc) {
		printf("| Unable to open database \"%s\". Terminating. |\n\n", DATABASE);
		exit(1);
	}


	char *query = "SELECT id, name, data FROM testdb;";
	sqlite3_stmt *statement;

	sqlite3_prepare_v2( //https://sqlite.org/c3ref/prepare.html
		db,
		query,
		-1, //length of char[], negative for null terminated string
		&statement,
		NULL
	);
	if (rc != SQLITE_OK) {
		printf("| Unable to parse query. Terminating. |\n\n");
		sqlite3_close(db);
		exit(1);
	}

	while (1) {
		rc = sqlite3_step(statement); //https://sqlite.org/c3ref/step.html
		switch (rc) {
			case SQLITE_ROW:
				printf("%lld | %s | %d\n", sqlite3_column_int64(statement, 0), sqlite3_column_text(statement, 1), sqlite3_column_int(statement, 2));
				break;
			case SQLITE_DONE:
				goto endloop;
				break;
			case SQLITE_MISUSE:
				printf("| MISUSE error from sqlite3_step(). Terminating. |\n\n");
				exit(1);
				break;
			case SQLITE_ERROR:
				printf("| Error from sqlite3_step(). Terminating. |\n\n");
				exit(1);
				break;
			default:
				printf("| Unexpected sqlite3_step return value: \"%d\". Terminating. |\n\n", rc);
				exit(1);
				break;
				//doesnt handle SQLITE_BUSY
		}
		continue;
		endloop:
			break;
	}
	sqlite3_finalize(statement);
	statement = NULL;

	sqlite3_close(db);
	db = NULL;

	printf("\n| ... ending program. |\n\n");
	return 0;
}
