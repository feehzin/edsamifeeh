#include <iostream>
#include <fstream> //Biblioteca para ler arquivo texto
#include <string>
#include <stdexcept> // Biblioteca para lançar exceções
#include <algorithm> // Biblioteca para retornar o menor valor entre A e B
#include <vector>
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

    // Percorre as linhas das matrizes ate que as duas tenham sido completamente revistadas
    while(linha_A != A.getHead-> || linha_B != B.getHead){
      // Se a linha de A for menor, insere os elementos de A em C
      if(linha_B == B.getHead() || (linha_A != A.getHead() && linha_A->linhas < linha_B->linhas)){
        Node* atual_A = linha_A->direita; // Ponteiro para o primeiro elemento da linha A 
        while(atua_A != linha_A){ // Percorre toda a linha A
        C.insert(linha_A->linhas, atual_A->colunas, atual_A->valor); // Insere o valor de atual_A->valor na posição linha_A->linhas, atual_A->colunas em C
        atual_A = atual_A->direita; // Segui para o próximo nó na linha A
        }
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
  
} 