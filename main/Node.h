#ifndef NODE_H
#define NODE_H

struct Node
{
  Node *direita;
  Node *abaixo;
  int linha;
  int coluna;
  double valor;

  Node(int linha, int coluna, double valor)
    : direita{this}, abaixo{this}, linha{linha}, coluna{coluna}, valor{valor}
  {}
};

#endif

//direita e abaixo recebem ele mesmos, apontando para o próprio nó (indicando que, inicialmente, forma-se uma uma lista circular para ele mesmo)