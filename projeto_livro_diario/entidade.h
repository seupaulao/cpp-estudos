#pragma once
#include <string>
#include <vector>
#include <sqlite3.h>

using namespace std;

struct Entidade {
    int    id;
    string nome;
    string descricao;
};

bool             entidade_inserir(sqlite3* db, const string& nome, const string& descricao);
bool             entidade_excluir(sqlite3* db, int id);
vector<Entidade> entidade_listar(sqlite3* db);
void             menu_entidade(sqlite3* db);
