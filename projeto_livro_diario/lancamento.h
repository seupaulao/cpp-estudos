#pragma once
#include <string>
#include <vector>
#include <sqlite3.h>

using namespace std;

struct ItemLancamento {
    int    id;
    int    lancamento_id;
    string conta;
    char   tipo;    // 'D' = debito | 'C' = credito
    double valor;
};

struct Lancamento {
    int                    id;
    int                    entidade_id;
    string                 data;
    string                 comentario;
    vector<ItemLancamento> itens;
};

// Persiste lancamento + itens em transacao. Retorna true se bem-sucedido.
bool lancamento_inserir(sqlite3* db, Lancamento& l);

// Exibe lançamentos. Se entidade_id > 0, filtra pela entidade.
void lancamento_visualizar(sqlite3* db, int entidade_id = -1);

// Menu interativo de lancamentos
void menu_lancamento(sqlite3* db);
