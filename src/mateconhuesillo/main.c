#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Función de comparación para qsort
int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Estructura para representar un nodo del árbol
typedef struct Nodo {
    int id;
    int valor;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

// Estructura para representar un nodo de la lista enlazada
typedef struct NodoLista {
    Nodo* subarbol;
    struct NodoLista* siguiente;
} NodoLista;

// Función para crear un nuevo nodo del árbol
Nodo* crearNodo(int valor, int id) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->id = id;
    nodo->valor = valor;
    nodo->izquierdo = NULL;
    nodo->derecho = NULL;
    return nodo;
}

// Función para crear un nuevo nodo de la lista enlazada
NodoLista* crearNodoLista(Nodo* subarbol) {
    NodoLista* nodoLista = (NodoLista*)malloc(sizeof(NodoLista));
    nodoLista->subarbol = subarbol;
    nodoLista->siguiente = NULL;
    return nodoLista;
}

// Función auxiliar para contar el número total de nodos en el subárbol
int contarNodos(Nodo* subarbol) {
    if (subarbol == NULL)
        return 0;

    return 1 + contarNodos(subarbol->izquierdo) + contarNodos(subarbol->derecho);
}

// Función auxiliar para contar el número de nodos con un valor específico en el subárbol
int contarNodosColor(Nodo* subarbol, int color) {
    if (subarbol == NULL)
        return 0;

    int contador = (subarbol->valor == color) ? 1 : 0;
    contador += contarNodosColor(subarbol->izquierdo, color) + contarNodosColor(subarbol->derecho, color);
    return contador;
}

// Función de hash para un subárbol
int funcionHash(Nodo* subarbol) {
    if (subarbol == NULL)
        return 0;

    int totalNodos = contarNodos(subarbol);
    int nodosNegros = contarNodosColor(subarbol, 0);
    int nodosBlancos = totalNodos - nodosNegros;
    
    // Puedes combinar estos valores de alguna manera para obtener el valor hash
    // Por ejemplo, puedes multiplicarlos por diferentes factores y sumarlos
    int valorHash = totalNodos * 2 + nodosNegros * 3 + nodosBlancos * 5;
    
    return valorHash;
}

// Función de ajuste para obtener el índice en la tabla hash
int funcionAjuste(int valorHash, int tamTablaHash) {
    return valorHash % tamTablaHash;
}

// Función que compara dos arboles
bool sonArbolesIguales(Nodo* arbol1, Nodo* arbol2) {
    // Si ambos árboles son nulos, son considerados iguales
    if (arbol1 == NULL && arbol2 == NULL) {
        return true;
    }
    // Si solo uno de los árboles es nulo, son considerados diferentes
    else if (arbol1 == NULL || arbol2 == NULL) {
        return false;
    }
    // Si los valores de los nodos son diferentes, los árboles son diferentes
    else if (arbol1->valor != arbol2->valor) {
        return false;
    }
    // Compara recursivamente los subárboles izquierdo y derecho
    else {
        bool izquierdoIgual = sonArbolesIguales(arbol1->izquierdo, arbol2->izquierdo);
        bool derechoIgual = sonArbolesIguales(arbol1->derecho, arbol2->derecho);
        // Los árboles son iguales si sus subárboles izquierdo y derecho también son iguales
        return izquierdoIgual && derechoIgual;
    }
}

// Función que dada una consulta K (arbol) obtiene su número de hash
int* contarArbolesIguales(Nodo* T, NodoLista** tablaHash, int tamTablaHash, int* numValores) {
    int valorHash = funcionHash(T);
    int indiceHash = funcionAjuste(valorHash, tamTablaHash);

        // printf("Arbol T: ");
        // imprimirArbol(T);
        // printf("\n");

    NodoLista* nodoLista = tablaHash[indiceHash];
    int capacidad = 10;
    int* valores = malloc(capacidad * sizeof(int));
    int contador = 0;



    while (nodoLista != NULL) {
        Nodo* subarbol = nodoLista->subarbol;

        // printf("Opción subarbol: ");
        // imprimirArbol(subarbol);
        // printf("\n");

        if (sonArbolesIguales(T, subarbol)) {
            if (contador == capacidad) {
                // Aumenta la capacidad del arreglo de valores
                capacidad *= 2;
                valores = realloc(valores, capacidad * sizeof(int));
            }
            valores[contador++] = subarbol->id;
        }
        nodoLista = nodoLista->siguiente;
    }

    *numValores = contador;
    return valores;
}

