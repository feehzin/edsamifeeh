#include <iostream>
#include <fstream> //Biblioteca para ler arquivo texto
#include <string>
#include <stdexcept> // Biblioteca para lançar exceções
#include <algorithm> // Biblioteca para retornar o menor valor entre A e B
#include "SparseMatrix.h"
using namespace std;

void readSparseMatrix(SparseMatrix& m, std::string nome_do_arquivo)
  {
    ifstream arquivo;

    arquivo.open(nome_do_arquivo);

    if (!arquivo.is_open())
    {
      cerr << "Erro: nao foi possivel abrir: " << nome_do_arquivo << endl;
      return;
    }

    int linhas, colunas;
    arquivo >> linhas >> colunas;

    if (linhas != m.getLinhas() || colunas != m.getColunas())
    {
      cerr << "Erro: dimensoes do arquivo nao correspodem a matriz dada" << endl; //o uso de cerr é para mensagens de erro
      arquivo.close();
      return;
    }
    
    int i, j;
    double valor;

    while (arquivo >> i >> j >> valor)
    {
      if (i < 1 || i > linhas || j < 1 || j > colunas)
      {
        cerr << "Erro: indices fora do limite esperado (" << linhas << ", " << colunas << ")" << endl;
        continue;
      }
      
      if (valor == 0)
      {
        continue;
      }
      
      m.insert(i, j, valor);
    }
    
    arquivo.close();
  }
  
  /**Função que soma matrizes esparsas */
  SparseMatrix sum(SparseMatrix& A, SparseMatrix& B) {
    // Verificar se as matrizes são da mesma dimensão(tamanho)
    if(A.getLinhas() != B.getLinhas()|| A.getColunas()!= B.getColunas()){
      throw std::out_of_range("As matrizes devem ter o mesmo tamanho para a função de soma.");
    }
    
    SparseMatrix C(A.getLinhas(), A.getColunas());

    // Ponteiros para percorrer as linhas das matrizes A e B
    Node* linha_A = A.m_head->abaixo; // Começa na primeira linha de A
    Node* linha_B = B.m_head->abaixo; // Começa na primeira linha de B

    // Percorre as linhas das matrizes ate que as duas tenham sido completamente revistadas
    whilee(linha_A != A.m_head-> || linha_B != B.m_head) {
      
    }

  }

  // Matriz criada para guardar o resultado da soma        
  SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B) {
    if(A.getLinhas() != B.getLinhas()|| A.getColunas()!= B.getColunas()){
      throw std::out_of_range("As matrizes devem ter o mesmo tamanho para a função de soma.");
    }
    SparseMatrix C(A.getLinhas(), A.getColunas());
    
  }

int main()
{
  

}