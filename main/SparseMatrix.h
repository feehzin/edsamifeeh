#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
#include "Node.h"

class SparseMatrix
{
  private:
    Node* m_head; //nó sentinela
    int linhas; //número de linhas
    int colunas; //números de colunas
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
      
    }
};

#endif