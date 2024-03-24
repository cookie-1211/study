#include "tests.h"


int testBasicIntVectorsLogic()
{
        int response = 0;
        VectorCollection collection = {NULL, 0};

        vectorAddToCollection(&collection, "abc", sizeof(int), numberSum, numberPrint);

        if (collection.size != 1)
        {
                printf("vectorAddToCollection does not work!");
                response = -1;
        }

        Vector *vec = vectorFindInCollection(&collection, "abc");

        if (vec)
        {
                // далее по аналогии тесты для вектора
        }
        else
        {
                printf("vectorFindInCollection does not work!");
                response = -1;
        }

        // Освобождение ресурсов
        for (size_t i = 0; i < collection.size; i++)
        {
                vectorFree(&collection.vectors[i].vector);
        }
        free(collection.vectors);
        return response;
}
