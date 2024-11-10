
### Voraces

Los algoritmos voraces son una técnica que construye soluciones paso a paso tomando decisiones óptimas de forma local, sin reconsiderar decisiones anteriores. Es decir, tomamos decisiones en base a lo que tenemos que decidir ahora, no nos importa lo anterior.

**Características principales**
- Solución de forma iterativa
- Decisión óptima en cada paso
- Decisiones tomadas se consideran definitivas y no se reconsideran
- Buscan optimizar un objetivo

#### Componentes esenciales

1. **Conjunto de candidatos**
2. **Función de selección** (mejor candidato en cada paso)
3. **Función de factibilidad** (verifica si la selección es válida)
4. **Función solución** (determinamos si hemos alcanzado una solución)
5. **Función objetivo** (evaluamos lo óptima que es la solución)

#### Ventajas y desventajas

**Ventajas**
- Sencillo de implementar
- Eficiencia computacional (complejidad polinómica), véase [[Complejidad Algorítmica]]
- Encuentran la solución óptima en varios problemas

**Desventajas**
- No siempre hay solución óptima
- La no reconsideración de decisiones puede llevar a óptimos locales
- Es dificil encontrar la función de selección adecuada
- Compleja demostración formal de optimalidad

#### Aplicaciones

1. **Problema del cambio de monedas**
	- **Objetivo** --> Devolver cantidad M usando el mínimo número de monedas
	- **Estrategia** --> Seleccionar siempre la moneda de mayor valor posible
2. **Minimización del tiempo de espera en sistema**
	- **Objetivo** --> Minimizar el tiempo medio de espera de n clientes
	- **Estrategia** --> Ordenar los clientes por tiempo de servicio creciente
3. **Problema de la mochila fraccionaria**
	- **Objetivo** --> Maximizar el valor de objetos en una mochila con capacidad limitada
	- **Estrategia** --> Seleccionar objetos por mayor ratio valor/peso
	- Se permiten fracciones de objetos
4. **Planificación con plazo fijo**
	- **Objetivo** --> Maximizar beneficio realizando tareas antes de su fecha límite.
	- **Estrategia** --> Ordenar tareas por beneficio decreciente.
	- Cada tarea tiene un beneficio tope.

#### Estructura general

```python
función voraz(C: conjunto): conjunto
    S ← ∅
    mientras C ≠ ∅ y no solución(S) hacer
        x ← seleccionar(C)
        C ← C \ {x}
        si factible(S ∪ {x}) entonces
            S ← S ∪ {x}
        fin_si
    fin_mientras
    si solución(S) entonces
        devolver S
    si_no
        devolver ∅
    fin_si
fin_función
```

### Voraces aplicado a grafos

- Kruskal > Prim (todo lo de prim se puede hacer con kruskal pero no al revés)


