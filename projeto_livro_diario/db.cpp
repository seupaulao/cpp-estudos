#include "db.h"
#include <iostream>
#include <cstdlib>

using namespace std;

sqlite3* db_open(const string& path) {
    sqlite3* db = nullptr;
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        cerr << "Erro ao abrir banco de dados: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }
    // Habilita suporte a chaves estrangeiras (desativado por padrao no SQLite3)
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
    return db;
}

void db_close(sqlite3* db) {
    if (db) sqlite3_close(db);
}

void db_init_schema(sqlite3* db) {
    const char* ddl = R"(
        CREATE TABLE IF NOT EXISTS entidade (
            id        INTEGER PRIMARY KEY AUTOINCREMENT,
            nome      TEXT    NOT NULL,
            descricao TEXT    DEFAULT '',
            UNIQUE(nome)
        );

        CREATE TABLE IF NOT EXISTS lancamento (
            id          INTEGER PRIMARY KEY AUTOINCREMENT,
            entidade_id INTEGER NOT NULL,
            data        TEXT    NOT NULL,
            comentario  TEXT    DEFAULT '',
            FOREIGN KEY (entidade_id) REFERENCES entidade(id)
        );

        CREATE TABLE IF NOT EXISTS item_lancamento (
            id            INTEGER PRIMARY KEY AUTOINCREMENT,
            lancamento_id INTEGER NOT NULL,
            conta         TEXT    NOT NULL,
            tipo          TEXT    NOT NULL CHECK(tipo IN ('D','C')),
            valor         REAL    NOT NULL,
            FOREIGN KEY (lancamento_id) REFERENCES lancamento(id) ON DELETE CASCADE
        );
    )";

    char* errmsg = nullptr;
    if (sqlite3_exec(db, ddl, nullptr, nullptr, &errmsg) != SQLITE_OK) {
        cerr << "Erro ao criar schema: " << errmsg << endl;
        sqlite3_free(errmsg);
        exit(1);
    }
}
