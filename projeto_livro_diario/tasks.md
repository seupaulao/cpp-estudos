# Tasks — Livro Diário

## Legenda
- [x] Concluído
- [ ] Pendente

---

## Fase 1 — Infraestrutura

- [x] `Makefile` — flags `g++ -std=c++17 -Wall -Wextra -lsqlite3`, targets `all` e `clean`
- [x] `utils.h / utils.cpp` — `trim`, `parse_conta`, `valida_formato_conta`, `valida_data`, `formata_valor`
- [x] `db.h / db.cpp` — `db_open`, `db_close`, `db_init_schema`, `PRAGMA foreign_keys = ON`

## Fase 2 — Modelos e CRUD

- [x] `entidade.h / entidade.cpp`
  - [x] Struct `Entidade`
  - [x] `entidade_inserir` — verifica unicidade de nome
  - [x] `entidade_excluir` — bloqueia se houver lançamentos vinculados
  - [x] `entidade_listar`
  - [x] `menu_entidade` — submenus A/B/C/Q
- [x] `lancamento.h / lancamento.cpp`
  - [x] Structs `Lancamento` e `ItemLancamento`
  - [x] `coletar_itens` — loop até '.', valida formato de conta e valor
  - [x] `validar_partidas` — SUM(D)==SUM(C), exibe erro detalhado se falhar
  - [x] `lancamento_inserir` — transação BEGIN/COMMIT/ROLLBACK
  - [x] `lancamento_alterar_db` — delete itens + re-insert em transação
  - [x] `lancamento_excluir_db` — CASCADE nos itens via FK
  - [x] `lancamento_visualizar` — tabela formatada, filtro opcional por entidade
  - [x] `menu_lancamento` — submenus A/B/C/D/Q

## Fase 3 — Relatórios

- [x] `relatorio.h / relatorio.cpp`
  - [x] `imprimir_grupo` — helper: filtra por prefixo de conta, calcula saldo
  - [x] `relatorio_balanco` — ativo / passivo / patrimônio + verificação de equilíbrio
  - [x] `relatorio_dre` — receitas / despesas / resultado (lucro ou prejuízo)
  - [x] `menu_relatorio` — submenus A/B/Q

## Fase 4 — Ponto de Entrada

- [x] `main.cpp` — `db_open`, `db_init_schema`, loop do menu principal, `db_close`

## Fase 5 — Documentação

- [x] `plan.md` — plano de implementação
- [x] `tasks.md` — lista de tarefas (este arquivo)

---

## Verificação (executar após compilação)

- [ ] `make` compila sem erros ou warnings
- [ ] Criar entidade → verificar persistência no banco
- [ ] Tentar excluir entidade com lançamentos → deve exibir erro
- [ ] Novo lançamento com SUM(D) ≠ SUM(C) → deve exibir erro e descartar
- [ ] Novo lançamento válido → persistir, exibir ID, voltar ao menu
- [ ] Alterar lançamento → itens antigos removidos, novos persistidos
- [ ] Excluir lançamento → verificar CASCADE nos itens
- [ ] Balanço com dados: Total Ativo == Total Passivo + PL
- [ ] DRE com dados: resultado = Receita − Despesa
- [ ] Digitar conta inválida → rejeitar com mensagem explicativa
- [ ] Digitar `.` imediatamente → nenhum item, cancelar lançamento
