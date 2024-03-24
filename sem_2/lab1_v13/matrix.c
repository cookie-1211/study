#include "matrix.h"
#include <stdlib.h>
#include <string.h>

/*
    с-код, реализующий интерфейс для работы с векторами
*/

void matrixInit(Matrix* v, size_t columns, size_t rows, size_t elemSize, SumMatrixElements sumElements, MultMatrixElements multElements, PrintMatrixElement printElement)
{
    v->data = malloc(columns * rows * elemSize);
    if (v->data == NULL) 
    {
        return;
        // ошибка выделения памяти
    }
     
    for (int i=1; i < columns * rows; i++) 
    {
        
    }
    v->columns = columns;
    v->rows = rows;
    v->elemSize = elemSize;
    v->sumElements = sumElements;
    v->multElements = multElements;
    v->printElement = printElement;
}


void matrixFree(Matrix *v)
{
    free(v->data);
    v->data = NULL;
}

void matrixSum(Matrix *res, const Matrix *v1, const Matrix *v2)
{
    // if (v1->size == v2->size && v1->elemSize == v2->elemSize && v1->sumElements != NULL)
    // {
    //     matrixInit(res, v1->elemSize, v1->sumElements, v1->printElement);
    //     // Временное хранилище для результата сложения двух элементов
    //     void *tempResult = malloc(v1->elemSize);
    //     if (tempResult == NULL)
    //     {
    //         // Можно вставить обработку ошибки выделения памяти
    //         return;
    //     }

    //     for (size_t i = 0; i < v1->size; i++)
    //     {
    //         // Получаем указатели на текущие элементы обоих векторов
    //         const void *elem1 = (const char *)v1->data + i * v1->elemSize;
    //         const void *elem2 = (const char *)v2->data + i * v2->elemSize;

    //         // Складываем элементы callback функцией
    //         v1->sumElements(tempResult, elem1, elem2);

    //         // Добавляем результат в результирующий вектор
    //         matrixPushBack(res, tempResult);
    //     }
    //     free(tempResult); // Освобождаем временное хранилище
    // }
    // else
    // {
    //     // Ошибка: векторы разной длины, разного размера элементов или функция сложения не определена
    // }
}

void matrixPrintElements(const Matrix *v)
{
    // for (size_t i = 0; i < v->size; i++)
    // {
    //     v->printElement((const char *)v->data + i * v->elemSize);
    // }
}

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

void matrixMult(Matrix* res, const Matrix* v1, const Matrix* v2);

void matrixT(Matrix* res, const Matrix* v);