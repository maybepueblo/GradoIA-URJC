## ¿Por qué?
Si bien nosotros tenemos sentido común, los ordenadores son literales.
- **Humano:** "Si llueve, me mojo" (si hay lluvia, te mojas)
- **Máquina**: No entiende relación causa-efecto
La lógica nos permite formalizar el conocimiento para que un ordenador pueda sacar conclusiones nuevas a partir de datos viejos (Inferencia).
## 1. Lógica Proposicional
Forma más básica de lógica, centrada en proposiciones completas. Nos importa si la frase completa es **Verdadera** o **Falsa**
### Sintaxis (Construcción)
Se define por dos conjuntos de símbolos:
1. **Símbolos de proposición**: Variables que representan afirmaciones (*e.j*: $p, q, r$,martes,animal,etc.)
	- *p* = "Hoy es martes"
	- *q* = "Llueve"
2. **Conectivas**: Operadores lógicos para unir las frases:

| **Símbolo**       | **Nombre**            | **Significado Humano** | **Ejemplo (p→q)**                                     |
| ----------------- | --------------------- | ---------------------- | ----------------------------------------------------- |
| $\neg$            | **Negación**          | NO                     | $\neg p$ (No es martes)                               |
| $\wedge$          | **Conjunción**        | Y                      | $p \wedge q$ (Es martes Y llueve)                     |
| $\vee$            | **Disyunción**        | O                      | $p \vee q$ (Es martes O llueve)                       |
| $\to$             | **Implicación**       | SI... ENTONCES...      | $p \to q$ (Si es martes, entonces llueve)             |
| $\leftrightarrow$ | **Doble Implicación** | SI Y SOLO SI           | $p \leftrightarrow q$ (Es martes si y solo si llueve) |
Las **Fórmulas Bien Formadas (fbf)** se construyen usando estos símbolos de manera recursiva

**Limitación**
La LP es muy pobre. Si decimos "Juan es un hombre" (*p*) y "Pedro es hombre" (*q*), la máquina no sabe que *p* y *q* tienen algo en común (ser hombre).
## 2. Lógica de Predicados (Primer Orden)
Abrimos la frase y miramos en su interior. No usamos solo letras sueltas, sino **Sujetos** y **Propiedades**.

### Elementos nuevos
1. **Constantes:** Objetos concretos (minúscula o nombre propio)
	- *EJ* `juan`, `madrid`, `tuna`
2. **Predicados**: Propiedades o relaciones (empiezan con mayúscula)
	- *Perro(x)*: "x es un perro"
	- *Ama(x, y)*: "x ama a y"
3. **Variables**: Marcadores genéricos (*x, y, z*). Sirven para decir "cualquiera" o "alguien".
4. **Cuantificadores:** La clave de todo.

