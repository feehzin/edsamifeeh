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
      Node* m_head;
      int linhas, colunas;
  
  public:
      // Construtor
      SparseMatrix(int m, int n) 
        : linhas(m), colunas(n) {
          m_head = new Node(0, 0, 0);  // Criar o nó cabeça
          m_head->abaixo = m_head;
          m_head->direita = m_head;
      }
  
      // Destrutor
      ~SparseMatrix() {
          Node* linha = m_head->abaixo;
          while (linha != m_head) {
              Node* coluna = linha->direita;
              while (coluna != linha) {
                  Node* temp = coluna;
                  coluna = coluna->direita;
                  delete temp;
              }
              Node* temp = linha;
              linha = linha->abaixo;
              delete temp;
          }
          delete m_head;
      }
  
      // Função para inserir um valor na matriz esparsa
      void insert(int i, int j, double value) {
        // Cria um novo nó
        Node* nova = new Node(i, j, value);

        // Encontrar ou criar a linha
        Node* linha_atual = m_head;
        while (linha_atual->abaixo != m_head && linha_atual->abaixo->linha < i) {
            linha_atual = linha_atual->abaixo;
        }

        // Se a linha não existe, cria uma nova linha
        if (linha_atual->abaixo == m_head || linha_atual->abaixo->linha != i) {
            Node* nova_linha = new Node(0, 0, 0);
            nova_linha->linha = linha;
            nova_linha->abaixo = linha_atual->abaixo;
            linha_atual->abaixo = nova_linha;
            linha_atual = nova_linha;
        }

        // Encontrar ou criar a coluna
        Node* coluna_atual = linha_atual;
        while (coluna_atual->direita != linha_atual && coluna_atual->direita->coluna < j) {
            coluna_atual = coluna_atual->direita;
        }

        // Se a coluna não existe, insere uma nova coluna
        if (coluna_atual->direita == linha_atual || coluna_atual->direita->coluna != j) {
            nova->direita = coluna_atual->direita;
            coluna_atual->direita = nova;
        } else {
            // Se o elemento já existe, apenas atualiza o valor
            coluna_atual->direita->valor = value;
            delete nova;
        }
      }
  
      // Função para obter o valor da matriz em uma posição específica
      double get(int i, int j) {
          Node* linha = m_head->abaixo;
          while (linha != m_head && linha->linha < i) {
              linha = linha->abaixo;
          }
  
          if (linha == m_head || linha->linha != i) {
              return 0.0;
          }
  
          Node* coluna = linha->direita;
          while (coluna != linha && coluna->coluna < j) {
              coluna = coluna->direita;
          }
  
          if (coluna == linha || coluna->coluna != j) {
              return 0.0;
          }
  
          return coluna->valor;
      }
  
      // Função para imprimir a matriz esparsa
      void print() {
        for (int i = 1; i <= linhas; i++){
          for (int j = 1; j <= colunas; j++){
            double valor = get(i, j);
            std::cout << valor << " ";
          }
          std::cout << std::endl;
        }  
      }

      void clear() {
        Node* aux = m_head->abaixo;
        while (aux != m_head) {
            Node* atual = aux->direita;
            while (atual != aux) {
                Node* temp = atual;
                atual = atual->direita;
                delete temp;  // Deleta cada nó de dados (elemento da matriz)
            }
            Node* temp = aux;
            aux = aux->abaixo;
            delete temp;  // Deleta o nó da linha
        }
    
        // Libera o nó cabeça (sentinela)
        delete m_head;
        m_head = nullptr;  // Aponta para nullptr para evitar referências pendentes
      }
  
      // Getters para número de linhas e colunas
      int getLinhas() const {
         return linhas; 
      }
      int getColunas() const {
         return colunas;
      }
  
      // Função para obter o nó cabeça
      Node* getHead() const {
         return m_head; 
      }
  };

#endif
  