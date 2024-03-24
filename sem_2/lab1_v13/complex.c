#include "complex.h"

/*
    с-код, реализующий интерфейс для работы с комплексными числами
*/

void complexSum(void* result, const void* a, const void* b) {
    ((Complex*)result)->real = ((const Complex*)a)->real + ((const Complex*)b)->real;
    ((Complex*)result)->imag = ((const Complex*)a)->imag + ((const Complex*)b)->imag;
}

void complexMult(void* result, const void* a, const void* b) {
    ((Complex*)result)->real = (((const Complex*)a)->real * ((const Complex*)b)->real) - (((const Complex*)a)->imag * ((const Complex*)b)->imag);
    ((Complex*)result)->imag = (((const Complex*)a)->real * ((const Complex*)b)->imag) + (((const Complex*)a)->imag * ((const Complex*)b)->real);
}

void complexPrint(const void* elem) {
    const Complex* complexElem = (const Complex*)elem;
    printf("%d + %di ", complexElem->real, complexElem->imag);
}