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
    printf("3. Fill int matrix\n");
    printf("4. Fill complex matrix\n");
    printf("5. Sum matrices\n");
    printf("6. Mult matrices\n");
    printf("7. Matrix transpose\n");
    printf("8. Show matrix by name\n");
    printf("Enter 'q' for finish.\n");
    printf("Choose action: ");
}

// само меню можно дополнительно оптимизировать
int main()
{
    // модульное тестирование перед переходом в меню
    if (testMatrixLogic() == -1)
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

        if (strcmp(input, "q") == 0)
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
            int rows, columns;
            printf("Enter int matrix name: ");
            scanf("%19s", name);
            printf("Enter row number: ");
            scanf("%d", &rows);
            printf("Enter column number: ");
            scanf("%d", &columns);

            matrixAddToCollection(&collection, name, rows, columns, sizeof(int), numberSum, numberMult, numberPrint);
            break;
        }
        case 2:
        {
            // create complex matrix
            char name[20];
            int rows, columns;
            printf("Enter complex matrix name: ");
            scanf("%19s", name);
            printf("Enter row number: ");
            scanf("%d", &rows);
            printf("Enter column number: ");
            scanf("%d", &columns);
            matrixAddToCollection(&collection, name, rows, columns, sizeof(Complex), complexSum, complexMult, complexPrint);
            break;
        }
        case 3:
            // fill int matrix
            {
                char name[20];
                printf("Enter int matrix name: ");
                scanf("%19s", name);
                Matrix *m = matrixFindInCollection(&collection, name);
                if (m)
                {
                    printf("Matrix %ld rows x %ld columns\n", m->rows, m->columns);
                    int value;
                    for (size_t row = 0; row < m->rows; row++)
                    {
                        for (size_t col = 0; col < m->columns; col++)
                        {
                            printf("Enter integer to add into [%ld][%ld]: ", row, col);
                            scanf("%d", &value);
                            setMatrixElement(m, row, col, &value);
                        }
                    }
                }
                else
                {
                    printf("Matrix not found.\n");
                }
                break;
            }
        case 4:
            // fill complex matrix
            {
                char name[20];
                printf("Enter complex matrix name: ");
                scanf("%19s", name);
                Matrix *m = matrixFindInCollection(&collection, name);
                if (m)
                {
                    int real;
                    int imag;
                    printf("Matrix %ld rows x %ld columns\n", m->rows, m->columns);
                    printf("To add complex '3r+4i' you should enter two int numbers '3 4' and press Enter\n");
                    for (size_t row = 0; row < m->rows; row++)
                    {
                        for (size_t col = 0; col < m->columns; col++)
                        {
                            printf("Enter real and imag parrs of complex number to add into [%ld][%ld]: ", row, col);
                            scanf("%d %d", &real, &imag);
                            Complex complex = {real, imag};
                            setMatrixElement(m, row, col, &complex);
                        }
                    }
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
                printf("Enter matrix names like this 'm1 m2 res': ");
                scanf("%19s %19s %19s", nameFirstArg, nameSecondArg, nameResult);
                Matrix *m1 = matrixFindInCollection(&collection, nameFirstArg);
                Matrix *m2 = matrixFindInCollection(&collection, nameSecondArg);
                Matrix *mRes = matrixFindInCollection(&collection, nameResult);
                if (m1 && m2 && mRes)
                {
                    matrixSum(mRes, m1, m2);
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
                printf("Enter matrix names like this 'm1 m2 res': ");
                scanf("%19s %19s %19s", nameFirstArg, nameSecondArg, nameResult);
                Matrix *m1 = matrixFindInCollection(&collection, nameFirstArg);
                Matrix *m2 = matrixFindInCollection(&collection, nameSecondArg);
                Matrix *mRes = matrixFindInCollection(&collection, nameResult);
                if (m1 && m2 && mRes)
                {
                    matrixMult(mRes, m1, m2);
                }
                else
                {
                    printf("Some matrices not found.\n");
                }
                break;
            }
        case 7:
            // matrix transpose
            {
                // транспонирование матрицы
                char nameMatrix[20];
                printf("Enter matrix name to transpose: ");
                scanf("%19s", nameMatrix);
                Matrix *m = matrixFindInCollection(&collection, nameMatrix);
                if (m)
                {
                    matrixT(m);
                }
                else
                {
                    printf("Matrix to transpose not found.\n");
                }
                break;
            }
        case 8:
        {
            // show martix by name
            char name[20];
            printf("Enter matrix name for show: ");
            scanf("%19s", name);
            Matrix *m = matrixFindInCollection(&collection, name);
            if (m)
            {
                matrixPrintElements(m);
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
