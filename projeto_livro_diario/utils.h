#pragma once
#include <string>

using namespace std;

struct ContaInfo {
    string conta;   // ex: "ativo:banco"
    char   tipo;    // 'D' = debito, 'C' = credito
};

string    trim(const string& s);
ContaInfo parse_conta(const string& raw);
bool      valida_formato_conta(const string& conta);
bool      valida_data(const string& data);
string    formata_valor(double v);
