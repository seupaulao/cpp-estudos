#include "db.h"
#include "entidade.h"
#include "lancamento.h"
#include "relatorio.h"
#include <iostream>
#include <cctype>

using namespace std;

int main() {
    sqlite3* db = db_open("livro_diario.db");
    db_init_schema(db);

    char op;
    do {
        cout << "\n============================\n"
             << "      LIVRO DIARIO\n"
             << "============================\n"
             << "[A] Cadastrar Entidade\n"
             << "[B] Cadastrar Lancamentos\n"
             << "[C] Relatorios\n"
             << "[Q] Sair\n"
             << "Opcao: ";
        cin >> op;
        cin.ignore();
        op = (char)toupper((unsigned char)op);
        switch (op) {
            case 'A': menu_entidade(db);   break;
            case 'B': menu_lancamento(db); break;
            case 'C': menu_relatorio(db);  break;
            case 'Q': cout << "Saindo...\n"; break;
            default:  cout << "Opcao invalida.\n";
        }
    } while (op != 'Q');

    db_close(db);
    return 0;
}