// Función para leer el árbol a partir de la secuencia de valores
Nodo* leerArbol(int valores[], int inicio, int fin, int id) {
    if (inicio > fin)
        return NULL;
    
    // Crear el nodo actual
    Nodo* nodo = crearNodo(valores[inicio], id);
    
    // Calcular los índices de los hijos
    int indiceHijoIzq = 2 * inicio + 1;
    int indiceHijoDer = 2 * inicio + 2;
    
    // Leer los subárboles izquierdo y derecho de forma recursiva
    nodo->izquierdo = leerArbol(valores, indiceHijoIzq, fin, id * 2);
    nodo->derecho = leerArbol(valores, indiceHijoDer, fin, id * 2 + 1);
    
    return nodo;
}

// Función para imprimir los valores de un árbol en un recorrido en anchura
void imprimirArbol(Nodo* raiz) {
    if (raiz == NULL)
        return;
    
    // Cola para realizar el recorrido en anchura
    Nodo* cola[1000];
    int frente = 0;
    int final = 0;
    cola[final++] = raiz;
    
    while (frente < final) {
        Nodo* nodoActual = cola[frente++];
        //printf("%d ", nodoActual->valor);
        
        // Agregar los hijos a la cola
        if (nodoActual->izquierdo != NULL)
            cola[final++] = nodoActual->izquierdo;
        if (nodoActual->derecho != NULL)
            cola[final++] = nodoActual->derecho;
    }
}

// Función para liberar la memoria utilizada por el árbol
void liberarArbol(Nodo* raiz) {
    if (raiz == NULL)
        return;
    
    liberarArbol(raiz->izquierdo);
    liberarArbol(raiz->derecho);
    free(raiz);
}


// Nodo* procesarArbol(int numNodos, int *colores, int numConsultas) {
//     // Lógica para procesar el árbol y realizar las consultas
//     // Aquí puedes implementar la lógica específica que necesites
//     // para tu problema concreto
//     printf("Procesando árbol con %d nodos: %d", numNodos, colores[0]);
//     Nodo* arbolBusqueda = crearNodo(colores[0], -1);
//     for (int i = 1; i < numNodos; i++) {
//         int value = colores[i];
//         if (i % 2 != 0) {
//             arbolBusqueda->izquierdo = crearNodo(value, -1);
//             printf(" %d", colores[i]);
//         } else {
//             arbolBusqueda->derecho = crearNodo(value, -1);
//             printf(" %d", colores[i]);
//         }
//     }
//     printf("\n");
//     return arbolBusqueda;
// }

Nodo* procesarArbol(int numNodos, int *colores, int numConsultas) {
    //printf("Procesando árbol con %d nodos: %d", numNodos, colores[0]);
    Nodo* arbolBusqueda = crearNodo(colores[0], -1);
    int indiceColores = 1; // Índice para recorrer el arreglo de colores

    // Utilizar un contador para asegurar que se construya un árbol completo
    int contadorNodos = 1; // Inicializar en 1 ya que el primer nodo ya ha sido creado

    // Utilizar una cola para construir el árbol por niveles
    Nodo* cola[numNodos];
    int frente = 0;
    int final = 0;
    cola[final++] = arbolBusqueda;

    // Construir el árbol por niveles hasta que se alcance el número deseado de nodos
    while (contadorNodos < numNodos && frente < final) {
        Nodo* nodoActual = cola[frente++];

        // Agregar el hijo izquierdo si aún se necesitan más nodos
        if (contadorNodos < numNodos) {
            nodoActual->izquierdo = crearNodo(colores[indiceColores], -1);
            //printf(" %d", colores[indiceColores]);
            cola[final++] = nodoActual->izquierdo;
            indiceColores++;
            contadorNodos++;
        }

        // Agregar el hijo derecho si aún se necesitan más nodos
        if (contadorNodos < numNodos) {
            nodoActual->derecho = crearNodo(colores[indiceColores], -1);
            //printf(" %d", colores[indiceColores]);
            cola[final++] = nodoActual->derecho;
            indiceColores++;
            contadorNodos++;
        }
    }

    //printf("\n");
    return arbolBusqueda;
}



int contarElementos(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    } else {
        int contador = 1;  // Inicializar el contador con el nodo actual

        contador += contarElementos(nodo->izquierdo); // Contar elementos del subárbol izquierdo
        contador += contarElementos(nodo->derecho);   // Contar elementos del subárbol derecho

        return contador;
    }
}


