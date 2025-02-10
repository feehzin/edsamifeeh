#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include "SparseMatrix.h"

using namespace std;

// Função que lê a matriz esparsa de um arquivo
void ReadSparseMatrix(SparseMatrix*& m, const string& nome_arquivo) {
    ifstream arquivoLido(nome_arquivo);

    if (!arquivoLido.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo: " + nome_arquivo);
    }

    int linhas, colunas;
    arquivoLido >> linhas >> colunas;

    // Criando a matriz corretamente com as dimensões lidas
    m = new SparseMatrix(linhas, colunas);
    cout << "Matriz de " << linhas << "x" << colunas << " lida do arquivo " << nome_arquivo << "." << endl;

    int linha, coluna;
    double valor;
    while (arquivoLido >> linha >> coluna >> valor) {
        cout << "Inserindo valor: linha " << linha << ", coluna " << coluna << ", valor " << valor << endl;
        m->insert(linha, coluna, valor);
    }

    arquivoLido.close();
}

// Função que soma duas matrizes esparsas
SparseMatrix sum(SparseMatrix& A, SparseMatrix& B) {
    // Verificar se as matrizes são da mesma dimensão
    if (A.getLinhas() != B.getLinhas() || A.getColunas() != B.getColunas()) {
        throw out_of_range("As matrizes devem ter o mesmo tamanho para a funcao de soma.");
    }

    SparseMatrix C(A.getLinhas(), A.getColunas());

    // Ponteiros para percorrer as linhas das matrizes A e B
    Node* linha_A = A.getHead()->abaixo;
    Node* linha_B = B.getHead()->abaixo;

    while (linha_A != A.getHead()) {
        Node* coluna_A = linha_A->direita;
        Node* coluna_B = linha_B->direita;

        while (coluna_A != linha_A && coluna_B != linha_B) {
            if (coluna_A->coluna == coluna_B->coluna) {
                double soma = coluna_A->valor + coluna_B->valor;
                if (soma != 0) {
                    C.insert(coluna_A->linha, coluna_A->coluna, soma);
                }
                coluna_A = coluna_A->direita;
                coluna_B = coluna_B->direita;
            } else if (coluna_A->coluna < coluna_B->coluna) {
                C.insert(coluna_A->linha, coluna_A->coluna, coluna_A->valor);
                coluna_A = coluna_A->direita;
            } else {
                C.insert(coluna_B->linha, coluna_B->coluna, coluna_B->valor);
                coluna_B = coluna_B->direita;
            }
        }

        while (coluna_A != linha_A) {
            C.insert(coluna_A->linha, coluna_A->coluna, coluna_A->valor);
            coluna_A = coluna_A->direita;
        }
        while (coluna_B != linha_B) {
            C.insert(coluna_B->linha, coluna_B->coluna, coluna_B->valor);
            coluna_B = coluna_B->direita;
        }

        linha_A = linha_A->abaixo;
        linha_B = linha_B->abaixo;
    }

    return C;
}

// Função que multiplica duas matrizes esparsas
SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B) {
    if (A.getColunas() != B.getLinhas()) {
        throw out_of_range("O numero de colunas de A deve ser igual ao número de linhas de B para executar a multiplicacao.");
    }

    SparseMatrix C(A.getLinhas(), B.getColunas());

    // Para cada linha de A
    for (Node* linha_A = A.getHead()->abaixo; linha_A != A.getHead(); linha_A = linha_A->abaixo) {
        // Para cada coluna de B (que é uma linha na transposta de B)
        for (Node* element_A = linha_A->direita; element_A != linha_A; element_A = element_A->direita) {
            int i = element_A->linha;
            int j = element_A->coluna;
            double valor_A = element_A->valor;

            // Achar a linha correspondente na matriz B
            Node* coluna_B = B.getHead()->abaixo;
            while (coluna_B != B.getHead() && coluna_B->linha != j) {
                coluna_B = coluna_B->abaixo;
            }

            if (coluna_B != B.getHead()) { // Coluna B encontrada
                for (Node* element_B = coluna_B->direita; element_B != coluna_B; element_B = element_B->direita) {
                    int s = element_B->coluna;
                    double valor_B = element_B->valor;

                    double valorC = C.get(i, s) + (valor_A * valor_B);
                    if (valorC != 0) {
                        C.insert(i, s, valorC);
                    }
                }
            }
        }
    }

    return C;
}

