#include "lancamento.h"
#include "entidade.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <stdexcept>

using namespace std;

// ─────────────────────────────────────────────
//  Helpers internos
// ─────────────────────────────────────────────

static void linha(char c = '-', int n = 60) {
    cout << string(n, c) << endl;
}

// Coleta itens de lancamento interativamente. Encerra ao digitar '.'.
static vector<ItemLancamento> coletar_itens() {
    vector<ItemLancamento> itens;
    cout << "  (Digite '.' no campo Conta para fechar a entrada)\n";
    while (true) {
        string raw;
        cout << "  Conta: ";
        getline(cin, raw);
        raw = trim(raw);
        if (raw == ".") break;
        if (raw.empty()) continue;

        ContaInfo ci = parse_conta(raw);
        if (!valida_formato_conta(ci.conta)) {
            cout << "  Formato invalido. Exemplos validos:\n"
                 << "    ativo:banco          (debito)\n"
                 << "    a passivo:fornecedor (credito)\n";
            continue;
        }

        string sv;
        cout << "  Valor: ";
        getline(cin, sv);
        sv = trim(sv);
        double valor = 0.0;
        try {
            valor = stod(sv);
            if (valor <= 0.0) throw invalid_argument("valor nao positivo");
        } catch (...) {
            cout << "  Valor invalido. Informe um numero positivo (ex: 1500.00).\n";
            continue;
        }

        ItemLancamento item;
        item.id            = 0;
        item.lancamento_id = 0;
        item.conta         = ci.conta;
        item.tipo          = ci.tipo;
        item.valor         = valor;
        itens.push_back(item);

        cout << "  >> " << (ci.tipo == 'D' ? "DEBITO  " : "CREDITO ")
             << left << setw(30) << ci.conta
             << right << setw(12) << formata_valor(valor) << endl;
    }
    return itens;
}

// Valida partidas dobradas. Exibe erro detalhado e retorna false se desequilibrado.
static bool validar_partidas(const vector<ItemLancamento>& itens) {
    if (itens.empty()) {
        cout << "ERRO: Nenhum item informado.\n";
        return false;
    }
    double td = 0.0, tc = 0.0;
    for (auto& i : itens) {
        if (i.tipo == 'D') td += i.valor;
        else               tc += i.valor;
    }
    if (fabs(td - tc) > 0.001) {
        cout << "\nERRO: Partidas desequilibradas — lancamento nao sera persistido.\n";
        cout << "  Total Debitos : " << formata_valor(td) << endl;
        cout << "  Total Creditos: " << formata_valor(tc) << endl;
        cout << "  Diferenca     : " << formata_valor(fabs(td - tc)) << endl;
        return false;
    }
    return true;
}

// ─────────────────────────────────────────────
//  CRUD — banco de dados
// ─────────────────────────────────────────────

bool lancamento_inserir(sqlite3* db, Lancamento& l) {
    sqlite3_exec(db, "BEGIN;", nullptr, nullptr, nullptr);

    // Insere cabecalho do lancamento
    const char* sql_l = "INSERT INTO lancamento (entidade_id, data, comentario) VALUES (?,?,?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql_l, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, l.entidade_id);
    sqlite3_bind_text(stmt, 2, l.data.c_str(),        -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, l.comentario.c_str(),  -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
        cerr << "Erro ao inserir lancamento: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_finalize(stmt);
    int lanc_id = (int)sqlite3_last_insert_rowid(db);

    // Insere cada item
    const char* sql_i = "INSERT INTO item_lancamento (lancamento_id, conta, tipo, valor) VALUES (?,?,?,?);";
    for (auto& item : l.itens) {
        sqlite3_prepare_v2(db, sql_i, -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, lanc_id);
        sqlite3_bind_text(stmt, 2, item.conta.c_str(), -1, SQLITE_STATIC);
        string tipo_str(1, item.tipo);
        sqlite3_bind_text(stmt, 3, tipo_str.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 4, item.valor);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            cerr << "Erro ao inserir item: " << sqlite3_errmsg(db) << endl;
            return false;
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
    l.id = lanc_id;
    return true;
}

static bool lancamento_excluir_db(sqlite3* db, int id) {
    const char* sql = "DELETE FROM lancamento WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE && sqlite3_changes(db) > 0;
}

static bool lancamento_alterar_db(sqlite3* db, int id) {
    // Carrega cabecalho atual
    const char* sql_sel = "SELECT entidade_id, data, comentario FROM lancamento WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql_sel, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        cout << "Lancamento #" << id << " nao encontrado.\n";
        return false;
    }
    int    eid  = sqlite3_column_int(stmt, 0);
    string data = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    string com  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    sqlite3_finalize(stmt);

    cout << "Data atual [" << data << "]: ";
    string nova_data; getline(cin, nova_data); nova_data = trim(nova_data);
    if (!nova_data.empty()) {
        if (!valida_data(nova_data)) { cout << "Data invalida.\n"; return false; }
        data = nova_data;
    }

    cout << "Comentario atual [" << com << "]: ";
    string novo_com; getline(cin, novo_com);
    if (!trim(novo_com).empty()) com = trim(novo_com);

    cout << "\nRe-insira os itens do lancamento:\n";
    auto itens = coletar_itens();
    if (itens.empty()) { cout << "Nenhum item informado. Alteracao cancelada.\n"; return false; }
    if (!validar_partidas(itens)) {
        cout << "Lancamento nao alterado. Retornando ao menu.\n";
        return false;
    }

    // Atualiza tudo em transacao
    sqlite3_exec(db, "BEGIN;", nullptr, nullptr, nullptr);

    const char* del = "DELETE FROM item_lancamento WHERE lancamento_id = ?;";
    sqlite3_prepare_v2(db, del, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt); sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr); return false;
    }
    sqlite3_finalize(stmt);

    const char* upd = "UPDATE lancamento SET data=?, comentario=?, entidade_id=? WHERE id=?;";
    sqlite3_prepare_v2(db, upd, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, data.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, com.c_str(),  -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt,  3, eid);
    sqlite3_bind_int(stmt,  4, id);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt); sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr); return false;
    }
    sqlite3_finalize(stmt);

    const char* sql_i = "INSERT INTO item_lancamento (lancamento_id, conta, tipo, valor) VALUES (?,?,?,?);";
    for (auto& item : itens) {
        sqlite3_prepare_v2(db, sql_i, -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_bind_text(stmt, 2, item.conta.c_str(), -1, SQLITE_STATIC);
        string ts(1, item.tipo);
        sqlite3_bind_text(stmt, 3, ts.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 4, item.valor);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt); sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr); return false;
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
    return true;
}

