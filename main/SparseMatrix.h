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

      m_head->linhas = linhas;
      m_head->colunas = colunas;

      m_head = (Node *)malloc(sizeof(Node));
      if (m_head == nullptr)
      {
        throw std::out_of_range("Erro ao alocar memoria");
      }
      
      m_head = new Node(0, 0, 0);
      m_head->direita = m_head; //aponta para si mesmo
      m_head->abaixo = m_head; //aponta para si mesmo
    }

    //Destrutor: libera a memória alocada
    ~SparseMatrix() {
      if(!m_head) {
        throw std::out_of_range("Lista vazia");
      } 

      Node* atual_c = m_head->abaixo; //recebe a primeira linha

      //percorre as linhas da matriz
      while(atual_c != m_head) {
      
        Node* atual_l = m_head->direita;

        //percorre até retornar para o início da linha
        while (atual_l != atual_c)
        {
          Node* aux_l = atual_l->direita; //guarda o prócimo nó antes de deletá-lo
          delete atual_l;
          atual_l = aux_l; //atual_l avança para o próximo nó
        }

        Node* aux_c = atual_c->abaixo; //guarda a próxima linha antes de deletar o atual
        delete atual_c; // deleta o nó da coluna
        atual_c = aux_c; //avança para a próxima coluna
      }

      delete m_head;
      m_head = nullptr;
    }
       
    //Função que insere um valor na matriz esparsa
    void insert(int i, int j, double value)
    {
      if(value == 0) {
       // Não aceita inserir 0 na matriz
      throw std::out_of_range("Valor invalido");
      }
      
      if(i < 0 || i >= linhas || j < 0 || j >= colunas){ 
        // Impede que os indices acessados sejam negativos ou indices que a matriz nao suporta 
      throw std::out_of_range("Indices invalidos");
    }
    // Ponteiros auxiliares que percorre a lista de linhas
    Node* atual_c = m_head->abaixo;
    Node* auxguard = m_head; //auxguard guarda a linha anterior
    


    }
    
    //Retorna um valor da matriz
    double get(int i, int j)
    {
      if (i < 0 || i >= linhas || j < 0 || j >= colunas)
      {
        throw std::out_of_range("Indice(s) invalido(s)");
      }
      
      Node* aux = m_head->abaixo;

      if (aux == m_head || aux->linhas != i)
      {
        return 0.0;
      }
      
      Node* elemento = aux->direita;

      while (elemento != aux && elemento->colunas < j)
      {
        elemento = elemento->direita;
      }
      
      if (elemento != aux && elemento->colunas == j)
      {
        return elemento->valor;
      }
      else
      {
        return 0.0;
      }
    }

    //Exibe a matriz no terminal
    void print()
    {

    }
      
    
};

#endif