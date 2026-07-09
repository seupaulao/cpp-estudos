/*
Hashing refere-se ao processo de gerar uma saída de tamanho fixo a partir de uma entrada de tamanho variável usando as fórmulas matemáticas conhecidas como funções hash. Esta técnica determina um índice ou local para o armazenamento de um item em uma estrutura de dados.
Hashing em Estruturas de Dados refere-se ao processo de transformar uma determinada chave em outro valor. Envolve o mapeamento de dados para um índice específico em uma tabela hash usando uma função hash que permite a recuperação rápida de informações com base em sua chave. A transformação de uma chave para o valor correspondente é feita usando uma Função Hash e o valor obtido da função hash é chamado de Código Hash.

Necessidade de estrutura de dados Hash
Todos os dias, os dados na internet estão aumentando multiplamente e é sempre uma luta armazenar esses dados de forma eficiente. Na programação do dia a dia, essa quantidade de dados pode não ser tão grande, mas ainda assim, precisa ser armazenada, acessada e processada de forma fácil e eficiente. Uma estrutura de dados muito comum que é usada para tal propósito é a estrutura de dados Array.

Agora surge a questão se Array já estava lá, qual era a necessidade de uma nova estrutura de dados! A resposta para isso está na palavra "eficiência". Embora armazenar em Array leve tempo O(1), pesquisar nele leva pelo menos tempo O(log n). Esse tempo parece ser pequeno, mas para um grande conjunto de dados, pode causar muitos problemas e isso, por sua vez, torna a estrutura de dados Array ineficiente.

Então agora estamos procurando uma estrutura de dados que possa armazenar os dados e pesquisar neles em tempo constante, ou seja, em tempo O(1). Foi assim que a estrutura de dados Hashing entrou em cena. Com a introdução da estrutura de dados Hash, agora é possível armazenar dados facilmente em tempo constante e recuperá-los em tempo constante também.

Componentes do Hashing
Existem principalmente três componentes do hashing:

Chave: Uma chave pode ser qualquer string ou inteiro que é alimentado como entrada na função hash, a técnica que determina um índice ou local para armazenamento de um item em uma estrutura de dados.
Função Hash: A função hash recebe a chave de entrada e retorna o índice de um elemento em uma matriz chamada tabela hash. O índice é conhecido como índice hash.
Tabela Hash: A tabela hash é uma estrutura de dados que mapeia chaves para valores usando uma função especial chamada função hash. O hash armazena os dados de forma associativa em um array onde cada valor de dados tem seu próprio índice exclusivo.
*/

/*
Como funciona o Hashing?
Suponha que temos um conjunto de strings {“ab”, “cd”, “efg”} e gostaríamos de armazená-lo em uma tabela.

Nosso principal objetivo aqui é pesquisar ou atualizar os valores armazenados na tabela rapidamente em tempo O(1) e não estamos preocupados com a ordenação das strings na tabela. Então, o conjunto de strings fornecido pode atuar como uma chave e a string em si atuará como o valor da string, mas como armazenar o valor correspondente à chave?

Etapa 1: Sabemos que as funções hash (que são algumas fórmulas matemáticas) são usadas para calcular o valor hash que atua como o índice da estrutura de dados onde o valor será armazenado.
Etapa 2: Então, vamos atribuir
“a” = 1,
“b”=2, .. etc, a todos os caracteres alfabéticos.
Etapa 3: Portanto, o valor numérico pela soma de todos os caracteres da string:

“ab” = 1 + 2 = 3,
“cd” = 3 + 4 = 7 ,
“efg” = 5 + 6 + 7 = 18

Etapa 4: Agora, suponha que temos uma tabela de tamanho 7 para armazenar essas strings. A função hash usada aqui é a soma dos caracteres na chave mod Table size . Podemos calcular a localização da string no array tomando sum(string) mod 7 .
Etapa 5: Então, armazenaremos
“ab” em 3 mod 7 = 3,
“cd” em 7 mod 7 = 0 e
“efg” em 18 mod 7 = 4.

A técnica acima nos permite calcular a localização de uma determinada string usando uma função hash simples e encontrar rapidamente o valor armazenado nessa localização. Portanto, a ideia de hash parece uma ótima maneira de armazenar pares (chave, valor) de dados em uma tabela.

O que é uma função Hash?
A função hash cria um mapeamento entre chave e valor, isso é feito por meio do uso de fórmulas matemáticas conhecidas como funções hash. O resultado da função hash é chamado de valor hash ou hash. O valor hash é uma representação da sequência original de caracteres, mas geralmente menor que o original.

Por exemplo: considere uma matriz como um Map onde a chave é o índice e o valor é o valor naquele índice. Então, para uma matriz A, se tivermos o índice i que será tratado como a chave, podemos encontrar o valor simplesmente olhando para o valor em A[i].
*/

