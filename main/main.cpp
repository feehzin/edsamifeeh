#include <iostream>
#include <fstream>
#include <string>
#include "SparseMatrix.h"
using namespace std;

int main()
{
  void readSparseMatrix(SparseMatrix& m, std::string nome_do_arquivo)
  {
    ifstream arquivo(nome_do_arquivo);

    if (!arquivo.is_open())
    {
      cerr << "Erro: nao foi possivel abrir: " << nome_do_arquivo << endl;
      return;
    }
    
  }
}