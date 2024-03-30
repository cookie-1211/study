#include "matrix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
    с-код, реализующий интерфейс для работы с векторами
*/

int matrixInit(Matrix *v, size_t rows, size_t columns, size_t elemSize, SumMatrixElements sumElements, MultMatrixElements multElements, PrintMatrixElement printElement)
{
    v->data = calloc(columns * rows, elemSize);
    if (v->data == NULL)
    {
        return -1;
        // ошибка выделения памяти
    }
    v->columns = columns;
    v->rows = rows;
    v->elemSize = elemSize;
    v->sumElements = sumElements;
    v->multElements = multElements;
    v->printElement = printElement;
    return 0;
}

void matrixFree(Matrix *v)
{
    free(v->data);
    v->data = NULL;
}

int setMatrixElement(Matrix *v, size_t row, size_t column, const void *value)
{
    if (column > v->columns || row > v->rows)
    {
        // index out fo range
        return -1;
    }
    size_t index = (row * v->columns + column) * v->elemSize;
    memcpy(v->data + index, value, v->elemSize);
    return 0;
}

void *getMatrixElement(const Matrix *v, size_t row, size_t column)
{
    if (column > v->columns || row > v->rows)
    {
        // index out fo range
        return NULL;
    }
    size_t index = (row * v->columns + column) * v->elemSize;
    return v->data + index;
}

int matrixSum(Matrix *res, const Matrix *v1, const Matrix *v2)
{
    int ok = 0;
    if (v1->columns != v2->columns || v1->rows != v2->rows || v1->elemSize != v2->elemSize)
    {
        // Матрицы должны иметь одинаковые размеры и тип элементов для выполнения сложения
        // написать разные ошибки
        return -1;
    }
    if (ok = matrixInit(res, v1->columns, v1->rows, v1->elemSize, v1->sumElements, v1->multElements, v1->printElement) != 0)
    {
        return -2;
    }

    size_t numElements = v1->columns * v1->rows;
    for (size_t i = 0; i < numElements; i++)
    {
        v1->sumElements(res->data + i * res->elemSize, v1->data + i * v1->elemSize, v2->data + i * v2->elemSize);
    }
    return 0;
}

int matrixMult(Matrix *res, const Matrix *v1, const Matrix *v2)
{
    int ok;
    if (v1->columns != v2->rows || v1->elemSize != v2->elemSize)
    {
        // Умножение матриц возможно только если количество столбцов первой матрицы равно количеству строк второй матрицы
        // и если тип элементов в матрицах одинаковый
        return -1;
    }

    size_t resRows = v1->rows;
    size_t resColumns = v2->columns;
    size_t elemSize = v1->elemSize;

    // Выделяем память под результирующую матрицу

    if (ok = matrixInit(res, resColumns, resRows, elemSize, v1->sumElements, v1->multElements, v1->printElement) != 0)
    {
        return -2;
    }

    // Устанавливаем параметры результирующей матрицы
    res->rows = resRows;
    res->columns = resColumns;
    res->elemSize = elemSize;
    res->sumElements = v1->sumElements;
    res->multElements = v1->multElements;
    res->printElement = v1->printElement;

    void *tmp1 = calloc(1, elemSize);
    void *tmp2 = calloc(1, elemSize);
    // Вычисление умножения матриц
    for (size_t i = 0; i < resRows; i++)
    {
        for (size_t j = 0; j < resColumns; j++)
        {
            for (size_t k = 0; k < v1->columns; k++)
            {
                res->multElements(tmp1, getMatrixElement(v1, i, k), getMatrixElement(v2, k, j));
                res->sumElements(tmp2, getMatrixElement(res, i, j), tmp1);
                setMatrixElement(res, i, j, tmp2);
            }
        }
    }
    free(tmp1);
    free(tmp2);
    return 0;
}

void matrixPrintElements(const Matrix *v)
{
    for (size_t row = 0; row < v->rows; row++)
    {
        for (size_t col = 0; col < v->columns; col++)
        {
            v->printElement(getMatrixElement(v, row, col));
        }
        printf("\n");
    }
}

void matrixAddToCollection(MatrixCollection *collection,
                           const char *name,
                           size_t rows,
                           size_t columns,
                           size_t elemSize,
                           SumMatrixElements addFunc,
                           MultMatrixElements multFunc,
                           PrintMatrixElement printFunc)
{
    collection->matrices = realloc(collection->matrices, (collection->size + 1) * sizeof(NamedMatrix));
    NamedMatrix *newMatrix = &collection->matrices[collection->size];
    strncpy(newMatrix->name, name, sizeof(newMatrix->name));
    matrixInit(&newMatrix->matrix, rows, columns, elemSize, addFunc, multFunc, printFunc);
    collection->size++;
}

Matrix *matrixFindInCollection(MatrixCollection *collection, const char *name)
{
    for (size_t i = 0; i < collection->size; i++)
    {
        if (strcmp(collection->matrices[i].name, name) == 0)
        {
            return &collection->matrices[i].matrix;
        }
    }
    return NULL; // Не найден
}

int matrixT(Matrix *v)
{
    Matrix tmp;
    int ok;
    if (ok = matrixInit(&tmp, v->columns, v->rows, v->elemSize, NULL, NULL, NULL) != 0)
    {
        // failed init tmp matrix
        return -1;
    }
    for (size_t row = 0; row < v->rows; row++)
    {
        for (size_t col = 0; col < v->columns; col++)
        {
            setMatrixElement(&tmp, col, row, getMatrixElement(v, row, col));
        }
    }
    matrixFree(v);
    v->data = tmp.data;
    v->rows = tmp.rows;
    v->columns = tmp.columns;

    return 0;
}