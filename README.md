# Tarea 2 2023-1

**Tarea del Ramo de Estructuras de Datos y Algoritmos: Simulación de Elecciones y Optimización de Algoritmos**

Este proyecto abarca la simulación de elecciones bajo diferentes sistemas de votación y la optimización de algoritmos para mejorar el rendimiento. Desde el procesamiento de votos y cálculo de resultados hasta la implementación de técnicas de ordenamiento y estructuras de datos avanzadas, el proyecto explora conceptos clave de programación y algoritmos.

**Objetivos:**
- Investigar y aplicar algoritmos y estructuras de datos para resolver problemas complejos.
- Utilizar técnicas de dividir y conquistar, y estrategias recursivas en la implementación de soluciones.
- Familiarizarse con la importancia de la complejidad computacional en la optimización de algoritmos.

**Parte 1: Matepossible**
Esta sección se centra en el procesamiento de votos y simulación de sistemas de votación. Los candidatos y votantes son analizados en un espectro ideológico. El sistema de votación STV es simulado con transferencias de votos según distancias ideológicas.

**Parte 2: DCCodersSort**
El objetivo es ordenar competidores en función de sus estadísticas de carreras. Se implementa el algoritmo QuickSort y se evalúa el rendimiento. Se busca optimizar la ordenación de datos en base a múltiples criterios.

**Parte 3: Mate, eso nunca paso.**
Se aborda un problema de simulación de colisiones en un escenario tridimensional. Se propone la optimización del algoritmo mediante la implementación de un KD-Tree (árbol de búsqueda en estructuras de datos).

**Código Base y Ejecución:**
Los programas se compilan con el comando 'make' y se ejecutan con parámetros de entrada y salida, procesando datos y generando resultados según el contexto de cada parte del proyecto.

Este proyecto provee una experiencia de aprendizaje integral en el manejo de algoritmos, estructuras de datos y optimización, enfocados en la resolución de problemas reales en el ámbito de la programación y la simulación.

## Compilar

```
make
```

## Recompilar

```
make clean && make
```

## Parte 1

```
./mateconhuesillo input.txt output.txt
```

## Comparar respuesta

Para esto les subimos un script de Python que les permite comparar su respuesta con la respuesta correcta. Para ejecutarlo, deben tener instalado Python 3.6 o superior:
```
python tests/hashing/check_output.py correc_output.txt student_output.txt
```

## Parte 2

```
./matechess input.txt output.txt
```

## Comparar respuesta

```
diff -b correct_output.txt student_output.txt
```


## Para revisar servidor

En algunos días se subirán testcases al servidor para que puedas probar tu tarea.

- Para revisar los _test publicos_ en el servidor del curso se tiene que acceder al siguiente [link](http://edd.ing.puc.cl/test?repo=T2-2023-1-USERNAME)

- Para revisar los _test de evaluacion_ en el servidor del curso se tiene que acceder al siguiente [link](http://edd.ing.puc.cl/grade?repo=T2-2023-1-USERNAME)

**Tiene que remplazar *USERNAME* por su usuario de github**