**Los dos cuantificadores** (IMPORTANTES)
- **Universal ($\forall$)**: "Para todo..."
	- Significa todos sin excepción
	- *Ejemplo:* "Todos los perros son animales"
	- *Fórmula:* $\forall x(Perro(x)\rightarrow (Animal(x))$
	- *Traducción: "Para todo x, si x es Perro, entonces x es Animal"*
- **Existencial ($\exists$):** "Existe algún..."
	- Significa al menos uno
	- *Ejemplo:* "Algunos alumnos aprueban"
	- *Fórmula:* $\exists x (Alumno(x) \wedge Aprueba(x))$
	- *Traducción*: "Existe un x tal que x es Alumno y x aprueba"
## 4. Inferencia: El método de resolución
Es el **cómo piensa la máquina**. La inferencia es el proceso de descubrir una verdad nueva a partir de lo que ya sabíamos. 

El método estrella es la **Resolución por Refutación** (Reducción al Absurdo)

**Caso práctico**
Imaginemos que somos un detective. Tenemos pistas (premisas) y queremos probar que Juan es el asesino (Conclusión). En lugar de probar que es culpable, asumes lo contrario y ves si eso da una contradicción imposible (que esté en dos sitios a la vez por ejemplo). Si hay contradicción, la suposición es falsa y por ende: "Juan es culpable".

**Pasos del algoritmo**
1. **Formalizar:** Traducimos frases a lógica ($\forall, \exists, \rightarrow, \neg$)
2. **Negar la conclusión:** Tomas lo que quieres probar ($C$) y añadimos su negación ($\neg C$) a tu lista de hechos. 
3. **Pasamos a Forma Clausular (Limpieza)**
	- Quitamos cuantificadores ($\forall, \exists$)
	- Quitamos flechas ($\rightarrow$). Truco: $A\rightarrow B$ es igual a $\neg A \vee B$ 
	- Dejarlo todo como una lista de esto o lo otro
4. **Resolver (Choque de cláusulas)** Buscar parejas que se cancelen
	- Si tenemos `(Llueve)` y `(No Llueve)`
	- Contradicción (Cláusula Vacía)
5. **Resultado**
	- Si llegamos a la **Cláusula Vacía**, hemos demostrado que el conjunto era inconsistente. Por tanto, la conclusión original era **VERDADERA**

# Mayor profundidad
Sección con una explicación más extensa por si acaso no es suficiente lo de arriba.
### Formalizar conocimiento
Para representar conocimiento en lenguaje natural, se usan patrones comunes para las conectivas:
- $A\wedge B$: "A y B", "A pero B", "A sin embargo B", etc.
- $A\vee B$: "A o B", "O bien A, o bien B", "Al menos A o B"
- $A\rightarrow B$: "Si A, luego B", "B si A", "A sólo si B", etc.
- $A\leftrightarrow B$: "A necesario y suficiente para B"
### Semántica
La semántica en LP se basa en la interpretación (I) que asigna un valor de verdad ($\{V, F\}$) a cada proposición atómica. Los valores de verdad de las fórmulas compuestas se determinan aplicando las tablas de verdad de cada conectiva
### Definiciones claves
- **Satisfacción:** Una interpretación $I$ satisface fórmula $A$ si el valor de verdad de $A$ bajo $I$ es verdadero ($I(A) = V$)
- **Fórmula satisfacible**: Si existe alguna interpretación $I$ que la satisface
- **Fórmula insatisfacible**: Si no existe ninguna interpretación $I$ que la satisfaga como por ejemplo $p \wedge \neg p$ 
- **Modelo:** Una interpretación $I$ que satisface una fórmula
## Inferencia en Lógica
El objetivo es contestar automáticamente sobre si una fórmula $\alpha$ es consecuencia lógica de una Base de Conocimiento (BC) Δ (Δ⊨α). Esto se logra aplicando un conjunto de **reglas de inferencia** para obtener conclusiones intermedias hasta llegar a $\alpha$

Tenemos varios métodos de inferencia
1. **Modus Ponens Generalizado:** Usa la regla de *Modus Ponens* como única regla de inferencia
2. **Deducción natural:** Usa un conjunto de reglas de inferencia. Algunas de ellas son:
	- Modus Ponens: $\frac{A\rightarrow B, A}{B}$ 
	- Modus Tollens: $\frac{A\rightarrow B, \neg A}{B}$
	- Silogismo Disyuntivo: $\frac{A\vee B, \neg A}{B}$
	- Silogismo Hipotético (Transitiva): $\frac{A\rightarrow B, B\rightarrow C}{A \rightarrow C}$
3. **Método de resolución**: Usa una única regla de inferencia, la regla de resolución. Este método es fundamental en la lógica de predicados.
## Lógica de predicados (Primer Orden - LPO)
Más expresiva que su antecesora, permite hablar sobre objetos, propiedades, relaciones y usar cuantificadores
### Sintaxis
Hay nuevos símbolos.
- **Símbolos de constante**: $a, b, c,...$
- **Símbolos de variable:** $x, y, z,...$
- **Símbolos de función:** $f, g, h,...$
- **Símbolos de predicado:** $P, Q, ...$ (relaciones con $n$ argumentos)
- **Términos:** Una constante, una varable, o una función aplicada a términos $f(t_1,t_2,...,t_n)$
Además de estas conectivas se introducen las **Cuantificadoras**
- **Cuantificador existencial ($\exists$)**: "Existe al menos uno"
- **Cuantificador universal ($\forall$)**: "Para todo"
Las **Fórmulas Bien Formadas (fbf)** ahora incluyen predicados $P(t_1, t_2, ..., t_n)$ y la aplicación de estos cuantificadores.
### Semántica
La semántica de LPO se centra en cómo los cuantificadores afectan el valor de verdad
- **Existencial ($\exists$)**: $I(\exists xA(x))= V$ si $A(x)=V$ para **al menos un elemento**
- **Universal ($\forall$)**: $I(\forall xA(x))= V$ si $A(x)=V$ para **todo elemento x**
### Representación en LPO
LPO permite formalizar conocimiento complejo del lenguaje natural:
- *Ejemplo 1:* "Juan tiene un perro" se representa como $\exists x(Perro(x) \wedge Posee(Juan, x))$
- *Ejemplo 2*: "Todos los que tienen perros aman a los animales" se representa como $\forall x(\exists y(Perro(y)\wedge Posee(x, y)) \rightarrow AmanteAnimales(x))$
## Inferencia en LPO: Método de resolución
En LPO, el principal mecanismo de inferencia es el **Método de Resolución** que se basa en la **demostración por contradicción** o **refutación**
### Refutación
Para demostrar que una fórmula $\alpha$ es consecuencia lógica de Δ (Δ⊨α), se debe demostrar que la base de conocimiento Δ', que resulta de insertan la negación de $\alpha$ en Δ es inconsistente (insatisfacible)$$Δ\cup\{\neg \alpha\}\vDash Falso$$
### Simplificación de fórmulas
Para aplicar la resolución, todas las fórmulas deben ser simplificadas y convertidas a la **Forma Normal Skolem** (FNS) que culmina en la **Forma Clausular**. Los pasos de simplificación incluyen:
1. Forma Prenex: Mover los cuantificadores al principio de la fórmula
2. Cierre existencial: Quitar variables libres
3. Forma Normal Conjuntiva: Convertir la fórmula en una conjunción de disyunciones
4. Eliminar cuantificadores existenciales: Sustituirlos por una constante de Skolem o una función de Skolem
### Forma Clausular
Es una disyunción de literales (una fórmula atómica o su negación). La Forma Clausular es el conjunto de estas cláusulas (que están unidas implícitamente por conjunciones)
### Aplicación del Método
Una vez que el conjunto $Δ\cup\{\neg \alpha\}$ está en forma clausular, se aplica la regla de resolución básica de forma sucesiva. Si en el proceso de aplicación se logra derivar la cláusula vacía, se demuestra que el conjunto original de cláusulas es insatisfacible.