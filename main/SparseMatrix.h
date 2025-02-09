#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "Node.h"
#include <iostream>
#include <stdexcept> // Biblioteca para lançar exceções

/**Funções obrigatorias da classe SparseMatrix:
 * Construtor: Inicializa a matriz esparsa com um nó sentinela.
 * Destrutor: Libera a memória alocada corretamente.
 * Inserção de elementos: Insere valores diferentes de zero na estrutura.
 * Obter valor: Retorna um elemento específico da matriz.
 * Impressão: Exibe a matriz esparsa de forma legível.
 */

// Classe que respresenta a matriz esparsa
class SparseMatrix {
  private:
    Node* m_head; // Nó sentinela
    int linhas, colunas; // Dimensões da matriz esparsa

  public:
    
    /*Construtor (cria uma matriz vazia).
    Para m Número de linhas.
    Para n Número de colunas.
    throws std::out_of_range se os valores forem inválidos.*/
    SparseMatrix(int m, int n){
      if(m <= 0 || n <= 0)
      {
        throw std::out_of_range("Numero de linhas e/ou colunas invalidas.");
      }
      linhas = m;
      colunas = n;
      m_head = new Node(0, 0, 0);
      if (!m_head){
        throw std::bad_alloc(); // Garante que a alocação foi bem-sucedida
    }
      m_head->direita = m_head; // Lista circular na horizontal
      m_head->abaixo = m_head; // Lista circular na vertical
    }
  
    //Destrutor: libera a memória alocada dinamicamente.
    ~SparseMatrix() {
      if (!m_head) return;
      Node* atual_L = m_head->abaixo;
      while (atual_L != m_head) {
          Node* atual_C = atual_L->direita;
          while (atual_C != atual_L) {
              Node* aux = atual_C;
              atual_C = atual_C->direita;
              delete aux; // Libera memória da célula
          }
          Node* aux = atual_L;
          atual_L = atual_L->abaixo;
          delete aux; // Libera memória da linha
      }
      delete m_head; // Libera o nó sentinela
      m_head = nullptr;
  }
    // Retorna o número de linhas de uma matriz.
    int getLinhas() const { return linhas; }

    // Retorna o número de colunas de uma matriz.
    int getColunas() const { return colunas; }
  
     // Retorna o ponteiro para o nó sentinela da matriz.
     Node* getHead() const { return m_head; }

    // Função que insere um valor na matriz esparsa
    void insert(int i, int j, double value){
    if (value == 0) return;
    if (i < 1 || i > linhas || j < 1 || j > colunas) {
        throw std::out_of_range("Índices fora dos limites da matriz.");
    }
    Node* atual_L = m_head;
    while (atual_L->abaixo != m_head && atual_L->abaixo->linha < i) {
        atual_L = atual_L->abaixo;
    }
    if (atual_L->abaixo == m_head || atual_L->abaixo->linha != i) {
        Node* novaLinha = new Node(i, -1, 0);
        novaLinha->abaixo = atual_L->abaixo;
        atual_L->abaixo = novaLinha;
    }
    atual_L = atual_L->abaixo;
    
    Node* atual_C = atual_L;
    while (atual_C->direita != atual_L && atual_C->direita->coluna < j) {
        atual_C = atual_C->direita;
    }
    if (atual_C->direita == atual_L || atual_C->direita->coluna != j) {
        Node* novoNode = new Node(i, j, value);
        novoNode->direita = atual_C->direita;
        atual_C->direita = novoNode;
    } else {
        atual_C->direita->valor = value;
    }
}
    // Retorna um valor específico da matriz.
    double get (int i, int j) const {
      if (i < 1 || i > linhas || j < 1 || j > colunas) {
        throw std::out_of_range("Índices fora dos limites da matriz.");
    }
    Node* atual_L = m_head->abaixo;
    while (atual_L != m_head && atual_L->linha < i) {
        atual_L = atual_L->abaixo;
    }
    if (atual_L == m_head || atual_L->linha != i) return 0.0;
    
    Node* atual_C = atual_L->direita;
    while (atual_C != atual_L && atual_C->coluna < j) {
        atual_C = atual_C->direita;
    }
    if (atual_C == atual_L || atual_C->coluna != j) return 0.0;
    return atual_C->valor;
}
    // Exibe a matriz no terminal
    void print(){
      for (int i = 1; i <= linhas; i++){
        for (int j = 1; j <= colunas; j++){
          double valor = get(i, j);
          std::cout << valor << " ";
        }
        std::cout << std::endl;
      }  
    } 
};

#endif
