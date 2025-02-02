#include "SparseMatrix.h"
#include <iostream>
using namespace std;

int main() {
  
    void readSparseMatrix(SparseMatrix& m,std::string nomedoarquivo)
    {

    }

    SparseMatrix sum(SparseMatrix&A, SparseMatrix&B)
    {
        SparseMatrix C;

        for (int i = 0; i < A.m_head->linhas; i++)
        {
            for (int j = 0; j < A.m_head->colunas; j++)
            {
                double soma += A.get(i, j) + B.get(i, j)
            }
        }

    }

    SparseMatrix multiply(SparseMatrix&A, SparseMatrix&B)
    {

    }

    return 0;
}

