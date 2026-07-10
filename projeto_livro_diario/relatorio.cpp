#include "relatorio.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <sqlite3.h>
#include <string>

using namespace std;

// ─────────────────────────────────────────────
//  Helpers internos
// ─────────────────────────────────────────────

static void cabecalho(const string& titulo) {
    cout << "\n" << string(60, '=') << "\n";
    int pad = (60 - (int)titulo.size()) / 2;
    cout << string(pad, ' ') << titulo << "\n";
    cout << string(60, '=') << "\n";
}

// Imprime o saldo por conta de um grupo (filtro por prefixo).
// saldo_credito=true  => saldo = credito - debito  (contas de passivo/receita)
// saldo_credito=false => saldo = debito  - credito (contas de ativo/despesa)
// Retorna o total do grupo.
static double imprimir_grupo(sqlite3* db,
                              const string& prefixo,
                              const string& label,
                              bool saldo_credito) {
    // Parametros sao strings literais internas — nao ha risco de SQL injection
    string sql =
        "SELECT conta, "
        "SUM(CASE WHEN tipo='D' THEN valor ELSE 0 END) AS td, "
        "SUM(CASE WHEN tipo='C' THEN valor ELSE 0 END) AS tc "
        "FROM item_lancamento "
        "WHERE conta LIKE '" + prefixo + "%' "
        "GROUP BY conta ORDER BY conta;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return 0.0;

    cout << "\n  " << label << ":\n";
    cout << "  " << left  << setw(38) << "Conta"
                 << right << setw(16) << "Saldo" << "\n";
    cout << "  " << string(54, '-') << "\n";

    double total = 0.0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string conta = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        double td    = sqlite3_column_double(stmt, 1);
        double tc    = sqlite3_column_double(stmt, 2);
        double saldo = saldo_credito ? (tc - td) : (td - tc);
        total += saldo;
        cout << "  " << left  << setw(38) << conta
                     << right << setw(16) << formata_valor(saldo) << "\n";
    }
    sqlite3_finalize(stmt);

    cout << "  " << string(54, '-') << "\n";
    cout << "  " << left  << setw(38) << ("Total " + label)
                 << right << setw(16) << formata_valor(total) << "\n";
    return total;
}

// ─────────────────────────────────────────────
//  Relatorio: Balanço Patrimonial
// ─────────────────────────────────────────────

void relatorio_balanco(sqlite3* db) {
    cabecalho("BALANCO PATRIMONIAL");

    double ativo   = imprimir_grupo(db, "ativo",       "ATIVO",              false);
    double passivo = imprimir_grupo(db, "passivo",     "PASSIVO",            true);
    double pl      = imprimir_grupo(db, "patrimonio",  "PATRIMONIO LIQUIDO", true);

    double total_passivo_pl = passivo + pl;
    cout << "\n  " << string(54, '=') << "\n";
    cout << "  " << left << setw(38) << "TOTAL ATIVO"
                 << right << setw(16) << formata_valor(ativo) << "\n";
    cout << "  " << left << setw(38) << "TOTAL PASSIVO + PL"
                 << right << setw(16) << formata_valor(total_passivo_pl) << "\n";
    cout << "  " << string(54, '=') << "\n";

    double diff = ativo - total_passivo_pl;
    if (fabs(diff) < 0.01)
        cout << "  Balanco EQUILIBRADO.\n";
    else
        cout << "  ATENCAO: Balanco desequilibrado. Diferenca: " << formata_valor(diff) << "\n";
}

// ─────────────────────────────────────────────
//  Relatorio: DRE
// ─────────────────────────────────────────────

void relatorio_dre(sqlite3* db) {
    cabecalho("DEMONSTRACAO DO RESULTADO DO EXERCICIO (DRE)");

    double receita = imprimir_grupo(db, "receita", "RECEITAS", true);
    double despesa = imprimir_grupo(db, "despesa", "DESPESAS", false);

    double resultado = receita - despesa;
    cout << "\n  " << string(54, '=') << "\n";
    cout << "  " << left  << setw(38) << "RESULTADO DO EXERCICIO"
                 << right << setw(16) << formata_valor(resultado) << "\n";
    cout << "  " << string(54, '=') << "\n";
    cout << "  " << (resultado >= 0 ? "Resultado: LUCRO" : "Resultado: PREJUIZO") << "\n";
}

// ─────────────────────────────────────────────
//  Menu Relatorios
// ─────────────────────────────────────────────

void menu_relatorio(sqlite3* db) {
    char op;
    do {
        cout << "\n--- Menu Relatorios ---\n"
             << "[A] Balanco\n"
             << "[B] DRE\n"
             << "[Q] Voltar\n"
             << "Opcao: ";
        cin >> op;
        cin.ignore();
        op = (char)toupper((unsigned char)op);
        if      (op == 'A') relatorio_balanco(db);
        else if (op == 'B') relatorio_dre(db);
    } while (op != 'Q');
}
