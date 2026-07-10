#include "entidade.h"
#include "lancamento.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

bool entidade_inserir(sqlite3* db, const string& nome, const string& descricao) {
    const char* sql = "INSERT INTO entidade (nome, descricao) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, descricao.c_str(), -1, SQLITE_STATIC);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool entidade_excluir(sqlite3* db, int id) {
    // Bloqueia exclusao se existirem lancamentos vinculados
    const char* chk = "SELECT COUNT(*) FROM lancamento WHERE entidade_id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, chk, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    int cnt = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    if (cnt > 0) {
        cout << "Erro: Entidade possui " << cnt << " lancamento(s) vinculado(s). Exclua-os primeiro." << endl;
        return false;
    }
    const char* sql = "DELETE FROM entidade WHERE id = ?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE || sqlite3_changes(db) == 0) {
        cout << "Erro: Entidade nao encontrada." << endl;
        return false;
    }
    return true;
}

vector<Entidade> entidade_listar(sqlite3* db) {
    vector<Entidade> lista;
    const char* sql = "SELECT id, nome, descricao FROM entidade ORDER BY nome;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return lista;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Entidade e;
        e.id        = sqlite3_column_int(stmt, 0);
        e.nome      = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        e.descricao = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        lista.push_back(e);
    }
    sqlite3_finalize(stmt);
    return lista;
}

void menu_entidade(sqlite3* db) {
    char op;
    do {
        cout << "\n--- Menu Entidade ---" << endl;
        cout << "[A] Nova Entidade" << endl;
        cout << "[B] Excluir Entidade" << endl;
        cout << "[C] Visualizar Lancamentos" << endl;
        cout << "[Q] Voltar" << endl;
        cout << "Opcao: ";
        cin >> op;
        cin.ignore();
        op = (char)toupper((unsigned char)op);

        if (op == 'A') {
            string nome, desc;
            cout << "Nome da Entidade: ";
            getline(cin, nome);
            nome = trim(nome);
            if (nome.empty()) { cout << "Nome invalido." << endl; continue; }
            cout << "Descricao: ";
            getline(cin, desc);
            if (entidade_inserir(db, nome, trim(desc)))
                cout << "Entidade '" << nome << "' cadastrada com sucesso." << endl;
            else
                cout << "Erro: Nome ja existe ou falha no banco." << endl;

        } else if (op == 'B') {
            auto lista = entidade_listar(db);
            if (lista.empty()) { cout << "Nenhuma entidade cadastrada." << endl; continue; }
            cout << "\nEntidades cadastradas:" << endl;
            for (auto& e : lista)
                cout << "  [" << e.id << "] " << left << setw(25) << e.nome << e.descricao << endl;
            cout << "ID para excluir (0 cancela): ";
            int id; cin >> id; cin.ignore();
            if (id <= 0) continue;
            if (entidade_excluir(db, id))
                cout << "Entidade excluida." << endl;

        } else if (op == 'C') {
            auto lista = entidade_listar(db);
            if (lista.empty()) { cout << "Nenhuma entidade cadastrada." << endl; continue; }
            cout << "\nEntidades cadastradas:" << endl;
            for (auto& e : lista)
                cout << "  [" << e.id << "] " << e.nome << endl;
            cout << "ID da Entidade (0 cancela): ";
            int id; cin >> id; cin.ignore();
            if (id <= 0) continue;
            lancamento_visualizar(db, id);
        }
    } while (op != 'Q');
}
