#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

const bool debug = true;
const int TAM = 8;

struct Jogador {
    string nome;
    int jogadas;
};

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(char t[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            t[i][j] = '~';
        }
    }
}

// Função para exibir o tabuleiro (escondendo os barcos se for do inimigo)
void exibirTabuleiro(char t[TAM][TAM], bool esconderBarcos) {
    esconderBarcos = debug;
    cout << "   1 2 3 4 5 6 7 8\n";
    for (int i = 0; i < TAM; i++) {
        char letra = 'A' + i;
        cout << letra << "  ";
        for (int j = 0; j < TAM; j++) {
            if (esconderBarcos && (t[i][j] == 'C' || t[i][j] == 'D' || t[i][j] == 'P')) {
                cout << "~ ";
            } else {
                cout << t[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

// Valida se a embarcação cabe e não sobrepõe outra
bool validarPosicionamento(char t[TAM][TAM], int l, int c, int tam, char dir) {
    for (int i = 0; i < tam; i++) {
        int nl = l + (dir == 'V' ? i : 0);
        int nc = c + (dir == 'H' ? i : 0);
        
        if (nl >= TAM || nc >= TAM || t[nl][nc] != '~') return false;
    }
    return true;
}

// Posiciona os barcos do Jogador
void posicionarBarcoJogador(char t[TAM][TAM], int tam, char tipo, string nomeBarco) {
    char letra, dir = 'H';
    int col, linha;
    bool valido = false;

    while (!valido) {
        exibirTabuleiro(t, false);
        cout << "\nPosicionando " << nomeBarco << " (Tamanho " << tam << ")\n";
        cout << "Digite a coordenada inicial (Ex: B3): ";
        cin >> letra >> col;
        letra = toupper(letra);
        linha = letra - 'A';
        col--; // Ajuste para índice 0

        if (tam > 1) {
            cout << "Direção (H para Horizontal, V para Vertical): ";
            cin >> dir;
            dir = toupper(dir);
        }

        if (linha >= 0 && linha < TAM && col >= 0 && col < TAM && (dir == 'H' || dir == 'V')) {
            if (validarPosicionamento(t, linha, col, tam, dir)) {
                for (int i = 0; i < tam; i++) {
                    t[linha + (dir == 'V' ? i : 0)][col + (dir == 'H' ? i : 0)] = tipo;
                }
                valido = true;
            } else {
                cout << "Erro: Posicao ocupada ou fora dos limites!\n";
            }
        } else {
            cout << "Coordenadas invalidas!\n";
        }
    }
}

// Posiciona os barcos do Computador aleatoriamente
void posicionarBarcosComputador(char t[TAM][TAM], int tam, char tipo) {
    bool valido = false;
    while (!valido) {
        int linha = rand() % TAM;
        int col = rand() % TAM;
        char dir = (rand() % 2 == 0) ? 'H' : 'V';

        if (validarPosicionamento(t, linha, col, tam, dir)) {
            for (int i = 0; i < tam; i++) {
                t[linha + (dir == 'V' ? i : 0)][col + (dir == 'H' ? i : 0)] = tipo;
            }
            valido = true;
        }
    }
}

// Executa o tiro e retorna se acertou algo
bool realizarTiro(char t[TAM][TAM], int l, int c, int &acertos) {
    if (t[l][c] == 'C' || t[l][c] == 'D' || t[l][c] == 'P') {
        cout << "BUM! Acertou uma embarcacao!\n";
        t[l][c] = 'X';
        acertos++;
        return true;
    } else if (t[l][c] == '~') {
        cout << "Agua...\n";
        t[l][c] = 'O';
    } else {
        cout << "Voce ja atirou aqui antes.\n";
    }
    return false;
}

// Exibe o ranking atualizado
void exibirRanking(const vector<Jogador>& ranking) {
    cout << "\n=== RANKING (Menos Jogadas Ganham) ===\n";
    if (ranking.empty()) {
        cout << "Nenhum registro ainda.\n";
    } else {
        for (size_t i = 0; i < ranking.size(); i++) {
            cout << i + 1 << ". " << ranking[i].nome << " - " << ranking[i].jogadas << " jogadas\n";
        }
    }
    cout << "=====================================\n";
}

int main() {
    srand(time(0));
    vector<Jogador> ranking;
    char continuar = 'S';

    while (toupper(continuar) == 'S') {
        char tabJogador[TAM][TAM], tabComputador[TAM][TAM];
        inicializarTabuleiro(tabJogador);
        inicializarTabuleiro(tabComputador);

        string nomeUser;
        cout << "Digite seu nome: ";
        cin >> nomeUser;

        // Configuração das frotas
        // Computador (Aleatório)
        posicionarBarcosComputador(tabComputador, 3, 'P');
        posicionarBarcosComputador(tabComputador, 2, 'D');
        posicionarBarcosComputador(tabComputador, 2, 'D');
        posicionarBarcosComputador(tabComputador, 1, 'C');
        posicionarBarcosComputador(tabComputador, 1, 'C');

        // Jogador (Manual)
        posicionarBarcoJogador(tabJogador, 3, 'P', "Porta-Avioes");
        posicionarBarcoJogador(tabJogador, 2, 'D', "Destroyer 1");
        posicionarBarcoJogador(tabJogador, 2, 'D', "Destroyer 2");
        posicionarBarcoJogador(tabJogador, 1, 'C', "Cruzador 1");
        posicionarBarcoJogador(tabJogador, 1, 'C', "Cruzador 2");

        int acertosJogador = 0, acertosComp = 0;
        int totalAlvos = 9; // 3(P) + 2(D)*2 + 1(C)*2 = 9 partes de barco no total
        int numJogadas = 0;
        bool fimDeJogo = false;

        // Loop de turnos
        while (!fimDeJogo) {
            numJogadas++;
            cout << "\n================ TURN " << numJogadas << " ================\n";
            
            // Turno do Jogador
            cout << "\n--- SEU TABULEIRO ---\n";
            exibirTabuleiro(tabJogador, false);
            cout << "\n--- TABULEIRO DO COMPUTADOR ---\n";
            exibirTabuleiro(tabComputador, true); // Oculta barcos inimigos

            char letra;
            int col, linha;
            bool tiroValido = false;

            while (!tiroValido) {
                cout << "\nSua vez! Digite as coordenadas do tiro (Ex: F5): ";
                cin >> letra >> col;
                letra = toupper(letra);
                linha = letra - 'A';
                col--;

                if (linha >= 0 && linha < TAM && col >= 0 && col < TAM) {
                    realizarTiro(tabComputador, linha, col, acertosJogador);
                    tiroValido = true;
                } else {
                    cout << "Coordenadas fora do tabuleiro. Tente novamente.\n";
                }
            }

            if (acertosJogador == totalAlvos) {
                cout << "\nParabens " << nomeUser << "! Voce venceu o jogo em " << numJogadas << " jogadas!\n";
                Jogador novoRecorde = {nomeUser, numJogadas};
                ranking.push_back(novoRecorde);
                // Ordena o ranking por menor número de jogadas
                sort(ranking.begin(), ranking.end(), [](const Jogador& a, const Jogador& b) {
                    return a.jogadas < b.jogadas;
                });
                fimDeJogo = true;
                break;
            }

            // Turno do Computador (Lógica Aleatória de palpite)
            cout << "\nTurno do Computador...\n";
            bool tiroCompValido = false;
            while (!tiroCompValido) {
                int lComp = rand() % TAM;
                int cComp = rand() % TAM;
                
                // Evita que o computador atire onde já atirou
                if (tabJogador[lComp][cComp] != 'X' && tabJogador[lComp][cComp] != 'O') {
                    cout << "Computador atirou em: " << (char)('A' + lComp) << cComp + 1 << "\n";
                    realizarTiro(tabJogador, lComp, cComp, acertosComp);
                    tiroCompValido = true;
                }
            }

            if (acertosComp == totalAlvos) {
                cout << "\nO Computador venceu! Mais sorte na proxima vez.\n";
                fimDeJogo = true;
            }
        }

        exibirRanking(ranking);

        cout << "\nDeseja jogar novamente? (S/N): ";
        cin >> continuar;
    }

    cout << "\nObrigado por jogar Batalha Naval!\n";
    return 0;
}