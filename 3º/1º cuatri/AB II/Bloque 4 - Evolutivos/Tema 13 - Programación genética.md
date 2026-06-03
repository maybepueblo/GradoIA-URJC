## 1. Contexto: ¿por qué existen estos algoritmos?

Los problemas de optimización difíciles (NP-completo, NP-duro) tienen espacios de búsqueda enormes y evaluaciones costosas. La fuerza bruta no es viable, por lo que se recurren a **metaheurísticas** — algoritmos que guían la búsqueda de forma inteligente sin garantizar el óptimo global.

Dentro de las metaheurísticas, los **Algoritmos Evolutivos (AE)** imitan la evolución natural:

```
Inicializar población → Evaluar → (Seleccionar → Cruzar → Mutar → Evaluar → Nueva generación) × N → Mejor individuo
```

Principios clave: *survival of the fittest*, diversidad para explorar, convergencia progresiva, elitismo para no perder buenas soluciones.

---

## 2. Algoritmos Genéticos (AG) — Base sobre la que se construye todo

| Concepto | Descripción |
|---|---|
| **Genotipo** | Representación codificada del individuo (cromosoma binario o entero) |
| **Fenotipo** | La solución real que expresa ese genotipo |
| **Cruce** | Opera sobre el genotipo; efecto en el fenotipo. Tipos: 1 punto, N puntos, uniforme... |
| **Mutación** | Cambio aleatorio en el genotipo |

Los operadores se aplican con cierta **probabilidad** sobre la población.

---

## 3. Programación Genética (PG / GP)

### 3.1 Idea central

> Los **individuos son árboles**, no cadenas lineales.

Esto permite representar directamente:
- Expresiones aritméticas: `4 − 5 + 2^7`
- Programas con bucles y condicionales
- Fórmulas lógicas

### 3.2 Componentes del árbol

- **Terminales (T):** hojas del árbol — variables, constantes (`x`, `3`, `π`)
- **Funciones / No terminales (F):** nodos internos con aridad definida (`+`, `sin`, `while`, …)
- **Propiedad de clausura:** cualquier función puede recibir cualquier otra función como argumento

### 3.3 Operadores en GP

**Recombinación (cruce):** se intercambian **subárboles** entre dos progenitores.

```
Progenitor 1           Progenitor 2
   +                      •
  / \          →         / \
 •   -               [sub] [sub]
```

**Mutación:** se sustituye un subárbol elegido al azar por un nuevo árbol generado aleatoriamente.

### 3.4 Inicialización de la población

Se fija una profundidad máxima inicial $D_{max}$:

| Método | Comportamiento |
|---|---|
| **Full** | Todas las ramas alcanzan exactamente $D_{max}$ |
| **Grow** | Las ramas crecen hasta $D_{max}$ mezclando terminales y funciones |
| **Ramped half-and-half** | La mitad con *full*, la mitad con *grow* — **el más usado** |

### 3.5 Selección

- Proporcional al *fitness* (ruleta).
- En poblaciones muy grandes se usa **sobreselección**: el 80 % de las operaciones eligen del mejor x% de la población.
- Reemplazo generacional + elitismo para no perder al mejor.

### 3.6 El problema del *Bloating* ("Survival of the Fattest")

Con el paso de las generaciones, los árboles tienden a crecer indefinidamente añadiendo código neutro. Contramedidas:
- Limitar el tamaño máximo de los hijos.
- **Presión de parsimonia:** penalizar en el *fitness* a los individuos grandes.
- Optimización bi-objetivo (fitness + tamaño).
- ⟶ Solución elegante: **Evolución Gramatical**.

### 3.7 Características prácticas de GP

