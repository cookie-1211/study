#include <string.h>
#include "matrix.h"
#include "complex.h"
#include "number.h"
#include "tests.h"
// 

void printMenu()
{
    printf("\n--- Menu ---\n");
    printf("0. Show matrices\n");
    printf("1. Create int matrix\n");
    printf("2. Create complex matrix\n");
    printf("3. Add element to int matrix\n");
    printf("4. Add element to complex matrix\n");
    printf("5. Sum matrices\n");
    printf("6. Mult matrices\n");
    printf("7. Matrix transpose\n");
    printf("8. Show matrix by name\n");
    printf("Enter 'STOP' for finish.\n");
    printf("Choose action: ");
}

//само меню можно дополнительно оптимизировать
int main()
{
    // test
    Matrix a;
    matrixInit(&a, 2, 2, sizeof(int), NULL, NULL, NULL);
    return -1;
    //

    // модульное тестирование перед переходом в меню
    if (testBasicIntMatricesLogic() == -1)
    {
        // нет смысла выполнять основной код, так как в тестах уже ошибка
        return -1;
    }

    //---------------------------------
    printf("All tests completed successfully!\n");

    MatrixCollection collection = {NULL, 0};

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
            printf("All matrices: ");
            for (size_t i = 0; i < collection.size; i++)
            {
                printf("%s ", collection.matrices[i].name);
            }
            break;
        }
        case 1:
        {
            // create int matrix
            char name[20];
            printf("Enter int matrix name: ");
            scanf("%19s", name);
            matrixAddToCollection(&collection, name, sizeof(int), numberSum, numberPrint);
            break;
        }
        case 2:
        {
            // create complex matrix
            char name[20];
            printf("Enter complex matrix name: ");
            scanf("%19s", name);
            matrixAddToCollection(&collection, name, sizeof(Complex), complexSum, complexPrint);
            break;
        }
        case 3:
            // add element to int matrix
            {
                char name[20];
                printf("Enter int matrix name: ");
                scanf("%19s", name);
                Matrix *vec = matrixFindInCollection(&collection, name);
                if (vec)
                {
                    int value;
                    printf("Enter integer to add to int matrix: ");
                    scanf("%d", &value);
                    matrixPushBack(vec, &value);
                }
                else
                {
                    printf("Matrix not found.\n");
                }
                break;
            }
        case 4:
            // add element to complex matrix
            {
                char name[20];
                printf("Enter complex matrix name: ");
                scanf("%19s", name);
                Matrix *vec = matrixFindInCollection(&collection, name);
                if (vec)
                {
                    int real;
                    int imag;
                    printf("Enter two int numbers like this '3 4' to \
                \ncreate complex '3r+4i' and add it to complex matrix: ");
                    scanf("%d %d", &real, &imag);
                    Complex complex = {real, imag};
                    matrixPushBack(vec, &complex);
                }
                else
                {
                    printf("Matrix not found.\n");
                }
                break;
            }
        case 5:
            // sum matrices
            {
                char nameFirstArg[20];
                char nameSecondArg[20];
                char nameResult[20];
                printf("Enter matrix names like this 'v1 v2 res': ");
                scanf("%19s %19s %19s", nameFirstArg, nameSecondArg, nameResult);
                Matrix *vec1 = matrixFindInCollection(&collection, nameFirstArg);
                Matrix *vec2 = matrixFindInCollection(&collection, nameSecondArg);
                Matrix *vecRes = matrixFindInCollection(&collection, nameResult);
                if (vec1 && vec2 && vecRes)
                {
                    matrixSum(vecRes, vec1, vec2);
                }
                else
                {
                    printf("Some matrices not found.\n");
                }
                break;
            }
        case 6:
            // mult matrices
            {
                char nameFirstArg[20];
                char nameSecondArg[20];
                char nameResult[20];
                printf("Enter matrix names like this 'v1 v2 res': ");
                scanf("%19s %19s %19s", nameFirstArg, nameSecondArg, nameResult);
                Matrix *vec1 = matrixFindInCollection(&collection, nameFirstArg);
                Matrix *vec2 = matrixFindInCollection(&collection, nameSecondArg);
                Matrix *vecRes = matrixFindInCollection(&collection, nameResult);
                if (vec1 && vec2 && vecRes)
                {
                    matrixSum(vecRes, vec1, vec2);
                }
                else
                {
                    printf("Some matrices not found.\n");
                }
                break;
            }
        case 7:
            // matricx transpose
            {
                // транспонирование матрицы
            //     char nameFirstArg[20];
            //     char nameSecondArg[20];
            //     char nameResult[20];
            //     printf("Enter matrix names like this 'v1 v2 res': ");
            //     scanf("%19s %19s %19s", nameFirstArg, nameSecondArg, nameResult);
            //     Matrix *vec1 = matrixFindInCollection(&collection, nameFirstArg);
            //     Matrix *vec2 = matrixFindInCollection(&collection, nameSecondArg);
            //     Matrix *vecRes = matrixFindInCollection(&collection, nameResult);
            //     if (vec1 && vec2 && vecRes)
            //     {
            //         matrixSum(vecRes, vec1, vec2);
            //     }
            //     else
            //     {
            //         printf("Some matrices not found.\n");
            //     }
            //     break;
            // }
        case 8:
        {
            // show martix by name
            char name[20];
            printf("Enter matrix name for show: ");
            scanf("%19s", name);
            Matrix *vec = matrixFindInCollection(&collection, name);
            if (vec)
            {
                matrixPrintElements(vec);
            }
            else
            {
                printf("Matrix not found.\n");
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
        matrixFree(&collection.matrices[i].matrix);
    }
    free(collection.matrices);

    return 0;
}
