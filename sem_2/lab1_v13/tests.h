#ifndef TESTS_H
#define TESTS_H

#include "complex.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>

int testMatrixLogic(); // return 0 - OK, -1 - ERROR
// тест заполенения матриц
int testMatrixFill();  // return 0 - OK, -1 - ERROR
// тест сложения матриц
int testMatrixSum();  // return 0 - OK, -1 - ERROR
// тест умножения матриц
int testMatrixMult();  // return 0 - OK, -1 - ERROR
// тест транспонирования матриц
int testMatrixT();  // return 0 - OK, -1 - ERROR

// необходимо добавить остальные тесты для покрытия всего функционала и запустить их в мейне перед основной логикой

#endif