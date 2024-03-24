#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

/*
    Хэдер, представляющий интерфейс для работы с векторами
*/
typedef void (*SumMatrixElements)(void* result, const void* a, const void* b);

typedef void (*MultMatrixElements)(void* result, const void* a, const void* b);

typedef void (*PrintMatrixElement)(const void* el);

typedef struct {
    void* data;       // Указатель на элементы
    size_t columns;      // Количество столбцов
    size_t rows;      // Количество строк
    size_t elemSize;  // Размер одного элемента
    SumMatrixElements sumElements; // Функция сложения
    MultMatrixElements multElements; // Функция умножения
    PrintMatrixElement printElement; // Функция вывода
} Matrix;

typedef struct {
    char name[20]; // Имя матрицы
    Matrix matrix; // Сама матрица
} NamedMatrix;

typedef struct {
    NamedMatrix* matrices; // Динамический массив именованных матриц
    size_t size;
} MatrixCollection;

//начинаем названия функций с имени хэдера, чтобы было понятно, какую библиотеку используем

void matrixInit(Matrix* v, size_t columns, size_t rows, size_t elemSize, SumMatrixElements sumElements, MultMatrixElements multElements, PrintMatrixElement printElement);

void matrixFree(Matrix* v);

void matrixSum(Matrix* res, const Matrix* v1, const Matrix* v2);

void matrixMult(Matrix* res, const Matrix* v1, const Matrix* v2);

void matrixT(Matrix* res, const Matrix* v);

void matrixPrintElements(const Matrix* v);

void matrixAddToCollection(MatrixCollection* collection, const char* name, size_t elemSize, SumMatrixElements addFunc, PrintMatrixElement printFunc);

Matrix* matrixFindInCollection(MatrixCollection* collection, const char* name);

//необходимо добавить еще функции согласно заданию! 

#endif
