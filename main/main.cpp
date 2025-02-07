#include <iostream>
#include <fstream> //Biblioteca para ler arquivo texto
#include <string>
#include <stdexcept> // Biblioteca para lançar exceções
#include <algorithm> // Biblioteca para retornar o menor valor entre A e B
#include <vector>
#include <sstream>
#include "SparseMatrix.h"
using namespace std;

void criar(istringstream ss){
  int M, N;
  ss >> M >> N;

  if (M > 0 && N > 0)
  {
    matrix.push_back(SparseMatrix(M, N));
    cout << "Matriz "<< matriz.size() - 1 << "adicionada com sucesso!" << endl;
  }
  else {
    throw out_of_range("Dimensoes da matriz sao invalidas");
  }
}

void readSparseMatrix(SparseMatrix& m, std::string nome_do_arquivo){
    ifstream arquivo;

    arquivo.open(nome_do_arquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro: nao foi possivel abrir: " << nome_do_arquivo << endl;
        return;
    }

    int linhas, colunas;
    arquivo >> linhas >> colunas;

    if (linhas != m.getLinhas() || colunas != m.getColunas()){
        cerr << "Erro: dimensoes do arquivo nao correspodem a matriz dada" << endl; //o uso de cerr é para mensagens de erro
        arquivo.close();
        return;
    }
    
    int i, j;
    double valor;

    while (arquivo >> i >> j >> valor){
        if (i < 1 || i > linhas || j < 1 || j > colunas){
            cerr << "Erro: indices fora do limite esperado (" << linhas << ", " << colunas << ")" << endl;
            continue;
        }
      
        if (valor == 0){
            continue;
        }
      
        m.insert(i, j, valor);
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
      Node* coluna_B = linha_A->direita; // Primeira coluna da linha de A
      Node* coluna_A = linha_B->direita; // Primeira linha de B
      while(coluna_A != linha_A && coluna_B != linha_B){
        if(coluna_A->colunas == coluna_B->colunas){ // Se as colunas forem iguais, soma os valores
          double soma = coluna_A->valor + coluna_B->valor;
          if(soma != 0){
            C.inserte(coluna_A->linhas, coluna_A->colunas, soma);
          }
          coluna_A = coluna_A->direita; // Avança para a próxima coluna de A
          coluna_B = coluna_B->direita; // Avança para a próxima coluna de B
        }
        else if(coluna_A->colunas < coluna_B->colunas){
          // Se a coluna A for melhor, insere o valor de A 
          C.insert(coluna_A->linhas, coluna_A->colunas, coluna_A->valor);
          coluna_A = coluna_A->direita; // Avança para a próxima coluna de A
        }else{
          // Se a coluna de B for menor, insere a o valor eem B
          C.insert(coluna_B->linhas, coluna_B->colunas, coluna_B->valor);
          coluna_B = coluna_B->direita; // Avança para a próximma coluna de B
        }
      }
      // Adicionam as colunas restantes de A e B, se houver
      while(coluna_A != linha_A){
        C.inserte(coluna_A->linhas, coluna_A->colunas, coluna_A->valor);
        caluna_A = coluna_A->direita;
      }
      while(coluna_B != linha_B){
        C.inserte(coluna_B->linhas, coluna_B->colunas, coluna_B->valor);
        coluna_B = coluna_B->direita;
      }
      // Avança para a próxima linha de A e B
      linha_A = linha_A->abaixo;
      linha_B = linha_B->abaixo;
    }
    return C;
  }

     
 SparseMatrix multiply(SparseMatrix& A, SNodeparseMatrix& B){
    if (A.getColunas()!= B.getLinhas()){
      throw std::out_of_range("O número de colunas de A deve ser igual ao número de  linhas de B para executar a multiplicação.");
    }

    SparseMatrix C(A.getLinhas(), B.getColunas());  

    // loop para percorrer todas a linhas de A
    for(Node* element_A = A.getHead()->abaixo; linha_A != A.getHead(); linha_A = linha_A->abaixo){
      int i = element_A->linhas;
      int j = element_A->colunas;
      double valorA = element_A->valor;
    }
  }

