#include "tests.h"
#include "matrix.h"

int testMatrixLogic()
{
        if (-1 == testMatrixFill())
        {
                return -1;
        }
        if (-1 == testMatrixSum())
        {
                return -1;
        }
        if (-1 == testMatrixMult())
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
                                printf("ERR: то что записали не соответствует тому что прочитали\n");
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
        if (ok = matrixInit(&m1, 20, 20, sizeof(int), numberSum, NULL, NULL) != 0)
        {
                return -1;
        }
        if (ok = matrixInit(&m2, 20, 20, sizeof(int), numberSum, NULL, NULL) != 0)
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
                printf("ERR: ошибка операции сложения, код %d\n", ok);
                return -1;
        }
        for (int i = 0; i < 20; i++)
                for (int j = 0; j < 20; j++)
                {
                        int *val;
                        val = (int *)getMatrixElement(&result, i, j);
                        if (*val != 3)
                        {
                                printf("ERR: результат сложения 1+2 не ревен 3\n");
                                return -1;
                        }
                }
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
        if (ok = matrixInit(&m1, 3, 3, sizeof(int), numberSum, numberMult, NULL) != 0)
        {
                return -1;
        }
        if (ok = matrixInit(&m2, 3, 3, sizeof(int), numberSum, numberMult, NULL) != 0)
        {
                return -1;
        }

        for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                {
                        int val1 = 2;
                        int val2 = 3;
                        setMatrixElement(&m1, i, j, &val1);
                        setMatrixElement(&m2, i, j, &val2);
                }
        if (ok = matrixMult(&result, &m1, &m2) != 0)
        {
                printf("ERR: ошибка операции умножения, код %d\n", ok);
                return -1;
        }
        for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                {
                        int *val;
                        val = (int *)getMatrixElement(&result, i, j);
                        if (*val != 18)
                        {
                                printf("ERR: результат умножения не соответствует ожиданиям. [%d][%d]=%d, ожидалось %d\n", i, j, *val, 18);
                                return -1;
                        }
                }
        matrixFree(&m1);
        matrixFree(&m2);
        matrixFree(&result);
        return 0;
}