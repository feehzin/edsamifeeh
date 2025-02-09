#include <iostream>
#include <fstream> //Biblioteca para ler arquivo texto
#include <string>
#include <stdexcept> // Biblioteca para lançar exceções
#include <algorithm> // Biblioteca para retornar o menor valor entre A e B
#include <vector>
#include <sstream>
#include "SparseMatrix.h"
using namespace std;

void readSparseMatrix(SparseMatrix& m, std::string& nome_do_arquivo) {
  ifstream arquivo(nome_do_arquivo);
  
  if (!arquivo.is_open()) {
      cerr << "Erro: não foi possível abrir o arquivo " << nome_do_arquivo << endl;
      return;
  }

  int linhas, colunas;
  arquivo >> linhas >> colunas;

  int i, j;
  double valor;

  while (arquivo >> i >> j >> valor) {
      if (i < 1 || i > linhas || j < 1 || j > colunas) {
          cerr << "Erro: índices fora do limite esperado (" << linhas << ", " << colunas << ")" << endl;
          continue;
      }

      m->insert(i, j, valor);  // Insere diretamente sem verificar se é zero, pois a matriz já não armazena zeros
  }
  
  arquivo.close();
}
  
  /**Função que soma matrizes esparsas */
  SparseMatrix sum(SparseMatrix& A, SparseMatrix& B){
    // Verificar se as matrizes são da mesma dimensão(tamanho)
    if(A.getLinhas() != B.getLinhas()|| A.getColunas()!= B.getColunas()){
      throw out_of_range("As matrizes devem ter o mesmo tamanho para a função de soma.");
    }
    
    // Cria uma matriz para guardar o resultado com as mesmas dimensões de A e B
    SparseMatrix C(A.getLinhas(), A.getColunas());

    // Ponteiros para percorrer as linhas das matrizes A e B
    Node* linha_A = A.getHead()->abaixo; // Começa na primeira linha de A
    Node* linha_B = B.getHead()->abaixo; // Começa na primeira linha de B

    // Percorre as linhas das matrizes A e B
    while(linha_A != A.getHead()){
      Node* coluna_A = linha_A->direita; // Primeira coluna da linha de A
      Node* coluna_B = linha_B->direita; // Primeira linha de B
      while(coluna_A != linha_A && coluna_B != linha_B){
        if(coluna_A->coluna == coluna_B->coluna){ // Se as colunas forem iguais, soma os valores
          double soma = coluna_A->valor + coluna_B->valor;
          if(soma != 0){
            C.insert(coluna_A->linha, coluna_A->coluna, soma);
          }
          coluna_A = coluna_A->direita; // Avança para a próxima coluna de A
          coluna_B = coluna_B->direita; // Avança para a próxima coluna de B
        }
        else if(coluna_A->coluna < coluna_B->coluna){
          // Se a coluna A for melhor, insere o valor de A 
          C.insert(coluna_A->linha, coluna_A->coluna, coluna_A->valor);
          coluna_A = coluna_A->direita; // Avança para a próxima coluna de A
        }else{
          // Se a coluna de B for menor, insere a o valor eem B
          C.insert(coluna_B->linha, coluna_B->coluna, coluna_B->valor);
          coluna_B = coluna_B->direita; // Avança para a próximma coluna de B
        }
      }
      // Adicionam as colunas restantes de A e B, se houver
      while(coluna_A != linha_A){
        C.insert(coluna_A->linha, coluna_A->coluna, coluna_A->valor);
        coluna_A = coluna_A->direita;
      }
      while(coluna_B != linha_B){
        C.insert(coluna_B->linha, coluna_B->coluna, coluna_B->valor);
        coluna_B = coluna_B->direita;
      }
      // Avança para a próxima linha de A e B
      linha_A = linha_A->abaixo;
      linha_B = linha_B->abaixo;
    }
    return C;
  }

     
SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B){
  if (A.getColunas()!= B.getLinhas()){
    throw std::out_of_range("O número de colunas de A deve ser igual ao número de  linhas de B para executar a multiplicação.");
  }

  SparseMatrix C(A.getLinhas(), B.getColunas());  

  // percorre todas as linhas de A
  for(Node* linha_A = A.getHead()->abaixo; linha_A != A.getHead(); linha_A = linha_A->abaixo){
    // Percorre todos os elementos da linha A
    for(Node* element_A = linha_A->direita; element_A != linha_A; element_A = element_A->direita){
    int i = element_A->linha;
    int j = element_A->coluna;
    double valor_A = element_A->valor;

    // Percorre a coluna correspondente em B
    Node* coluna_B = B.getHead()->abaixo;
    while(coluna_B->linha != j && coluna_B != B.getHead()){
      coluna_B = coluna_B->abaixo;
    }
    if(coluna_B->linha == j){
      for(Node* element_B = coluna_B->direita; element_B != coluna_B; element_B = element_B->direita){
        int s = element_B->coluna;
        double valor_B = element_B->valor;

        double valorC = C.get(i, s) + (valor_A * valor_B);
        C.insert(i, s, valorC);
        }
      }
    }
  }
  return C;
}

