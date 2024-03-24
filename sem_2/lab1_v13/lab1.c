#include <string.h>
#include "vector.h"
#include "matrix.h"
#include "complex.h"
#include "number.h"
#include "tests.h"


void printMenu()
{
    printf("\n--- Menu ---\n");
    printf("0. Show vectors\n");
    printf("1. Create int vector\n");
    printf("2. Create complex vector\n");
    printf("3. Add element to int vector\n");
    printf("4. Add element to complex vector\n");
    printf("5. Sum vectors\n");
    printf("6. Show vector by name\n");
    printf("Enter 'STOP' for finish.\n");
    printf("Choose action: ");
}

//само меню можно дополнительно оптимизировать
int main()
{
    Matrix a;
    matrixInit(&a, 2, 2, sizeof(int), NULL, NULL, NULL);
    return -1;

    // модульное тестирование перед переходом в меню
    if (testBasicIntVectorsLogic() == -1)
    {
        // нет смысла выполнять основной код, так как в тестах уже ошибка
        return -1;
    }

    //---------------------------------
    printf("All tests completed successfully!\n");

    VectorCollection collection = {NULL, 0};

    while (1)
    {
        char input[20];
        printMenu();
        scanf("%19s", input);

        if (strcmp(input, "STOP") == 0)
        {
            break;
        }

        int action = atoi(input);
        switch (action)
        {
        case 0:
        {
            char name[20];
            printf("All vectors: ");
            for (size_t i = 0; i < collection.size; i++)
            {
                printf("%s ", collection.vectors[i].name);
            }
            break;
        }
        case 1:
        {
            char name[20];
            printf("Enter int vector name: ");
            scanf("%19s", name);
            vectorAddToCollection(&collection, name, sizeof(int), numberSum, numberPrint);
            break;
        }
        case 2:
        {
            char name[20];
            printf("Enter complex vector name: ");
            scanf("%19s", name);
            vectorAddToCollection(&collection, name, sizeof(Vector), complexSum, complexPrint);
            break;
        }
        case 3:
            // add element to int vector
            {
                char name[20];
                printf("Enter int vector name: ");
                scanf("%19s", name);
                Vector *vec = vectorFindInCollection(&collection, name);
                if (vec)
                {
                    int value;
                    printf("Enter integer to add to int vector: ");
                    scanf("%d", &value);
                    vectorPushBack(vec, &value);
                }
                else
                {
                    printf("Vector not found.\n");
                }
                break;
            }
        case 4:
            // add element to complex vector
            {
                char name[20];
                printf("Enter complex vector name: ");
                scanf("%19s", name);
                Vector *vec = vectorFindInCollection(&collection, name);
                if (vec)
                {
                    int real;
                    int imag;
                    printf("Enter two int numbers like this '3 4' to \
                \ncreate complex '3r+4i' and add it to complex vector: ");
                    scanf("%d %d", &real, &imag);
                    Complex complex = {real, imag};
                    vectorPushBack(vec, &complex);
                }
                else
                {
                    printf("Vector not found.\n");
                }
                break;
            }
        case 5:
            // sum vectors
            {
                char nameFirstArg[20];
                char nameSecondArg[20];
                char nameResult[20];
                printf("Enter vector names like this 'v1 v2 res': ");
                scanf("%19s %19s %19s", nameFirstArg, nameSecondArg, nameResult);
                Vector *vec1 = vectorFindInCollection(&collection, nameFirstArg);
                Vector *vec2 = vectorFindInCollection(&collection, nameSecondArg);
                Vector *vecRes = vectorFindInCollection(&collection, nameResult);
                if (vec1 && vec2 && vecRes)
                {
                    vectorSum(vecRes, vec1, vec2);
                }
                else
                {
                    printf("Some vectors not found.\n");
                }
                break;
            }
        case 6:
        {
            char name[20];
            printf("Enter vector name for show: ");
            scanf("%19s", name);
            Vector *vec = vectorFindInCollection(&collection, name);
            if (vec)
            {
                vectorPrintElements(vec);
            }
            else
            {
                printf("Vector not found.\n");
            }
            break;
        }
        default:
            printf("Unknown command.\n");
            break;
        }
    }

    // Освобождение ресурсов
    for (size_t i = 0; i < collection.size; i++)
    {
        vectorFree(&collection.vectors[i].vector);
    }
    free(collection.vectors);

    return 0;
}
