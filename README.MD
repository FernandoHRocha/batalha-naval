# Batalha Naval em C++
Este é um clássico jogo de Batalha Naval desenvolvido em C++ para console. O jogo permite que um jogador humano dispute contra a inteligência artificial (computador). Ambos os lados posicionam suas frotas em um tabuleiro oculto e se alternam dando tiros em coordenadas específicas até que uma das frotas seja completamente destruída. O jogo também mantém um ranking local que avalia a performance baseado no menor número de jogadas para vencer.

# 🛠️ Principais Conceitos Utilizados
O código faz uso de diversos conceitos fundamentais da programação estruturada e da linguagem C++. Abaixo estão os principais destaques:

## 1. O Tabuleiro de Matriz (char t[TAM][TAM])
O coração visual e lógico do jogo é a matriz bidimensional de caracteres (char t[TAM][TAM]).
- O que representa: Uma matriz é uma tabela com linhas e colunas. Neste caso, TAM está definido como 8, gerando um tabuleiro de $8 \times 8$ (64 posições).
- Estados das Células: Cada posição da matriz armazena um caractere (char) que indica o que há naquela coordenada:
  - ~ : Água (posição intocada).
  - P, D, C : Partes dos barcos (Porta-Aviões, Destroyer e Cruzador).
  - X : Tiro certeiro (embarcação atingida).
  - O : Tiro na água (erro).

## 2. Estruturas de Dados (struct) e Vetores Dinâmicos (std::vector)
Para gerenciar o sistema de pontuação, foram utilizadas estruturas e contêineres da biblioteca padrão:
- struct Jogador: Uma estrutura personalizada que agrupa o nome do usuário (string) e a quantidade de jogadas (int) que ele levou para vencer.
- vector<Jogador> ranking: Um array dinâmico da STL (Biblioteca de Modelos Padrão) (std::vector) que armazena os recordes. Ele cresce automaticamente à medida que novas partidas são jogadas e vencidas.

## 3. Passagem de Parâmetros por Referência (&)
Na função realizarTiro(char t[TAM][TAM], int l, int c, int &acertos), o parâmetro acertos é passado por referência:
```cpp
bool realizarTiro(char t[TAM][TAM], int l, int c, int &acertos)
```
Isso permite que a função modifique diretamente a variável original (acertosJogador ou acertosComp) que foi criada dentro da função main(), controlando o fim do jogo sem a necessidade de variáveis globais.

## 4. Geração de Números Aleatórios (rand() e srand())
Para que o computador posicione seus barcos aleatoriamente e faça disparos imprevisíveis, é utilizada a função rand(). O comando srand(time(0)) no início do programa garante que a semente do gerador mude a cada segundo, fazendo com que cada partida seja completamente diferente da anterior.

## 5. Algoritmos de Ordenação (std::sort) com Expressões Lambda
Ao final de uma vitória, o ranking é ordenado automaticamente para que o jogador com menos turnos apareça no topo. Isso é feito de forma moderna usando uma função anônima (Expressão Lambda):
```cpp
sort(ranking.begin(), ranking.end(), [](const Jogador& a, const Jogador& b) {
    return a.jogadas < b.jogadas;
});
```
# 🎮 Como Jogar

1. Compilação: Compile o código usando qualquer compilador C++ moderno (suporte a C++11 ou superior).
```bash
g++ -std=c++11 main.cpp -o batalha_naval
```

2. Execução: Rode o executável gerado.
```bash
./batalha_naval
```

3. Fase de Posicionamento: * Digite a coordenada inicial do seu barco (Ex: B3) e defina a direção (H para Horizontal, V para Vertical).
4. Fase de Combate:No seu turno, digite a coordenada do alvo (Ex: F5).Fique atento ao feedback do console (BUM! ou Agua...).O jogo acaba assim que você ou o computador destruírem as 9 partes das embarcações inimigas.
# 🔧 Modo Debug
No topo do código, há uma constante global booleana:
```cpp
const bool debug = true;
```
Se estiver true, o tabuleiro do computador mostrará onde foram posicionados os barcos inimigos (útil para testes de desenvolvimento).
Para jogar uma partida real, altere para false para esconder os barcos inimigos.