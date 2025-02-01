#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
#include "Node.h"
#include <stdexcept> // Biblioteca para lançar exceções

/**Funções obrigatorias da classe SparseMatrix:
 * Construtor
 * Destrutor
 * Inserção de elementos
 * Obter valor
 * Impressão
 */

// Classe que respresenta a matriz esparsa
class SparseMatrix {
  private:
    Node* m_head_linha; // Nó sentinela da linha
    Node* m_head_coluna; // Nó sentinela da coluna
    int linhas; // Número de linhas
    int colunas; // Número de colunas

  public:
    //Construtor
    SparseMatrix(int linhas, int colunas)
    {
      Node* mat;

      if(linhas <= 0 || colunas <= 0)
      {
        throw std::out_of_range("Numero de linhas e/ou colunas invalidas");
      }

      mat->linhas = linhas;
      mat->colunas = colunas;

      
    }

    //Destrutor (libera memória)
    ~SparseMatrix() 
    { 

    }
       
    //Função que insere um valor na matriz esparsa
    void insert(int i, int j, double value)
    {

    }

    //Retorna um valor da matriz
    double get(int i, int j)
    {

    }

    //Exibe a matriz no terminal
    void print()
    {

    }
      
    
};

#endif