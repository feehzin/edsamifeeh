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
    SparseMatrix(int m, int n)
    {
      if(m <= 0 || n <= 0)
      {
        throw std::out_of_range("Numero de linhas e/ou colunas invalidas");
      }

      m_head->linhas = m;
      m_head->colunas = n;
      
      m_head = new Node(-1, -1, 0);
      
      if (m_head == nullptr)
      {
        throw std::out_of_range("Erro ao alocar memoria");
      }
      
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
    Node* atual_c = m_head->abaixo; // Recebe a primeira linha da matriz
    Node* auxguard = m_head; //auxguard guarda a linha anterior para possiveis inserções

    // Percorre as linhas ate encontrar a linha desejada ou passar por ela
    while(atual_c != m_head && atual_c->linhas < i){
      auxguard = atual_c; // Atualiza o ponteiro auxiliar para manter a referenca da linha anterior
      atual_c = atual_c->abaixo; // Move para proxima linha abaixo
    }

    // Verifica se a linha já existe ou precisa ser criada
    if(atual_c == m_head || atual_c->linhas != i){ // Cria uma nova linha, pois a linha i ainda não existe
      Node* novaLinha = new Node(i, -1, 0); // -1 na coluna indica o nó de controle da linha
      novaLinha->abaixo = atual_c; // O novo nó aponta para próxima linha
      auxguard->abaixo = novaLinha; // A linha anterioe aponta para a nova linha
      atual_c = novaLinha; // Atualiza a atual_c para apontar para a nova linha criada
    }
    // Ponteiros auxiliares para percorrer as colunas dentro da linha
    Node* atual = atual_c->direita; // Começa no primeiro elemento da linha
    Node* anterior = atual_c; // Guarda o nó anterior na linha

    // Percorre a linha ate achhar a coluna desejada ou passar por ela
    while(atual != atual_c && atual->colunas < j){ // O loop avança pelas colunas ate achar a posição de j ou passar por ela  
      anterior = atual; // Atualiza o ponteiro anterior para manter a referencia do nó anterior na linha
      atual = atual->direita; //Move para a proxima coluna 
    }

    // Verifica se o elemento já existe na posição i e j
    if(atual != atual_c && atual->colunas  == j){
      atual->valor = value; // Se já existe, atualiza o valor
      return;
    }

    // Se o elemeento não existe, se cria um novo nó para guardar o valor
    Node* novoNode = new Node(i, j, value); // Cria um nó novo com os valores fornecidos
    novoNode->direita = atual; // O novo nó aponta para o proximo elemento na linha
    anterior->direita = novoNode; // O nó anterior aponta para o novo nó , inoserindo ele corretamente
    }
    
    //Retorna um valor da matriz
    double get(int i, int j)
    {
      //verifica se os índices são válidos
      //senão, lança uma exceção
      if (i < 0 || i >= linhas || j < 0 || j >= colunas)
      {
        throw std::out_of_range("Indice(s) invalido(s)");
      }
      
      Node* aux = m_head->abaixo;
      
      //Percorre os nós (parte da coluna) até encontrar a linha i
      //aux->linhas < i, significa que não chegamos, então faz o aux continuar percorrendo
      while (aux != m_head && aux->linhas < i)
      {
        aux = aux->abaixo;
      }
      
      //se aux == m_head, significa que foi-se até o fim da matriz sem achar a linha
      //se aux->linhas != i,significa que a linha i não tem nenhum elemnto, diferente de zero, armazenado
      if (aux == m_head || aux->linhas != i)
      {
        return 0.0;
      }
      
      Node* elemento = aux->direita; //aux->direita nos leva ao primeiro elemto não nulo da linha

      //Percorre os nós à direita ate encontrar a coluna j
      //se elemento->colunas < j, significa que não chegou na coluna j, então faz o elemento continuar percorrendo
      while (elemento != aux && elemento->colunas < j)
      {
        elemento = elemento->direita;
      }
      
      //elemnto != aux nos garante que não retorne um elemento->valor não real
      //aux aponta como nó sentinela para a linha
      if (elemento != aux && elemento->colunas == j && elemento->linhas == i)
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
      for (int i = 0; i < linhas; i++)
      {
        for (int j = 0; i < colunas; i++)
        {
          double valor = get(i, j);
          std::cout << valor << " ";
        }
        std::cout << std::endl;
      }  
    }
      
    
};

#endif