int main(int argc, char** argv) {
  if (argc != 3) {
    printf("Modo de uso: %s input output\nDonde:\n", argv[0]);
    printf("\t\"input\" es la ruta al archivo de input\n");
    printf("\t\"output\" es la ruta al archivo de output\n");
    return 1;
  }

  // Abrimos el archivo de input
  FILE* input_stream = fopen(argv[1], "r");

  // Abrimos el archivo de output
  FILE* output_stream = fopen(argv[2], "w");

  // Si alguno de los dos archivos no se pudo abrir
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

    // [Aqui va tu tarea]
    int numNodos;
    int numConsultas;
    char linea[10000];
    int contador = 0;

    // Leer la línea del archivo
    fgets(linea, sizeof(linea), input_stream);

    // Leer el primer número
    sscanf(linea, "%d", &numNodos);

    int valores[numNodos];

    // Leer los demás números y almacenarlos en la lista
    char *token = strtok(linea, " ");
    while (token != NULL) {
        token = strtok(NULL, " ");
        if (token != NULL) {
            valores[contador++] = atoi(token);
        }
    }

    // Imprimir el primer número y la lista de números
    //printf("numNodos: %d\n", numNodos);
    //printf("Lista de números: ");
    // for (int i = 0; i < contador; i++) {
    //     printf("%d ", valores[i]);
    // }

    // printf("\n");
    
    Nodo* arbolPrincipal = leerArbol(valores, 0, numNodos - 1, 1);
    // printf("Árbol principal: ");
    // imprimirArbol(arbolPrincipal);
    // printf("\n");
    
    // Obtener los subárboles completos
    Nodo* subArboles[1000];
    int numSubArboles = 0;
    
    // Cola para realizar el recorrido en anchura
    Nodo* cola[1000];
    int frente = 0;
    int final = 0;
    cola[final++] = arbolPrincipal;
    
    while (frente < final) {
        Nodo* nodoActual = cola[frente++];
        
        // Verificar si el subárbol es completo
        bool esCompleto = true;
        
        if (nodoActual->izquierdo != NULL) {
            cola[final++] = nodoActual->izquierdo;
            if (nodoActual->derecho != NULL)
                cola[final++] = nodoActual->derecho;
            else
                esCompleto = false;
        } else if (nodoActual->derecho != NULL) {
            esCompleto = false;
        }
        
        // Verificar si el subárbol tiene más de un nodo
        if (esCompleto && (nodoActual->izquierdo != NULL || nodoActual->derecho != NULL))
            subArboles[numSubArboles++] = nodoActual;
    }

    //printf("------\n");
    for (int i = 0; i < numSubArboles; i++) {
        int numElementos = contarElementos(subArboles[i]); // Función para contar los elementos del subárbol
        
        if (numElementos > 3) {
            // Recorrer el subárbol y guardar los primeros tres valores en un nuevo subárbol auxiliar
            Nodo* nodoActual = subArboles[i];
            Nodo* subarbolAuxiliar = NULL;
            int fixID = -10;
            int contador = 0;

            Nodo* colaAuxiliar[1000];
            int frenteAuxiliar = 0;
            int finalAuxiliar = 0;
            colaAuxiliar[finalAuxiliar++] = nodoActual;

            Nodo* nodoRaiz = NULL;
            Nodo* nodoIzquierdo = NULL;
            Nodo* nodoDerecho = NULL;

            while (nodoActual != NULL && contador < 3 && frenteAuxiliar < finalAuxiliar) {
                nodoActual = colaAuxiliar[frenteAuxiliar++];

                if (contador == 0) {
                    nodoRaiz = nodoActual;
                } else if (contador == 1) {
                    nodoIzquierdo = nodoActual;
                } else if (contador == 2) {
                    nodoDerecho = nodoActual;
                }

                contador++;

                if (contador == 1) {
                    fixID = nodoActual->id;
                }

                // Agregar los hijos a la cola auxiliar
                if (nodoActual->izquierdo != NULL)
                    colaAuxiliar[finalAuxiliar++] = nodoActual->izquierdo;
                if (nodoActual->derecho != NULL)
                    colaAuxiliar[finalAuxiliar++] = nodoActual->derecho;
            }

            // Crear los nuevos nodos del subárbol auxiliar en el orden deseado
            Nodo* nuevoNodoRaiz = crearNodo(nodoRaiz->valor, fixID);
            Nodo* nuevoNodoIzquierdo = crearNodo(nodoIzquierdo->valor, fixID);
            Nodo* nuevoNodoDerecho = crearNodo(nodoDerecho->valor, fixID);

            //uxiliar\n");
            nuevoNodoRaiz->izquierdo = nuevoNodoIzquierdo;
            nuevoNodoRaiz->derecho = nuevoNodoDerecho;

            subarbolAuxiliar = nuevoNodoRaiz;

            subArboles[numSubArboles++] = subarbolAuxiliar;
            
        }
    }
    
    // Imprimir los subárboles completos
    // printf("Subárboles completos:\n");
    // for (int i = 0; i < numSubArboles; i++) {
    //     printf("Subárbol %d: ", i + 1);
    //     imprimirArbol(subArboles[i]);
    //     printf("\n");
    // }

    // Crear y llenar la tabla hash con los subárboles correspondientes
    // int tamTablaHash = (int)sqrt(numNodos);

    
    // NodoLista* tablaHash[numNodos] = {NULL}; // Tamaño de la tabla hash: 1000
    // int tamTablaHash = sizeof(tablaHash) / sizeof(tablaHash[0]);

    NodoLista** tablaHash = (NodoLista**)malloc(numNodos * sizeof(NodoLista*));
    for (int i = 0; i < numNodos; i++) {
        tablaHash[i] = NULL;
    }

    int tamTablaHash = numNodos;



    for (int i = 0; i < numSubArboles; i++) {
        Nodo* subarbol = subArboles[i];
        int valorHash = funcionHash(subarbol);
        int indiceHash = funcionAjuste(valorHash, tamTablaHash);
        
        // Agregar el subárbol a la tabla hash en la posición correspondiente
        if (tablaHash[indiceHash] == NULL) {
            tablaHash[indiceHash] = crearNodoLista(subarbol);
        } else {
            // Si la posición ya está ocupada, agregar el subárbol al final de la lista
            NodoLista* nodoLista = tablaHash[indiceHash];
            while (nodoLista->siguiente != NULL) {
                nodoLista = nodoLista->siguiente;
            }
            nodoLista->siguiente = crearNodoLista(subarbol);
        }
    }
    

    // Leer el número de consultas
    fgets(linea, sizeof(linea), input_stream);
    sscanf(linea, "%d", &numConsultas);

    // Procesar cada consulta
    // printf("-----\n");
    // printf("numConsultas: %d\n", numConsultas);
    for (int i = 0; i < numConsultas; i++) {
        // Leer el árbol γi
        fgets(linea, sizeof(linea), input_stream);
        int numNodosConsulta;
        int coloresConsulta[numNodos];
        int contadorConsulta = 0;

        sscanf(linea, "%d", &numNodosConsulta);

        // Leer los colores de los nodos en la consulta
        char *tokenConsulta = strtok(linea, " ");
        while (tokenConsulta != NULL) {
            tokenConsulta = strtok(NULL, " ");
            if (tokenConsulta != NULL) {
                coloresConsulta[contadorConsulta++] = atoi(tokenConsulta);
            }
        }

        // Procesar la consulta
        Nodo* arbolBusqueda = procesarArbol(numNodosConsulta, coloresConsulta, numConsultas);


        // printf("Arbol arbolBusqueda: ");
        // imprimirArbol(arbolBusqueda);
        // printf("\n");

        // Contar la cantidad de árboles iguales al árbol de búsqueda
        int* valoresIguales;
        int numValoresIguales = 0;

        valoresIguales = contarArbolesIguales(arbolBusqueda, tablaHash, tamTablaHash, &numValoresIguales);

        if (numValoresIguales == 0) {
            fprintf(output_stream, "-1");
        } else {
            // Ordenar los valores de menor a mayor
            qsort(valoresIguales, numValoresIguales, sizeof(int), comparar);

            // Imprimir los valores ordenados
            for (int i = 0; i < numValoresIguales; i++) {
                fprintf(output_stream, "%d ", valoresIguales[i]);
            }
        }

        fprintf(output_stream, "\n");

        // Liberar la memoria asignada al arreglo de valores cuando ya no lo necesites
        free(valoresIguales);
    }

    free(tablaHash);  // Liberar la memoria asignada cuando ya no se necesita

    // Liberar la memoria utilizada por el árbol
    liberarArbol(arbolPrincipal);

    // Cerrar archivo de input
    fclose(input_stream);

    // Cerrar archivo de output
    fclose(output_stream);
    
    return 0;
}