/*
Tipos de Funções Hash
Existem muitas funções hash que usam chaves numéricas ou alfanuméricas. Este artigo se concentra em discutir diferentes funções hash:

Método de Divisão.
Método de Multiplicação
Método do Quadrado Médio
Método de Dobramento
Funções Hash Criptográficas
Hash Universal
Hash Perfeito

1. Método de Divisão
O método de divisão envolve dividir a chave por um número primo e usar o restante como valor hash.

PUBLICIDADE

h(k)=k mod m

Onde k é a chave e 𝑚m é um número primo.

Vantagens:

Simples de implementar.
Funciona bem quando 𝑚m é um número primo.
Desvantagens:

Distribuição ruim se 𝑚m não for escolhido com sabedoria.
2. Método de Multiplicação
No método de multiplicação, uma constante 𝐴A (0 < A < 1) é usada para multiplicar a chave. A parte fracionária do produto é então multiplicada por 𝑚m para obter o valor hash.

h(k)=⌊m(kAmod1)⌋

Onde ⌊ ⌋ denota a função de piso.

Vantagens:

Menos sensível à escolha de 𝑚m.
Desvantagens:

Mais complexo que o método de divisão.
3. Método do quadrado médio
No método do quadrado médio, a chave é elevada ao quadrado, e os dígitos do meio do resultado são tomados como o valor hash.

Etapas:

Eleve a chave ao quadrado.
Extraia os dígitos do meio do valor elevado ao quadrado.
Vantagens:

Produz uma boa distribuição de valores hash.
Desvantagens:

Pode exigir mais esforço computacional.
4. Método de dobramento
O método de dobramento envolve dividir a chave em partes iguais, somar as partes e, em seguida, tomar o módulo em relação a 𝑚m.

Etapas:

Divida a chave em partes.
Some as partes.
Pegue o módulo 𝑚m da soma.
Vantagens:

Simples e fácil de implementar.
Desvantagens:

Depende da escolha do esquema de particionamento.

5. Funções de hash criptográficas
As funções de hash criptográficas são projetadas para serem seguras e são usadas em criptografia. Exemplos incluem MD5, SHA-1 e SHA-256.

Características:

Resistência à pré-imagem.
Resistência à segunda pré-imagem.
Resistência à colisão.
Vantagens:

Alta segurança.
Desvantagens:

Computacionalmente intensivo.
6. Hashing universal
O hashing universal usa uma família de funções de hash para minimizar a chance de colisão para qualquer conjunto de entradas.

h(k)=((a⋅k+b)modp)modm

Onde a e b são constantes escolhidas aleatoriamente, p é um número primo maior que m, e k é a chave.

Vantagens:

Reduz a probabilidade de colisões.
Desvantagens:

Requer mais computação e armazenamento.
7. Hashing perfeito
O hashing perfeito visa criar uma função hash sem colisões para um conjunto estático de chaves. Ele garante que nenhuma das duas chaves fará o hash para o mesmo valor.

Tipos:

Hashing perfeito mínimo: garante que o intervalo da função hash seja igual ao número de chaves.
Hashing perfeito não mínimo: o intervalo pode ser maior que o número de chaves.
Vantagens:

Sem colisões.
Desvantagens:

Complexo de construir.
Conclusão
Concluindo, as funções hash são ferramentas muito importantes que ajudam a armazenar e encontrar dados rapidamente. Conhecer os diferentes tipos de funções hash e como usá-las corretamente é essencial para fazer o software funcionar melhor e com mais segurança. Ao escolher a função hash certa para o trabalho, os desenvolvedores podem melhorar muito a eficiência e a confiabilidade de seus sistemas.
*/
