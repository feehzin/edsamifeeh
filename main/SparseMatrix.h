#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
#include "Node.h"

/**Funções obrigatorias da classe SparseMatrix:
 * Construtor
 * Destrutor
 * Inserção de elementos
 * Obter valor
 * Impressão
 */

class SparseMatrix {
  private:
    Node* m_head; // Nó sentinela
    int linhas; // Número de linhas
    int colunas; // Número de colunas

  public:
    //Construtor
    SparseMatrix(int linhas, int colunas)
    {
      if(linhas <= 0 || colunas <= 0)
      {
        throw std::out_of_range("Numero de linhas e/ou colunas invalidas");
      }

      this->linhas = linhas;
      this->colunas = colunas;

      for (int i = 0; i < ; i++)
      {
        /* code */
      }

      /Destrutor (libera memória)/ 
      ~SparsaMatrix(){ oiii

      }
       
      /Função que insere um valor na matriz esparsa/ 
      void insert(int i, int j, double value){

      }

      /Retorna um valor da matriz/ 
      double get(int i, int j){

      }

      /Exibe a matriz no terminal/ 
      void print(){

      }
      
    }
};

#endif