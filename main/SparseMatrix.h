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
    Node* m_head; // Nó sentinela
    int linhas, colunas; // Dimensões da matriz esparsa

  public:
    //Construtor (cria uma matriz vazia)
    SparseMatrix(int linhas, int colunas)
    {
      if(linhas <= 0 || colunas <= 0)
      {
        throw std::out_of_range("Numero de linhas e/ou colunas invalidas");
      }

      this->linhas = linhas;
      this->colunas = colunas;

      m_head = (Node *)malloc(sizeof(Node));
      if (m_head == nullptr)
      {
        throw std::out_of_range("Erro ao alocar memoria");
      }
      
      m_head = new Node(0, 0, 0);
      m_head->direita = m_head; //aponta para si mesmo
      m_head->abaixo = m_head; //aponta para si mesmo
    }

    //Destrutor (libera memória)
    ~SparseMatrix() {
      if(!m_head) {
        throw std::out_of_range("Lista vazia");
      } 
      Node*  aux = m_head->next // O ponteiro aux recebe o ponteiro cabeça da matriz esparsa


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