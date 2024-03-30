#include "tests.h"
#include "matrix.h"

int testMatrixLogic()
{
    if (testMatrixFill() != 0)
    {
        return -1;
    }
    if (testMatrixSum() != 0)
    {
        return -1;
    }
    if (testMatrixMult() != 0)
    {
        return -1;
    }
    if (testMatrixT() != 0)
    {
        return -1;
    }
    return 0;
}
int testMatrixFill()
{
    Matrix m;
    int ok;
    ok = matrixInit(&m, 20, 20, sizeof(int), NULL, NULL, NULL);
    if (ok != 0)
    {
        return -1;
    }

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            int val = i + j;
            setMatrixElement(&m, i, j, &val);
        }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            int *val;
            val = (int *)getMatrixElement(&m, i, j);
            if (*val != i + j)
            {
                printf("ERR: unexpected result when reading written data\n");
                return -1;
            }
        }
    }
    matrixFree(&m);
    return 0;
}

int testMatrixSum()
{
    Matrix m1;
    Matrix m2;
    Matrix result;
    int ok;
    if (ok = matrixInit(&m1, 20, 20, sizeof(int), numberSum, NULL, numberPrint) != 0)
    {
        return -1;
    }
    if (ok = matrixInit(&m2, 20, 20, sizeof(int), numberSum, NULL, numberPrint) != 0)
    {
        return -1;
    }

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            int val1 = 1;
            int val2 = 2;
            setMatrixElement(&m1, i, j, &val1);
            setMatrixElement(&m2, i, j, &val2);
        }
    if (ok = matrixSum(&result, &m1, &m2) != 0)
    {
        printf("ERR: summ error, code %d\n", ok);
        return -1;
    }
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            int *val;
            val = (int *)getMatrixElement(&result, i, j);
            if (*val != 3)
            {
                printf("ERR: unexpected summing result\n");
                return -1;
            }
        }
    // matrixPrintElements(&result);
    matrixFree(&m1);
    matrixFree(&m2);
    matrixFree(&result);
    return 0;
}

int testMatrixMult()
{
    Matrix m1;
    Matrix m2;
    Matrix result;
    int ok;
    if (ok = matrixInit(&m1, 3, 2, sizeof(int), numberSum, numberMult, numberPrint) != 0)
    {
        return -1;
    }
    if (ok = matrixInit(&m2, 2, 3, sizeof(int), numberSum, numberMult, numberPrint) != 0)
    {
        return -1;
    }

    for (int row = 0, v = 0; row < m1.rows; row++)
        for (int col = 0; col < m1.columns; col++)
        {
            v++;
            setMatrixElement(&m1, row, col, &v);
        }
    // matrixPrintElements(&m1);

    for (int row = 0, v = 0; row < m2.rows; row++)
        for (int col = 0; col < m2.columns; col++)
        {
            v++;
            setMatrixElement(&m2, row, col, &v);
        }
    // matrixPrintElements(&m2);

    if (ok = matrixMult(&result, &m1, &m2) != 0)
    {
        printf("ERR: multilplication error, code %d\n", ok);
        return -1;
    }
    // matrixPrintElements(&result);

    int reference[3][3] = {{9, 12, 15},
                           {19, 26, 33},
                           {29, 40, 51}};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int *val;
            val = (int *)getMatrixElement(&result, i, j);
            if (*val != reference[i][j])
            {
                printf("ERR: Unexpected multiply result. [%d][%d]=%d, expected %d\n", i, j, *val, reference[i][j]);
                return -1;
            }
        }
    }

    matrixFree(&m1);
    matrixFree(&m2);
    matrixFree(&result);
    return 0;
}

int testMatrixT()
{
    Matrix m;
    int ok;
    if (ok = matrixInit(&m, 2, 3, sizeof(int), numberSum, numberMult, numberPrint) != 0)
    {
        return -1;
    }

    for (int row = 0, v = 0; row < m.rows; row++)
        for (int col = 0; col < m.columns; col++)
        {
            v++;
            setMatrixElement(&m, row, col, &v);
        }
    // matrixPrintElements(&m);

    int reference[3][2] = {{1, 4},
                           {2, 5},
                           {3, 6}};
    matrixT(&m);
    // matrixPrintElements(&m);

    if (m.rows != 3 || m.columns != 2)
    {
        return -1;
    }
    for (int row = 0; row < m.rows; row++)
    {
        for (int col = 0; col < m.columns; col++)
        {
            int *val;
            val = (int *)getMatrixElement(&m, row, col);
            if (*val != reference[row][col])
            {
                printf("ERR: Unexpected transpose result. [%d][%d]=%d, expected %d\n", row, col, *val, reference[row][col]);
                return -2;
            }
        }
    }


    matrixFree(&m);
    return 0;
}