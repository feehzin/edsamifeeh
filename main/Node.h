#ifndef NODE_H
#define NODE_H

/*Estrutura que representa um nó da mariz esparsa.
Cada nó armazena um valor não nulo e mantém ponteiros para
os próximos elementos na mesma linha e na mesma coluna.*/ 
{
  Node *direita; // Ponteiro para o próximo elemento da mesma linha.
  Node *abaixo; // Ponteiro  para o próximo elemento da mesma coluna.
  int linha; // Índice da linha do elemento.
  int coluns; // Índice da coluna do elemento.
  double valor; // Valor armazenado no nó (valor não nulo).

  /*Construtor que inicializa um nó com valores específicos.
  Os ponteiros direita e abaixo recebem ele mesmos(this), apontando para o próprio nó 
  (indicando que, inicialmente, forma-se uma lista circular para ele mesmo)*/
  Node(int linhas, int colunas, double valor)
    : direita{this}, abaixo{this}, linha{linha}, coluna{coluna}, valor{valor} {}
};

#endif