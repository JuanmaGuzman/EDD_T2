#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 8  

int board[SIZE][SIZE];  
int rowSum[SIZE];
int colSum[SIZE];

typedef struct {
    int key;
    int x;
    int y;
} Entry;

Entry dictionary[SIZE * SIZE];
int entryCount = 0;

void calculateSums() {
    for (int i = 0; i < SIZE; i++) {
        rowSum[i] = 0;
        colSum[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            rowSum[i] += board[i][j];
            colSum[i] += board[j][i];
        }
    }
}

void updateSums(int x, int y, int num) {
  rowSum[x] += num ;
  colSum[y] += num;
}


bool isValidMove(int x, int y, int num) {
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == 0 &&
            (rowSum[x] + num <= 260) && (colSum[y] + num <= 260));
}


bool isSolutionValid(int target) {
    int sumRow, sumCol;
    
    for (int i = 0; i < SIZE; i++) {
        sumRow = 0;
        sumCol = 0;
        for (int j = 0; j < SIZE; j++) {
            sumRow += board[i][j];
            sumCol += board[j][i];
        }
        if (sumRow != target || sumCol != target) {
            return false;
        }
    }
    
    return true;
}


bool solveChessBoard(int x, int y, int num, int target) {
    // Verificar si se ha alcanzado el número máximo posible
    if (num > SIZE * SIZE) {
        // Verificar si la solución es válida
        if (isSolutionValid(target)) {
            return true;  // Se encontró una solución válida
        } else {
            return false;  // La solución no es válida
        }
    }

    int inputX = -1, inputY = -1;
    // Recorrer las claves del "diccionario"
    for (int i = 0; i < entryCount; i++) {
        Entry entry = dictionary[i];
        if (entry.key == num) {
            // printf("Número %d encontrado en coordenadas (%d, %d)\n", num, entry.x, entry.y);
            inputX = entry.x;
            inputY = entry.y;
            break;
        }
    }

    if (inputX != -1 && inputY != -1) {
        // printf("#%d no está\n", num);
        return solveChessBoard(inputX, inputY, num + 1, target);
    }

    // Definir las posiciones válidas dentro del rango específico
    // static const int validPositions[][2] = {{-2, 1}, {1, 2}, {2, 1}, {1, -2}};
    static const int validPositions[][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};


    // Recorrer las posiciones válidas y realizar las operaciones necesarias
    for (int k = 0; k < 8; k++) {  // Recorremos las 4 posiciones válidas
        int newX = x + validPositions[k][0];
        int newY = y + validPositions[k][1];

        // Verificar si la posición es válida
        if (isValidMove(newX, newY, num)) {
            board[newX][newY] = num;  // Asignar la etiqueta al tablero
            updateSums(newX, newY, num);  // Actualizar suma total fila y columnas

            // Llamar recursivamente a la función para buscar la etiqueta que sigue
            if (solveChessBoard(newX, newY, num + 1, target)) {
                return true;  // Se encontró una solución válida
            }

            // Si no se encontró una solución válida, deshacer el movimiento y la suma
            board[newX][newY] = 0;
            updateSums(newX, newY, num * -1);

            // // Reflejar simétricamente los resultados en las otras posiciones válidas
            // int reflectedX = SIZE - 1 - newX;
            // int reflectedY = SIZE - 1 - newY;

            // board[reflectedX][reflectedY] = num;
            // updateSums(reflectedX, reflectedY, num);

            // if (solveChessBoard(reflectedX, reflectedY, num + 1, target)) {
            //     return true;
            // }

            // board[reflectedX][reflectedY] = 0;
            // updateSums(reflectedX, reflectedY, num * -1);
        }
    }

    return false;  // No se encontró una solución válida
}


int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Modo de uso: %s input output\nDonde:\n", argv[0]);
        printf("\t\"input\" es la ruta al archivo de input\n");
        printf("\t\"output\" es la ruta al archivo de output\n");
        return 1;
    }

    // Abrir el archivo de input
    FILE* input_stream = fopen(argv[1], "r");

    // Abrir el archivo de output
    FILE* output_stream = fopen(argv[2], "w");

    // Verificar si alguno de los dos archivos no se pudo abrir
    if (!input_stream) {
        printf("El archivo %s no existe o no se puede leer\n", argv[1]);
        return 2;
    }
    if (!output_stream) {
        printf("El archivo %s no se pudo crear o no se puede escribir\n", argv[2]);
        printf("Recuerda que \"fopen\" no puede crear carpetas\n");
        fclose(input_stream);
        return 3;
    }

    // Leer el tablero incompleto desde el archivo de input
    // Evaluar si la etiqueta se encuentra en el input inicial
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(input_stream, "%d", &board[i][j]);
            if (board[i][j] != 0) {
                // agregar a lista con valores iniciales
                Entry entry = {board[i][j], i, j};
                dictionary[entryCount] = entry;
                entryCount++;
            }
        }
    }

    // Calculate the sums of rows and columns
    calculateSums();

    // Calcular el valor objetivo para las filas y columnas
    int target = 260;

    // Encontrar la posición inicial del número 1 en el tablero
    int startX, startY;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 1) {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    // Resolver el tablero utilizando el algoritmo de retroceso
    solveChessBoard(startX, startY, 2, target);

    // Escribir el tablero completo en el archivo de output
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fprintf(output_stream, "%d ", board[i][j]);
        }
        fprintf(output_stream, "\n");
    }

    // Cerrar el archivo de input
    fclose(input_stream);

    // Cerrar el archivo de output
    fclose(output_stream);

    return 0;
}