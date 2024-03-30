#include "matrix.h"
#include <stdlib.h>
#include <string.h>

/*
    с-код, реализующий интерфейс для работы с векторами
*/

int matrixInit(Matrix *v, unsigned int columns, unsigned int rows, size_t elemSize, SumMatrixElements sumElements, MultMatrixElements multElements, PrintMatrixElement printElement)
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

void setMatrixElement(Matrix *v, unsigned int column, unsigned int row, const void *value)
{
    size_t index = (row * v->columns + column) * v->elemSize;
    memcpy(v->data + index, value, v->elemSize);
}

void *getMatrixElement(const Matrix *v, unsigned int column, unsigned int row)
{
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

    unsigned int numElements = v1->columns * v1->rows;
    for (unsigned int i = 0; i < numElements; i++)
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

    unsigned int resRows = v1->rows;
    unsigned int resColumns = v2->columns;
    unsigned int elemSize = v1->elemSize;

    // переписать отсюда
    // Выделяем память под результирующую матрицу

    if (ok = matrixInit(res, resColumns, resRows, elemSize, v1->sumElements, v1->multElements, v1->printElement) != 0)
    {
        return -2;
    }

    // Вычисление умножения матриц
    for (unsigned int i = 0; i < resRows; i++)
    {
        for (unsigned int j = 0; j < resColumns; j++)
        {
            for (unsigned int k = 0; k < v1->columns; k++)
            {
                void *resElem = (char *)res->data + (i * resColumns + j) * elemSize;
                void *v1Elem = (char *)v1->data + (i * v1->columns + k) * elemSize;
                void *v2Elem = (char *)v2->data + (k * v2->columns + j) * elemSize;
                v1->sumElements(resElem, resElem, resElem);
                v1->multElements(resElem, v1Elem, v2Elem);
            }
        }
    }

    // Устанавливаем параметры результирующей матрицы
    res->rows = resRows;
    res->columns = resColumns;
    res->elemSize = elemSize;
    res->sumElements = v1->sumElements;
    res->multElements = v1->multElements;
    res->printElement = v1->printElement;
    return 0;
}

void matrixPrintElements(const Matrix *v)
{
    // for (size_t i = 0; i < v->size; i++)
    // {
    //     v->printElement((const char *)v->data + i * v->elemSize);
    // }
}

// возможно нехватает аргументов в функции
void matrixAddToCollection(MatrixCollection *collection, const char *name, size_t elemSize, SumMatrixElements addFunc, PrintMatrixElement printFunc)
{
    // collection->matrixs = realloc(collection->matrixs, (collection->size + 1) * sizeof(NamedMatrix));
    // NamedMatrix *newVec = &collection->matrixs[collection->size];
    // strncpy(newVec->name, name, sizeof(newVec->name));
    // matrixInit(&newVec->matrix, elemSize, addFunc, printFunc);
    // collection->size++;
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

// void matrixMult(Matrix* res, const Matrix* v1, const Matrix* v2);

int matrixT(Matrix *res, const Matrix *v)
{
    return 0;
}