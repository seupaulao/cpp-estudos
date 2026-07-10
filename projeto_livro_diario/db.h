#pragma once
#include <string>
#include <sqlite3.h>

using namespace std;

sqlite3* db_open(const string& path);
void     db_close(sqlite3* db);
void     db_init_schema(sqlite3* db);