int main() {
    vector<SparseMatrix> matriz;

    cout << "------- Sistema de Matriz -------" << endl
         << "Digite 'ajuda' para ver a lista de comandos" << endl;

    string comando;

    while (getline(cin, comando)) {
        istringstream ss(comando);
        string cmd;
        ss >> cmd;

        if (cmd == "ajuda") {
            cout << "------------------------------------ Lista de Comandos ------------------------------------" << endl
                 << "criar M N................ criar matriz vazia com M linhas e N colunas" << endl
                 << "ler m.txt................ ler arquivo de texto, armazenando seus parametros em uma matriz" << endl
                 << "mostre A................. mostra a matriz A" << endl
                 << "somar A B................ soma a matriz A com a matriz B" << endl
                 << "multi A B................ multiplica a matriz A com a matriz B" << endl
                 << "mudar A i j valor........ substitui o valor no indice i (linha), j (coluna) na matriz A" << endl
                 << "listar................... mostra todas as matrizes do sistema" << endl
                 << "limpar A................. limpa a matriz A" << endl
                 << "limparM.................. limpa todas as matrizes do sistema" << endl
                 << "sair..................... terminar sessao" << endl
                 << "-------------------------------------------------------------------------------------------" << endl;
        } else if (cmd == "criar") {
            int M, N;
            ss >> M >> N;

            if (M > 0 && N > 0) {
                SparseMatrix novaMatriz(M, N);
                matriz.push_back(novaMatriz);
                cout << "Matriz " << matriz.size() - 1 << " adicionada com sucesso!" << endl;
            } else {
                cerr << "Erro: Dimensoes da matriz sao invalidas!" << endl;
            }
        } else if (cmd == "ler") {
            string nomeArquivo;
            ss >> nomeArquivo;
            SparseMatrix* novaMatriz = nullptr;  // Ponteiro para a nova matriz
            ReadSparseMatrix(novaMatriz, nomeArquivo);
            
            if (novaMatriz) {
                matriz.push_back(novaMatriz);
                cout << "Matriz lida do arquivo '" << nomeArquivo << "' adicionada ao sistema com sucesso!" << endl;
            } else {
                cerr << "Erro: Falha ao criar matriz a partir do arquivo!" << endl;
            }
        }
        else if (cmd == "mostre") {
            int A;
            ss >> A;

            if (A >= 0 && A < matriz.size()) {
                matriz[A].print();
            } else {
                cerr << "Erro: A matriz com o indice passado não foi encontrada no sistema." << endl;
            }
        } else if (cmd == "somar") {
            int A, B;
            ss >> A >> B;

            if (A >= 0 && A < matriz.size() && B >= 0 && B < matriz.size()) {
                SparseMatrix resultado = sum(matriz[A], matriz[B]);
                matriz.push_back(resultado);
                cout << "Resultado da soma:" << endl;
                matriz.back().print();
            } else {
                cerr << "Erro: Indices inválidos para soma!" << endl;
            }
        } else if (cmd == "multi") {
            int A, B;
            ss >> A >> B;

            if (A >= 0 && A < matriz.size() && B >= 0 && B < matriz.size()) {
                SparseMatrix resultado = multiply(matriz[A], matriz[B]);
                matriz.push_back(resultado);
                cout << "Resultado da multiplicacaoo:" << endl;
                matriz.back().print();
            } else {
                cerr << "Erro: Indices inválidos para multiplicacao!" << endl;
            }
        } else if (cmd == "mudar") {
            unsigned A, i, j;
            double valor;
            ss >> A >> i >> j >> valor;

            if (A >= 0 && A < matriz.size() && i > 0 && i <= matriz[A].getLinhas() && j > 0 && j <= matriz[A].getColunas()) {
                matriz[A].insert(i, j, valor);
                cout << "Valor atualizado na matriz[" << A << "] com sucesso!" << endl;
            } else {
                cerr << "Erro: Dados passados não correspondem a nenhuma matriz ou posicao valida!" << endl;
            }
        } else if (cmd == "limpar") {
            int A;
            ss >> A;

            if (A >= 0 && A < matriz.size()) {
                matriz.erase(matriz.begin() + A);
                cout << "Matriz[" << A << "] removida com sucesso!" << endl;
            } else {
                cerr << "Erro: indice invalido!" << endl;
            }
        } else if (cmd == "limparM") {
            if (matriz.empty()) {
                cout << "Nao ha matrizes para limpar." << endl;
            } else {
                matriz.clear();
                cout << "Todas as matrizes foram removidas do sistema!" << endl;
            }
        } else if (cmd == "listar") {
            if (matriz.empty()) {
                cout << "Nao ha matrizes listadas no sistema!" << endl;
                continue;
            }

            for (int i = 0; i < matriz.size(); i++) {
                cout << "Matriz[" << i << "]:" << endl;
                matriz[i].print();
                cout << endl;
            }
            cout << "Todas as matrizes foram mostradas com sucesso!" << endl;
        } else if (cmd == "sair") {
            cout << "Saindo..." << endl;
            break;
        } else {
            cout << "Comando nao reconhecido. Digite 'ajuda' para ver a lista de comandos." << endl;
        }
    }
}