// ─────────────────────────────────────────────
//  Visualizacao
// ─────────────────────────────────────────────

void lancamento_visualizar(sqlite3* db, int entidade_id) {
    string sql =
        "SELECT l.id, e.nome, l.data, l.comentario, "
        "       il.conta, il.tipo, il.valor "
        "FROM lancamento l "
        "JOIN entidade e ON e.id = l.entidade_id "
        "JOIN item_lancamento il ON il.lancamento_id = l.id ";
    if (entidade_id > 0)
        sql += "WHERE l.entidade_id = " + to_string(entidade_id) + " ";
    sql += "ORDER BY l.id, il.id;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Erro na consulta.\n"; return;
    }

    int  cur_id = -1;
    bool found  = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        found   = true;
        int lid = sqlite3_column_int(stmt, 0);
        if (lid != cur_id) {
            cur_id = lid;
            linha();
            cout << "Lancamento #" << lid
                 << "  Entidade: " << sqlite3_column_text(stmt, 1)
                 << "  Data: "     << sqlite3_column_text(stmt, 2) << endl;
            cout << "Comentario: "  << sqlite3_column_text(stmt, 3) << endl;
            cout << left << setw(35) << "Conta" << setw(10) << "Tipo"
                 << right << setw(14) << "Valor" << endl;
            linha('-', 59);
        }
        string tipo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        cout << left  << setw(35) << sqlite3_column_text(stmt, 4)
             << setw(10) << (tipo == "D" ? "DEBITO" : "CREDITO")
             << right << setw(14) << formata_valor(sqlite3_column_double(stmt, 6)) << endl;
    }
    sqlite3_finalize(stmt);

    if (!found)
        cout << "Nenhum lancamento encontrado.\n";
    else
        linha();
}

// ─────────────────────────────────────────────
//  Menu
// ─────────────────────────────────────────────

void menu_lancamento(sqlite3* db) {
    char op;
    do {
        cout << "\n--- Menu Lancamentos ---\n"
             << "[A] Novo Lancamento\n"
             << "[B] Alterar Lancamento\n"
             << "[C] Excluir Lancamento\n"
             << "[D] Visualizar Lancamentos\n"
             << "[Q] Voltar\n"
             << "Opcao: ";
        cin >> op;
        cin.ignore();
        op = (char)toupper((unsigned char)op);

        // ── [A] Novo Lancamento ───────────────────────────
        if (op == 'A') {
            auto entidades = entidade_listar(db);
            if (entidades.empty()) {
                cout << "Nenhuma entidade cadastrada. Cadastre uma entidade primeiro.\n";
                continue;
            }
            cout << "\nEntidades disponíveis:\n";
            for (auto& e : entidades)
                cout << "  [" << e.id << "] " << e.nome << "\n";
            cout << "ID da Entidade: ";
            int eid; cin >> eid; cin.ignore();

            Lancamento l;
            l.id          = 0;
            l.entidade_id = eid;

            cout << "Data da Operacao (YYYY-MM-DD): ";
            getline(cin, l.data);
            l.data = trim(l.data);
            if (!valida_data(l.data)) { cout << "Data invalida.\n"; continue; }

            cout << "Comentario: ";
            getline(cin, l.comentario);
            l.comentario = trim(l.comentario);

            cout << "\nItens do Lancamento:\n";
            l.itens = coletar_itens();

            if (!validar_partidas(l.itens)) {
                cout << "Lancamento descartado. Retornando ao menu.\n";
                continue;
            }
            if (lancamento_inserir(db, l))
                cout << "Lancamento #" << l.id << " persistido com sucesso.\n";
            else
                cout << "Erro ao persistir lancamento.\n";

        // ── [B] Alterar Lancamento ────────────────────────
        } else if (op == 'B') {
            lancamento_visualizar(db);
            cout << "ID do Lancamento a alterar (0 cancela): ";
            int id; cin >> id; cin.ignore();
            if (id <= 0) continue;
            if (lancamento_alterar_db(db, id))
                cout << "Lancamento #" << id << " alterado com sucesso.\n";

        // ── [C] Excluir Lancamento ────────────────────────
        } else if (op == 'C') {
            lancamento_visualizar(db);
            cout << "ID do Lancamento a excluir (0 cancela): ";
            int id; cin >> id; cin.ignore();
            if (id <= 0) continue;
            cout << "Confirma exclusao do lancamento #" << id << "? (s/N): ";
            char c; cin >> c; cin.ignore();
            if (tolower((unsigned char)c) == 's') {
                if (lancamento_excluir_db(db, id))
                    cout << "Lancamento #" << id << " excluido.\n";
                else
                    cout << "Lancamento nao encontrado.\n";
            }

        // ── [D] Visualizar Lancamentos ────────────────────
        } else if (op == 'D') {
            lancamento_visualizar(db);
        }
    } while (op != 'Q');
}
