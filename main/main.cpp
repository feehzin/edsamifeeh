#include <iostream>
#include <fstream> //Biblioteca para ler arquivo texto
#include <string>
#include <stdexcept> // Biblioteca para lançar exceções
#include <algorithm> // Biblioteca para retornar o menor valor entre A e B
#include <vector>
#include <sstream>
#include "SparseMatrix.h"
using namespace std;

void readSparseMatrix(SparseMatrix& m, std::string nome_do_arquivo){
    ifstream arquivo;

    arquivo.open(nome_do_arquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro: nao foi possivel abrir: " << nome_do_arquivo << endl;
        return;
    }

    int linhas, colunas;
    arquivo >> linhas >> colunas;

    if (linhas != m.getLinhas() || colunas != m.getColunas()){
        cerr << "Erro: dimensoes do arquivo nao correspodem a matriz dada" << endl; //o uso de cerr é para mensagens de erro
        arquivo.close();
        return;
    }
    
    int i, j;
    double valor;

    while (arquivo >> i >> j >> valor){
        if (i < 1 || i > linhas || j < 1 || j > colunas){
            cerr << "Erro: indices fora do limite esperado (" << linhas << ", " << colunas << ")" << endl;
            continue;
        }
      
        if (valor == 0){
            continue;
        }
      
        m.insert(i, j, valor);
    }
    
    arquivo.close();
}
  
  /**Função que soma matrizes esparsas */
  SparseMatrix sum(SparseMatrix& A, SparseMatrix& B){
    // Verificar se as matrizes são da mesma dimensão(tamanho)
    if(A.getLinhas() != B.getLinhas()|| A.getColunas()!= B.getColunas()){
      throw std::out_of_range("As matrizes devem ter o mesmo tamanho para a função de soma.");
    }
    
    // Cria uma matriz para guardar o resultado com as mesmas dimensões de A e B
    SparseMatrix C(A.getLinhas(), A.getColunas());

    // Ponteiros para percorrer as linhas das matrizes A e B
    Node* linha_A = A.getHead()->abaixo; // Começa na primeira linha de A
    Node* linha_B = B.getHead()->abaixo; // Começa na primeira linha de B

    // Percorre as linhas das matrizes A e B
    while(linha_A != A.getHead()){
      Node* coluna_B = linha_A->direita; // Primeira coluna da linha de A
      Node* coluna_A = linha_B->direita; // Primeira linha de B
      while(coluna_A != linha_A && coluna_B != linha_B){
        if(coluna_A->colunas == coluna_B->colunas){ // Se as colunas forem iguais, soma os valores
          double soma = coluna_A->valor + co
        }
      }  

  }
  

     
  SparseMatrix multiply(SparseMatrix& *A, SNodeparseMatrix& B){
    if (A.getColunas()!= B.getLinhas()){
      throw std::out_of_range("O número de colunas de A deve ser igual ao número de  linhas de B para executar a multiplicação.");
    }

    SparseMatrix C(A.getLinhas(), B.getColunas());  
  }
 
int main()
{
  vector<SparseMatrix> matrix;
  
  cout << "------- Sistema de Matrix -------" << endl
       << "Digite 'ajuda' para ver a lista de comandos" << endl;
  
  while (true)
  {
    string comando;
    getline(cin, comando);

    istringstream ss(comando);
    string cmd;

    ss >> cmd;

    if(cmd == "ajuda")
    {
        cout << "------------------------- Lista de Comandos -------------------------" << endl
           << "criar matriz M N ........ criar matriz vazia com M linhas e N colunas" << endl
           << "mostre matriz A ......... imprime a matriz A" << endl
           << "somar matrizes A B ...... soma a matriz A com a matriz B" << endl
           << "multi matrizes A B ...... multiplica a matriz A com a matriz B" << endl
           << "limpar matriz A ......... limpa a matriz A" << endl
           << "limpar matrizes ......... limpa todas as matrizes no vector" << endl
           << "sair..................... terminar sessao" << endl;
    }
    else if(cmd == "criar") {
        int M, N;
        ss >> M > N;

        if (M > 0 && N > 0)
        {
          matrix.
        }
        
    }
  }
} 