#ifndef NODE_H
#define NODE_H

// Estrutura que representa um nó da mariz esparsa:
struct Node 
{
  Node *direita; // Ponteiro para o próximo elemento da mesma linha
  Node *abaixo; // Ponteiro  para o próximo elemento da mesma coluna
  int linhas; // Posição do elemento da matriz esparsa 
  int colunas; // Posição do elemento da matriz esparsa
  double valor; // Valor da matriz armazenado no nó (valor não nulo)

  /*Construtor que inicializa um nó com valores específicos
  Direita e abaixo recebem ele mesmos(this), apontando para o próprio nó 
  (indicando que, inicialmente, forma-se uma lista circular para ele mesmo)*/
  Node(int linhas, int colunas, double valor)
    : direita{this}, abaixo{this}, linhas{linhas}, colunas{colunas}, valor{valor} {}
};

#endif