int main()
{
  vector<SparseMatrix> matriz;

  cout << "------- Sistema de Matrix -------" << endl
       << "Digite 'ajuda' para ver a lista de comandos" << endl;
  
  while (true) {
    string comando;
    getline(cin, comando);

    istringstream ss(comando);
    string cmd;

    ss >> cmd;

    if(cmd == "ajuda")
    {
      cout << "------------------------------------ Lista de Comandos------------------------------------" << endl
           << "criar matriz M N......... criar matriz vazia com M linhas e N colunas" << endl
           << "ler m.txt................ le arquivo de texto, armazenando seus parametros em uma matriz"
           << "mostre matriz A.......... mostra a matriz A" << endl
           << "somar matrizes A B....... soma a matriz A com a matriz B" << endl
           << "multi matrizes A B....... multiplica a matriz A com a matriz B" << endl
           << "mudar A i j valor........ substitui o valor no indice i (linha), j (coluna) na matriz A" << endl
           << "listar................... mostra todas as matrizes do sistema"
           << "limpar matriz A.......... limpa a matriz A" << endl
           << "limparM.................. limpa todas as matrizes do sistema" << endl
           << "sair..................... terminar sessao" << endl
           << "-------------------------------------------------------------------------------------------" << endl;
    }
    else if(cmd == "criar"){
      criar(ss);
    }
    else if(cmd == "ler"){
      string arquivo;
      ss >> arquivo;

      

      SparseMatrix m(0, 0);
      readSparseMatrix(m, arquivo);
      matriz.push_back(m);

      cout << "Nova matriz, com parametros do arquivo (" << arquivo << ") listada no sistema com sucesso!" << endl;
    }
    else if(cmd == "mostre"){
      int A;
      ss >> A;

      if (A > 0 && A < matriz.size()){
        matriz[A].print();
      }
      else {
        throw out_of_range("A matriz com o indice [" << A << "] nao encontra-se listada no sistema.");

        char n;
        cout << "gostaria de adiciona-la? [y/n]: ";
        cin << n;

        if (n == 'y')
        {
          criar(ss);
        }
        else {
          cout << "Operacao nao realizada." << endl;
        }
      }
    } 
    else if(cmd == "somar"){
      int A, B;
      ss >> A >> B;

      if (A >= 0 && A < matriz.size() && B >= 0 && B < matriz.size()){
        SparseMatrix resultado = sum(matriz[A],matriz[B]);
        matriz.push_back(resultado);
        matriz.back().print();
      }
      else {
        throw out_of_range("Indices passados sao invalidos.") << endl;
      }
    }
    else if(cmd == "multi"){
      int A, B;
      ss >> A >> B;

      if (A >= 0 && A < matriz.size() && B >= 0 && B < matriz.size()){
        SparseMatrix resultado = multiply(matriz[A],matriz[B]);
        matriz.push_back(resultado);
        matriz.back().print();
      }
      else {
        throw out_of_range("Indices passados sao invalidos.") << endl;
      }
    }
    else if(cmd == "mudar"){
      int A, i, j, value;
      ss >> A >> i >> j >> 0;

      if (A >= 0 && A < matriz.size() && i > 1 && i <= matriz[A].getLinhas() && j > 1 && j <= matriz[A].getColunas())
      {
        matriz[A].insert(i, j);

        cout << "Valor atualizado na matriz[" << A << "] com sucesso!" << endl;
      }
      else {
        throw out_of_range("Dados passados nao correspodem a alguma matriz no sistema.")
      }
    }
    else if(cmd == "limpar")
    {
      int A;
      ss >> A;

      if (A >= 0 && A < matriz.size())
      {
        matriz[A].clear();

        cout << "Matriz[" << A << "] limpa com sucesso" << endl;
      }
      else {
        throw out_of_range("Indice passado nao valido!");
      }
    }
    else if(cmd == "limparM"){
      for (int i = 0; i < matriz.size(); i++)
      {
        matriz[i].clear();
      }
      cout << "Sistema limpo com sucesso!" << endl;
    }
    else if (cmd == "listar")
    {
      for (int i = 0; i < matriz.size(); i++)
      {
        matriz[i].print();
        cout << endl;
      }
      cout << "Todas as matrizes foram mostradas com sucesso!" << endl;
    }
    
  }
} 
