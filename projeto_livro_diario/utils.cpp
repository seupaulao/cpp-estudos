#include "utils.h"
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Prefixo "a " na frente da conta indica credito; sem prefixo indica debito.
ContaInfo parse_conta(const string& raw) {
    ContaInfo ci;
    string s = trim(raw);
    if (s.size() >= 2 && s[0] == 'a' && s[1] == ' ') {
        ci.tipo  = 'C';
        ci.conta = trim(s.substr(2));
    } else {
        ci.tipo  = 'D';
        ci.conta = s;
    }
    return ci;
}

// Formato valido: letras minusculas/digitos/underscore separados por ':'
// Deve ter ao menos um ':' e nao pode comecar ou terminar com ':'.
bool valida_formato_conta(const string& conta) {
    if (conta.empty()) return false;
    bool has_colon = false;
    for (char c : conta) {
        if (c == ':') { has_colon = true; continue; }
        if (!islower((unsigned char)c) && !isdigit((unsigned char)c) && c != '_') return false;
    }
    return has_colon && conta.front() != ':' && conta.back() != ':';
}

// Valida formato YYYY-MM-DD com valores plausíveis de mes e dia.
bool valida_data(const string& data) {
    if (data.size() != 10) return false;
    if (data[4] != '-' || data[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit((unsigned char)data[i])) return false;
    }
    int mes = stoi(data.substr(5, 2));
    int dia = stoi(data.substr(8, 2));
    return mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31;
}

string formata_valor(double v) {
    ostringstream oss;
    oss << fixed << setprecision(2) << v;
    return oss.str();
}