int main()
{
  vector<SparseMatrix> matriz;

  cout << "------- Sistema de Matrix -------" << endl
       << "Digite 'ajuda' para ver a lista de comandos" << endl;
  
  string comando;

  while (getline(cin, comando)) {
    istringstream ss(comando);
    string cmd;
    ss >> cmd;

    if(cmd == "ajuda")
    {
      cout << "------------------------------------ Lista de Comandos------------------------------------" << endl
           << "criar M N................ criar matriz vazia com M linhas e N colunas" << endl
           << "ler m.txt................ ler arquivo de texto, armazenando seus parametros em uma matriz" << endl
           << "mostre A................. mostra a matriz A" << endl
           << "somar A B................ soma a matriz A com a matriz B" << endl
           << "multi A B................ multiplica a matriz A com a matriz B" << endl
           << "mudar A i j valor........ substitui o valor no indice i (linha), j (coluna) na matriz A" << endl
           << "listar................... mostra todas as matrizes do sistema"
           << "limpar A................. limpa a matriz A" << endl
           << "limparM.................. limpa todas as matrizes do sistema" << endl
           << "sair..................... terminar sessao" << endl
           << "-------------------------------------------------------------------------------------------" << endl;
    }
    else if(cmd == "criar"){
      int M, N;
      ss >> M >> N;

      if (M > 0 && N > 0) {
        SparseMatrix novaMatriz(M, N); 
        matriz.push_back(novaMatriz);
        cout << "Matriz " << matriz.size() - 1 << " adicionada com sucesso!" << endl;
      } 
      else {
        throw std::out_of_range("Dimensoes da matriz sao invalidas");
      }
    }
    else if(cmd == "ler"){
      string nomeArquivo;
      ss >> nomeArquivo;
      
      int linhas, colunas;

      ifstream arquivo(nomeArquivo);
      if (!arquivo.is_open()) {
        cout << "Erro: nao foi possivel abrir o arquivo " << nomeArquivo << endl;
        continue;
      }
      
      arquivo >> linhas >> colunas;
      arquivo.close();

      SparseMatrix m(linhas, colunas);
      readSparseMatrix(m, nomeArquivo);
      matriz.push_back(m);

      cout << "Nova matriz, com parametros do arquivo (" << nomeArquivo << ") listada no sistema com sucesso!" << endl;
    }
    else if(cmd == "mostre"){
      int A;
      ss >> A;

      if (A >= 0 && A < matriz.size()){
        matriz[A].print();
      }
      else {
        throw out_of_range("A matriz com o indice passado nao encontra-se listada no sistema.");
      }
    } 
    else if(cmd == "somar"){
      int A, B;
      ss >> A >> B;

      if (A >= 0 && A < matriz.size() && B >= 0 && B < matriz.size()){
        SparseMatrix resultado = sum(matriz[A],matriz[B]);
        matriz.push_back(resultado);

        cout << "Resultado da soma:" << endl;
        matriz.back().print();
      }
      else {
        throw out_of_range("Indices passados sao invalidos.");
      }
    }
    else if(cmd == "multi"){
      int A, B;
      ss >> A >> B;

      if (A >= 1 && A < matriz.size() && B >= 1 && B < matriz.size()){
        SparseMatrix resultado = multiply(matriz[A],matriz[B]);
        matriz.push_back(resultado);

        cout << "Resultado da multiplicacao:" << endl;
        matriz.back().print();
      }
      else {
        throw out_of_range("Indices passados sao invalidos.");
      }
    }
    else if(cmd == "mudar"){
      unsigned A, i, j;
      double valor;
      ss >> A >> i >> j >> valor;

      if (A >= 0 && A < matriz.size() && i > 1 && i <= matriz[A].getLinhas() && j > 1 && j <= matriz[A].getColunas())
      {
        matriz[A].insert(i, j, valor);

        cout << "Valor atualizado na matriz[" << A << "] com sucesso!" << endl;
      }
      else {
        throw out_of_range("Dados passados nao correspodem a alguma matriz no sistema.");
      }
    }
    else if (cmd == "limpar") {
      int A;
      ss >> A;
  
      if (A >= 0 && A < matriz.size()) {
        matriz.erase(matriz.begin() + A);
        cout << "Matriz[" << A << "] foi removida do sistema!" << endl;
      } 
      else {
        throw std::out_of_range("Índice passado nao valido!");
      }
    }
    else if (cmd == "limparM") {
      if (matriz.empty()) {
        cout << "Não há matrizes para limpar." << endl;
      } 
      else {
        matriz.clear();  // Remove todos os ponteiros do vetor
        cout << "Todas as matrizes foram removidas do sistema!" << endl;
      }
  }
    else if (cmd == "listar"){
      for (unsigned i = 0; i < matriz.size(); i++)
      {
        cout << "Matriz[" << i << "]:" << endl;
        matriz[i].print();
        cout << endl;
      }
      cout << "Todas as matrizes foram mostradas com sucesso!" << endl;
    }
    else if (cmd == "sair") {
      cout << "saindo..." << endl;
      break;
    }
    else {
      cout << "Comando não reconhecido. Digite 'ajuda' para ver a lista de comandos." << endl;
    }
  }
}
