En este tema, veremos un algoritmo que descompone problemas grandes en subproblemas de tamaño manejable, resolviendo cada uno de ellos para luego combinarlos en pos de construir la solución final y completa. Este enfoque es aplicado comúnmente en varios algoritmos de **multiplicación**, **ordenación** y **búsqueda**.

#### Multiplicación de enteros grandes

Nos permite multiplica números de múltiples cifras reduciendo la cantidad de multiplicaciones y sumas necesarias mediante descomposición y combinación de resultados parciales.

#### Búsqueda binaria

Este algoritmo reduce el espacio de búsqueda en un vector ordenado a la mitad en cada paso, logrando una complejidad de O(log n), véase [[Complejidad Algorítmica]] para más info.

#### Ordenación

- **Mergesort** --> Dividimos el vector original en sub-vectores, los ordenamos recursivamente y luego los fusionamos en un vector ordenado con complejidad O(n log n) 
- **Quicksort** --> Seleccionamos un pivote y organizamos los elementos alrededor de este, dividiendo el problema en sub-vectores para resolverlos recursivamente, logrando también una complejidad de O(n log n) en promedio. 

#### Estructura

Tenemos tres etapas:
1. Dividir el problema
2. Conquistar resolviendo los subproblemas
3. Combinar las soluciones parciales

La eficiencia de estos algoritmos depende de factores como el número de subproblemas generados y el tamaño de la reducción en cada paso.

Veamos una posible interpretación de nuestro código:

```python
# Función general de Divide y Vencerás
def divide_y_venceras(problema):
	# Paso base: si el problema es lo suficientemente simple, resuélvelo directamente
    if es_simple(problema):
        return solucion_simple(problema)
    
    # Paso de división: divide el problema en subproblemas
    subproblemas = dividir(problema)
    
    # Paso de conquista: resuelve cada subproblema de forma recursiva
    soluciones_subproblemas = [divide_y_venceras(sub) for sub in subproblemas]
    
    # Paso de combinación: combina las soluciones de los subproblemas
    solucion = combinar(soluciones_subproblemas)
    
    return solucion
```

##### Ejemplo de uso

Por ejemplo para un algoritmo como **Mergesort**:
- `es_simple` verificaría si la lista tiene uno o cero elementos
- `dividir` separaría la lista en dos mitades
- `combinar`fusionaría las listas ordenadas de cada mitad.