- Requiere poblaciones **muy grandes** (miles de individuos).
- Ejecuciones lentas.
- Muy útil para **predicción y clasificación** (regresión simbólica).
- Campo activo: revista *Genetic Programming and Evolvable Machines*, bibliografía en [gpbib.cs.ucl.ac.uk](http://gpbib.cs.ucl.ac.uk/).

---

## 4. Evolución Gramatical (EG / GE)

> Propuesta original: Ryan & O'Neill, 1998.  
> Referencia de libro: O'Neill & Ryan, 2003, *Grammatical Evolution*, Kluwer.

### 4.1 Idea central

La EG combina lo mejor de AG y PG:
- Cromosoma **lineal de enteros** (como en AG) → operadores sencillos.
- El fenotipo es un **programa/árbol** (como en PG) → expresividad.
- La traducción genotipo → fenotipo se hace mediante una **gramática formal**.

### 4.2 La gramática BNF

Una gramática se define como la tupla `G = (N, T, S, P)`:

| Elemento | Significado |
|---|---|
| **N** | No terminales — símbolos que todavía hay que expandir `<expr>` |
| **T** | Terminales — símbolos finales del lenguaje `+`, `x`, `3` |
| **S** | Símbolo inicial (pertenece a N) |
| **P** | Reglas de producción: `<no-terminal> ::= opción1 \| opción2 \| ...` |

**Ejemplo** — gramática para expresiones matemáticas:

```
<func>  ::= <expr> <op> <expr> | <preop> (<expr>)
<expr>  ::= (<cte> <op> <var>) | <var>
<op>    ::= + | - | / | *
<var>   ::= x | y | z
<cte>   ::= A | B | C | D | E
<preop> ::= sin | cos
```

**Ventajas de usar gramática:**
- Define y limita el espacio de búsqueda.
- Permite incorporar conocimiento del dominio fijando términos.
- Se puede cambiar la gramática sin tocar el motor de optimización.

### 4.3 Proceso de decodificación (Mapeo genotipo → fenotipo)

El cromosoma es una secuencia de enteros, por ejemplo: `[15, 200, 22, 17, 123]`

**Regla de mapeo:** para elegir qué producción aplicar al siguiente no-terminal:

```
producción elegida = codón mod (número de alternativas de la regla)
```

**Traza del ejemplo** con la gramática anterior:

```
Paso 1: <func>  → codón 15, regla I tiene 2 alternativas → 15 mod 2 = 1 → <preop>(<expr>)
Paso 2: <preop> → codón 200, regla VI tiene 2 alternativas → 200 mod 2 = 0 → sin
Paso 3: <expr>  → codón 22, regla II tiene 2 alternativas → 22 mod 2 = 0 → (<cte> <op> <var>)
Paso 4: <cte>   → codón 17, regla V tiene 5 alternativas → 17 mod 5 = 2 → C
Paso 5: <op>    → codón 123, regla III tiene 4 alternativas → 123 mod 4 = 3 → *
Paso 6: <var>   → codón 15 (WRAP), regla IV tiene 3 alternativas → 15 mod 3 = 0 → x

Resultado fenotipo: sin(C * x)
```

![[Pasted image 20260603203113.png]]

> **WRAP:** si se agotan los codones antes de terminar la decodificación, se vuelve al inicio del cromosoma. Si se supera el límite de *wraps*, el individuo es **inválido** y se descarta.

### 4.4 Operadores genéticos en EG

Al operar sobre el genotipo (vector de enteros), los operadores son simples:

**Cruce de 1 punto sobre genotipo:**
```
P1: [15 | 200  22  17  123]        →   O1: [15  200  150  78  5]
P2: [ 8   11 | 150  78    5]       →   O2: [ 8   11   22  17  123]
```
El fenotipo del descendiente **no es una combinación exacta** de los fenotipos de los progenitores (efecto no lineal del mapeo).

**Mutación:** cambiar un codón por un valor diferente.
- Si el nuevo valor tiene el mismo resto módulo el número de producciones de la regla → **la mutación no tiene efecto fenotípico**.
- Cuantas más alternativas tenga una regla, menor es la probabilidad de que una mutación no tenga efecto.
- La mutación es más "radical" si afecta a un codón que mapea un símbolo no terminal profundo del árbol.

### 4.5 Ventajas de la EG frente a AG y PG

| Vs. Algoritmos Genéticos | Vs. Programación Genética |
|---|---|
| Cromosoma de tamaño variable (se usa parcial o totalmente) | Codificación de árboles **mucho más sencilla** |
| La gramática ajusta la búsqueda sin cambiar el motor | Controla el *bloating* limitando el número de wraps |
| Incorpora restricciones del dominio | Operadores genéticos más simples de aplicar |
| Delimita individuos no válidos | — |

### 4.6 Inconvenientes de la EG

- Diseñar la gramática adecuada puede ser complejo.
- Permitir muchos *wraps* ralentiza el descarte de individuos inválidos.

---

## 5. Aplicaciones reales de la EG

- Modelos de glucosa en diabéticos.
- Diseño automático de gestores de memoria dinámica (DMMs).
- Configuración automática de cachés.
- Creación de máquinas de estados finitos (FSMs).
- Reglas para sistemas de *trading*.
- Regresión simbólica y predicción en entornos dinámicos.
- Algoritmos de comportamiento en robots.
- Reconocimiento de voz y sonidos.
- Evolución de curvas fractales.

---

## 6. Software disponible

| Herramienta | Lenguaje | Notas |
|---|---|---|
| **GEVA** | Java | Primera implementación (UCD), en desuso |
| **JECO** | Java | GE + más AEs — [github.com/ABSysGroup/jeco](https://github.com/ABSysGroup/jeco) |
| **PonyGE2** | Python | Activo, mantenido por UCD — [github.com/PonyGE/PonyGE2](https://github.com/PonyGE/PonyGE2) |
| **DSGE** | Python | *Dynamic Structured GE*, mejora de codificación — [github.com/nunolourenco/dsge](https://github.com/nunolourenco/dsge) |

---

## 7. Mapa conceptual del tema

```
Metaheurísticas
└── Algoritmos Evolutivos
    ├── Algoritmos Genéticos (AG)
    │   └── cromosoma lineal, operadores sobre bits/enteros
    ├── Programación Genética (PG/GP)
    │   └── cromosoma = árbol, recombinación de subárboles
    │       ⚠ Problema: bloating
    └── Evolución Gramatical (EG/GE)
        ├── genotipo: vector de enteros (como AG) ✓
        ├── fenotipo: árbol/programa (como PG) ✓
        ├── mapeo: gramática BNF + operación módulo
        └── controla bloating mediante wraps ✓
```
