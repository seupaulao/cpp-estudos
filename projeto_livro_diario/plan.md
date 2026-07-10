# Plano de Implementação — Livro Diário

## Visão Geral

Aplicação console em C++17 utilizando STL e SQLite3 para registro de lançamentos contábeis em **partidas dobradas**, seguindo a nomenclatura de contas no estilo hledger.

---

## Estrutura de Arquivos

```
projeto_livro_diario/
├── main.cpp          — ponto de entrada, loop do menu principal
├── db.h / db.cpp     — wrapper SQLite3 (conexão, init schema)
├── utils.h / utils.cpp     — trim, parse_conta, validações, formatação
├── entidade.h / entidade.cpp     — struct + CRUD + menu_entidade
├── lancamento.h / lancamento.cpp — structs + CRUD + menu_lancamento
├── relatorio.h / relatorio.cpp   — Balanço + DRE + menu_relatorio
├── Makefile
└── livro_diario.db   — gerado em runtime pelo SQLite3
```

---

## Schema do Banco de Dados

```sql
CREATE TABLE entidade (
    id        INTEGER PRIMARY KEY AUTOINCREMENT,
    nome      TEXT    NOT NULL,
    descricao TEXT    DEFAULT '',
    UNIQUE(nome)
);

CREATE TABLE lancamento (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    entidade_id INTEGER NOT NULL,
    data        TEXT    NOT NULL,   -- formato YYYY-MM-DD
    comentario  TEXT    DEFAULT '',
    FOREIGN KEY (entidade_id) REFERENCES entidade(id)
);

CREATE TABLE item_lancamento (
    id            INTEGER PRIMARY KEY AUTOINCREMENT,
    lancamento_id INTEGER NOT NULL,
    conta         TEXT    NOT NULL,
    tipo          TEXT    NOT NULL CHECK(tipo IN ('D','C')),
    valor         REAL    NOT NULL,
    FOREIGN KEY (lancamento_id) REFERENCES lancamento(id) ON DELETE CASCADE
);
```

---

## Regras de Negócio

| Regra | Descrição |
|---|---|
| Prefixo `a ` | `a passivo:fornecedor` → tipo=C (crédito); sem prefixo → tipo=D (débito) |
| Formato de conta | `tipo:nome` ou `tipo:subtipo:nome` — letras minúsculas, dígitos, underscore |
| Encerramento de itens | Digitando `.` no campo Conta fecha o loop de entrada |
| Partidas dobradas | `SUM(D) == SUM(C)` por lançamento — obrigatório |
| Persistência | Lançamento e itens inseridos em transação SQLite3 (`BEGIN/COMMIT/ROLLBACK`) |
| Falha de validação | Mostra totais e diferença, descarta buffer, volta ao Menu Lançamentos |
| Exclusão de entidade | Bloqueada se existirem lançamentos vinculados |
| Exclusão de lançamento | `ON DELETE CASCADE` remove todos os itens automaticamente |

---

## Menus

```
Menu Principal
 ├─ [A] Cadastrar Entidade
 │     [A] Nova Entidade
 │     [B] Excluir Entidade (bloqueado se tiver lançamentos)
 │     [C] Visualizar Lançamentos da Entidade
 │     [Q] Voltar
 ├─ [B] Cadastrar Lançamentos
 │     [A] Novo Lançamento  ← loop de itens até '.', valida D==C
 │     [B] Alterar Lançamento  ← substitui todos os itens
 │     [C] Excluir Lançamento  ← cascade nos itens
 │     [D] Visualizar Lançamentos
 │     [Q] Voltar
 ├─ [C] Relatórios
 │     [A] Balanço Patrimonial
 │     [B] DRE
 │     [Q] Voltar
 └─ [Q] Sair
```

---

## Relatórios

### Balanço Patrimonial
- **Ativo** (`ativo:*`): saldo = Débitos − Créditos
- **Passivo** (`passivo:*`): saldo = Créditos − Débitos
- **Patrimônio Líquido** (`patrimonio:*`): saldo = Créditos − Débitos
- Verificação: Total Ativo == Total Passivo + PL

### DRE
- **Receitas** (`receita:*`): saldo = Créditos − Débitos
- **Despesas** (`despesa:*`): saldo = Débitos − Créditos
- **Resultado** = Receitas − Despesas (Lucro / Prejuízo)

---

## Decisões Técnicas

| Decisão | Justificativa |
|---|---|
| SQLite3 C API direta | Sem dependências extras, simples para projeto console |
| `using namespace std` | Padrão adotado em todo o projeto |
| Menus com `cin/cout` | Sem ncurses — alinhado com o estilo do restante do workspace |
| Compilador: `g++ -std=c++17 -Wall -Wextra -lsqlite3` | C++17 por `string_view`, structured bindings; warnings ativados |
| Alterar lançamento = delete items + re-insert | Simplifica lógica, mantém integridade transacional |
| Contas como texto livre | Segue o modelo hledger — não há tabela de plano de contas pré-fixada |
