## Conjuntos y Mapas
Los **conjuntos** (`unordered_set`) y **mapas** (`unordered_map`) son estructuras de datos que almacenan elementos de forma **no ordenada**, pero con acceso rápido.
### Características principales
- **No hay un orden específico**
- **Búsqueda, inserción y eliminación en tiempo promedio constante O(1)** gracias a las **tablas hash**
- **Claves únicas**
	- En `unordered_set` cada elemento es único
	- En `unordered_map` cada clave tiene un único valor asociado
#### **Ejemplo de `unordered_map`:**
```cpp
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<std::string, int> edad;
    edad["Juan"] = 25;
    edad["Ana"] = 30;

    // Acceso rápido
    std::cout << edad["Juan"]; // Salida: 25
    return 0;
}
```
Aquí `"Juan"` y `"Ana"` son claves únicas que apuntan a valores (`25` y `30`).
#### **Ejemplo de `unordered_set`**

```cpp
#include <unordered_set>
int main() {
	std::unordered_set<int> numeros = {1, 2, 3, 2, 4};
	// Sólo almacena {1, 2, 3, 4} sin duplicar
	return 0;
}
```
## Tablas Hash
### Introducción
Son la estructura subyacente en `unordered_set` y `unordered_map`. Permiten **acceso rápido** a los datos mediante una **función hash** que convierte una clave en un índice dentro de un arreglo. 
### Funciones hash 
#### Códigos Hash
- Una **función hash** toma una clave (ej: un string) y devuelve un **número entero** (código hash)
- **Propiedades de una buena función hash**:
	- **Consistencia** -> Misma clave -> Mismo hash
	- **Distribución uniforme**: Las claves diferentes deberían generar hashes diferentes.

**Ejemplo**

```cpp
std::hash<std::string> hasher;
size_t hash_value = hasher("Hola"); // devuelve un número único para "Hola"
```
### Función de compresión
- El código hash puede ser muy grande, así que se aplica una compresión para ajustarlo al tamaño de la tabla.
- Método común: `índice = hash % tamaño_tabla`
### Colisiones
Ocurren cuando **dos claves diferentes** producen el mismo índice. Hay dos formas de manejarlas:
1. **Encadenamiento (Chaining)**
	1. Cada posición de la tabla almacena una **lista enlazada** de elementos con el mismo hash
	2. *Ejemplo*: Si "Juan" y "Ana" tienen el mismo hash, se guardan en una lista en la misma posición. 
2. **Direccionamiento abierto (Open Addressing)**
	1. Si hay colisión, busca la siguiente posición disponible (ej: lineal, cuadrática)
## Diccionarios
Permiten **claves duplicadas**, a diferencia de `unordered_set` y `unordered_map`
### `unordered_multiset`
- Almacena elementos **duplicados**, pero sin orden.
- Útil cuando solo importa la pertenencia y no la unicidad.

**Ejemplo**
```cpp
#include <unordered_set>

int main() {
	std::unordered_multiset<int> nums = {1, 2, 2, 3};
	// Almacena {1, 2, 2, 3}
	return 0; 
}
```
### `unordered_multimap`
- Permite **múltiples valores para la misma clave**
- No se puede acceder con `[]` (porque una clave puede tener varios valores)

**Ejemplo**
```cpp
#include <unordered_map>
#include <string>

int main() {
	std::unordered_multimap<std::string, int> edades;
	edades.insert({"Juan", 25});
	edades.insert({"Juan", 30}); // Dos valores para "Juan"

	// Recorrer todos los valores de "Juan"
	auto range = edades.equal_range("Juan");
	for (auto it = range.first; it != range.second; ++it) {
		std::cout << it->second << " "; // Salida: 25 30
	}
	return 0;
} 
```
### Diferencias clave

| Estructura           | Claves únicas | Acceso con `[]` |
| -------------------- | ------------- | --------------- |
| `unordered_set`      | Sí            | No              |
| `unordered_map`      | Sí            | Sí              |
| `unordered_multiset` | No            | No              |
| `unordered_multimap` | No            | No              |
