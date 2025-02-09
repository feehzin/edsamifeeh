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

    // Construtor de cópia (cópia profunda)
    SparseMatrix(const SparseMatrix& mat) {
      linhas = mat.linhas;
      colunas = mat.colunas;
      m_head = new Node(0, 0, 0);
      m_head->direita = m_head;
      m_head->abaixo = m_head;

      // Copia os elementos não nulos da outra matriz
      Node* matM_Head = mat.m_head->abaixo;
      while (matM_Head != mat.m_head) {
          Node* matElem = matM_Head->direita;
          while (matElem != matM_Head) {
            this->insert(matElem->linha, matElem->coluna, matElem->valor);
            matElem = matElem->direita;
          }
          matM_Head = matM_Head->abaixo;
      }
    }

    // Operador de atribuição (para cópia profunda)
    SparseMatrix& operator=(const SparseMatrix& other) {
      if (this != &other) {
          clear();
          linhas = other.linhas;
          colunas = other.colunas;
          Node* otherRow = other.m_head->abaixo;
          while (otherRow != other.m_head) {
              Node* otherElem = otherRow->direita;
              while (otherElem != otherRow) {
                  this->insert(otherElem->linha, otherElem->coluna, otherElem->valor);
                  otherElem = otherElem->direita;
              }
              otherRow = otherRow->abaixo;
          }
      }
      return *this;
  }
  
    //Destrutor: libera a memória alocada dinamicamente.
    ~SparseMatrix() {
      clear();
      delete m_head;
  }
    // Retorna o número de linhas de uma matriz.
    int getLinhas() const { 
      return linhas; 
    }

    // Retorna o número de colunas de uma matriz.
    int getColunas() const {
       return colunas; 
    }
  
    // Retorna o ponteiro para o nó sentinela da matriz.
    Node* getHead() const {
       return m_head; 
    }

    // Função que insere um valor na matriz esparsa
    void insert(int i, int j, double value){
    if (value == 0) return;
    if (i < 1 || i > linhas || j < 1 || j > colunas) {
      throw std::out_of_range("Índices fora dos limites da matriz.");
    }
    Node* prev_L = m_head;
    Node* atual_L = m_head->abaixo;
    while (atual_L != m_head && atual_L->abaixo->linha < i) {
      prev_L = atual_L;
      atual_L = atual_L->abaixo;
    }
    if (atual_L == m_head || atual_L->linha != i) {
      Node* novaLinha = new Node(i, 0, 0);
      novaLinha->abaixo = atual_L;
      prev_L->abaixo = novaLinha;
      novaLinha->direita = novaLinha;
      atual_L = novaLinha;
    }
    
    Node* prevElem = atual_L;
    Node* currElem = atual_L->direita;
    while (currElem != atual_L && currElem->coluna < j) {
      prevElem = currElem;
      currElem = currElem->direita;
    }
    if (currElem != atual_L && currElem->coluna == j) {
      // Se o elemento já existe, atualiza seu valor
      currElem->valor = value;
    }
    else {
      // Insere um novo nó na posição correta
      Node* newNode = new Node(i, j, value);
      newNode->direita = currElem;
      prevElem->direita = newNode;
    }
}
    // Retorna um valor específico da matriz.
    double get(int i, int j) const {
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

    //Limpa a matriz, setando todos os seus valores para 0.0.
    void clear() {
       // Limpa as linhas
    Node* rowHead = m_head->abaixo;  // Começa da primeira linha (abaixo do sentinela)
    while (rowHead != m_head) {      // Enquanto não chegar ao sentinela
        Node* current = rowHead->direita;  // Primeira célula da linha
        while (current != rowHead) {       // Enquanto não voltar ao cabeçalho da linha
            Node* temp = current;
            current = current->direita;    // Move para o próximo elemento na linha
            delete temp;  // Libera o nó
        }
        Node* tempRow = rowHead;
        rowHead = rowHead->abaixo;  // Move para a próxima linha
        delete tempRow;  // Libera o cabeçalho da linha
    }

    // Limpa as colunas
    Node* colHead = m_head->direita;  // Começa da primeira coluna (direita do sentinela)
    while (colHead != m_head) {       // Enquanto não chegar ao sentinela
        Node* current = colHead->abaixo;  // Primeira célula da coluna
        while (current != colHead) {       // Enquanto não voltar ao cabeçalho da coluna
            Node* temp = current;
            current = current->abaixo;    // Move para o próximo elemento na coluna
            delete temp;  // Libera o nó
        }
        Node* tempCol = colHead;
        colHead = colHead->direita;  // Move para a próxima coluna
        delete tempCol;  // Libera o cabeçalho da coluna
    }

    // Libera o nó sentinela
    delete m_head;
    }
  
};

#endif
