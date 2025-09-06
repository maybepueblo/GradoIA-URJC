#### Lenguaje de una gramática libre de contexto

Definamos L(G) que es una gramática G = (V, Σ, Q₀, P) como el conjunto de todas las cadenas terminales que tienen derivaciones desde el símbolo inicial Q₀. Cuando G es una gramática libre de contexto, el lenguaje generado se denomina lenguaje libre de contexto o independiente del contexto. 

##### Ejemplo: Lenguaje de palíndromos

Vamos a presentar una gramática sobre el lenguaje {0, 1}: G = ({A}, {0, 1}, A, P) donde P contiene las producciones A → ε | 0 | 1 | 0A0 | 1A1. 

![[Árbol derivado 01110|1000]]

Esto es un árbol derivado para la gramática 01110 usando esta gramática.

#### Ejemplos de gramáticas

Diseña gramáticas para los siguientes lenguajes
1. L1 = {0^i 1^j |k = 2j, k, j ≥ 0}
2. L2 = {w| ♯1 (w) = ♯0(w)}, donde ♯i es el número de símbolos i en w
3. L3 = {w| ♯1 (w) > ♯0(w)}
4. L4 = {w| ♯1 (w) = 2 · ♯0(w)}

#### Ambigüedad en gramáticas y lenguajes

Una gramática se considera ambigüa si existe al menos una palabra en el lenguaje que tiene más de un árbol de derivación posible. No todas las gramáticas tienen la propiedad de ser no ambiguas por lo tanto. 

En algunos casos, es posible rediseñar una gramática ambigua para hacerla no ambigua, pero existen lenguajes "inherentemente ambiguos" para los cuales no es posible crear gramática no ambigua. 