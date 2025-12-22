#### ¿Por qué?
- **Autómatas Finitos** -> Modelado de protocolos y circuitos electrónicos.
- **Expresiones regulares** -> Uso en programación y scripting (Shell, Perl, UNIX)
- **Gramáticas libres de contexto**
	- Describir sintaxis de lenguajes de programación
	- Analizar compiladores
	- Describir lenguajes naturales

#### Importancia teórica
- Comprender limitaciones de soluciones software a diversos problemas.
- Identificar los dos tipos de problemas por excelencia:
	- No decidibles -> No existe ningún programa que pueda hacerlo. *Un compilador descarta programas que imprimen una determinada palabra*.
	- No tratables -> Hay programas pero ninguno de ellos es rápido. (complejidad computacional)

#### Objetivos
Tenemos una serie de objetivos que cumplir de cara a esta asignatura:
- Examinar modelos abstractos
- Comprender limitaciones de cada modelo
- Entender las equivalencias entre diversos modelos
- Manejar sistemas discretos 
- Construir traductores dirigidos por sintaxis

#### Historia
Vamos a dar una pincelada muy breve a la historia de esta asignatura:
- 1952: Primer compilador A-0 por Grace Murray Hopper
- 1956: Gramática universal de Chomsky
- 1978: Donald Knuth desarrolla TeX

### Conceptos fundamentales

#### Modelo de cálculo

Es una abstracción matemática que describe como realizar cálculos y procesar información. Todo cálculo basado en un algoritmo consiste en un proceso de comunicación:
- Algo se emite (input)
- Se manipula (transmisión)
- Y se responde (output)

#### Definiciones clave

==¿Qué es susceptible de ser comunicado?==
Es comunicable todo aquello expresado en un alfabeto finito.

Veamos diversas nociones que son indispensables para el cursado de esta asignatura:
- Alfabeto (Σ): Conjunto finito de símbolos
- Palabra: Lista finita de símbolos de un alfabeto
- Σ* : Conjunto de todas las palabras posibles sobre un alfabeto
- Lenguaje: Subconjunto de Σ*

##### Dos precisiones importantes
Para ver esto, imponemos un lenguaje x1 ··· xn que permite expresar la palabra (x1, ···, xn) perteneciente al alfabeto de n. Esto es una cadena de caracteres sin ambigüedad en la interpretación. 

- La palabra vacía se denota ε. Independientemente del alfabeto Σ, Σ⁰ = {ε} y su longitud es cero (|ε| = 0).
- El conjunto de todas las palabras Σ* incluye la palabra vacía: 
	- Por ejemplo {0, 1}* = {ε, 0, 1, 00, 01, 10, 11, ...}. 
	- El conjunto de cadenas no vacías se considera Σ⁺ siendo Σ* = Σ⁺ U {ε}
##### Ejemplos

- **Quijote** -> Podríamos escribir el libro al completo de el Quijote, siendo una palabra sobre nuestro alfabeto castellano, donde tenemos que "," y "." son los obvios, : siendo el "punto y aparte" y ♯ los espacios entre palabras.
- **Otello** -> No es una palabra del castellano. Es una palabra sobre este, que no es un alfabeto, sino un lenguaje C ⊆ Σ* (un lenguaje derivado del alfabeto original)
	- Una palabra pertenece a C si está incluida en la RAE o se construye sobre palabras incluidas en este. 
	- El "Otello" pertenece al inglés I ⊆ Σ*. Aunque la comunicación occidental tiene en común el alfabeto.

Así, decimos que la simplicidad del alfabeto no tiene relación con la simplicidad del lenguaje.
###### Otros
- Cadenas con n ceros seguidos de n unos
- Números binarios primos
- Σ* (todas las palabras posibles)
- Lenguaje vacío
- Lenguaje con solo cadena vacía

### Algoritmos y Lenguajes

#### Descripción del lenguaje

Nos es habitual describir un lenguaje utilizando una descripción de conjuntos: $$\{w |algo \space acerca \space de \space w\}$$
Ejemplos son los siguientes:
- {w|w es un entero binario que es un primo}
- {w|w es un programa C sintácticamente correcto}

>[!NOTE]
>Podemos tomar cada lenguaje de programación como un subconjunto de los caracteres ASCII

Damos vital importancia a la notación para poder interpretar el significado de forma fiable:
- Conjuntos en mayúsculas, palabras con *w, x, y, z* y las letras *x1, x2, ...*
- Usar parámetros o fórmulas matemáticas siempre que se pueda.

**Ejemplos** para Σ = {0, 1}:
- L1 = {0^n 1^n | n ≥ 1}
- L2 = {x0 |x ∈ Σ*}
- L3 = {w | |w| ≤ 3}
- L4 = {x01y |x, y ∈ Σ*}

##### Ejercicios 

- ¿Qué tipo de palabras describe el siguiente lenguaje?. $$L_1 = \{0^i1^j | 0 \le i \le j\} \space siendo \space i,j \in N$$
La notación nos indica lo siguiente:
- Tenemos palabras formadas por 0s seguidos de 1s.
- i representa el número de 0s y j el de 1s.
- La condición nos especifica lo siguiente:
	- i ha de ser mayor o igual a cero (puede no haber ceros)
	- i debe de ser menor o igual a j (debe haber al menos tanto unos como ceros)




- Definir la relación con el siguiente lenguaje: $$L_2 = \{ w | w \space contiene \space más \space 1s \space que \space 0s \}$$
En este caso, vemos que en realidad es lo mismo pero expresado de una forma menos matemática, debido a que en esencia es lo mismo. Siendo esto que podemos no tener 0s pero si 1s, habiendo de cumplirse siempre que haya más 1s que 0s, lo que en este caso no podrá haber un número igual de 1s que de 0s.
#### Definición de problema

Estudiamos una correspondencia de tipo f: D --> S donde:
- D = Datos
- S = Soluciones

Entonces, resolvemos mediante un algoritmo que evalúa f. 

#### Problemas decisionales 

Evaluamos funciones parcialmente definidas *f*: Σ* --> {0, 1}. Aquí, la idea es resolver problemas que tienen respuesta positiva o negativa. 

Decimos que estamos determinando pertenencia a un lenguaje.

#### Lenguajes recursivamente enumerables

Denominamos LRE a un lenguaje cuando se puede decidir a través de un algoritmo la pertenencia de una palabra a un lenguaje:
- Veamos manipulaciones de objetos de Σ*, éstos nos ayudarán a definir lenguajes.

##### Manipulaciones
La operación esencial sobre Σ* es la concatenación o adjunción de palabras:
- · : Σ* x Σ* --> Σ*
- (x, y) --> x · y

es decir, si x = x1 ··· xn e y = y1 ··· ym entonces:

	x · y = x1 ··· xny1 ··· ym

Recordamos que denotaremos por ε ∈ Σ* la palabra vacía (para distinguirla del lenguaje vacío ∅)

##### Teorema

>[!Teorema]
(Σ*, ·) es un monoide a (semigrupo unitario), donde ε es el elemento
neutro, y la longitud define un morfismo de monoides entre Σ∗ y el
conjunto de los números naturales. El monoide Σ∗ es abeliano b si y
solamente si el cardinal de Σ es uno.
>- a Un conjunto X con una operación ∗ : X × X =⇒ X, con propiedad asociativa y
conteniendo elemento neutro
>- b Todos sus elementos conmutan al operarlos>

1. Σ* representa todas las posibles cadenas (incluyendo la cadena vacía) que podemos formar con los símbolos de un alfabeto Σ. Por ejemplo, si Σ = {a}, entonces Σ* = {ε, a, aa, aaa, ...}, donde ε es la cadena vacía.
2. La operación · es simplemente la concatenación de cadenas. Por ejemplo: "hola" · "mundo" = "holamundo"
3. Cuando decimos que es un monoide, significa que:
    - Podemos concatenar cadenas (la operación)
    - Si concatenamos (A·B)·C es lo mismo que A·(B·C) (asociatividad)
    - Existe un elemento neutro ε (la cadena vacía) que al concatenarlo con cualquier cadena no la modifica
4. La longitud de una cadena es un morfismo significa que la longitud de la concatenación de dos cadenas es igual a la suma de sus longitudes individuales. Por ejemplo: longitud("hola"·"mundo") = longitud("holamundo") = 9 = 4 + 5 = longitud("hola") + longitud("mundo")
5. La parte más interesante es la última: este monoide solo es abeliano (conmutativo) cuando el alfabeto tiene un único símbolo.

Para entender esto último, pensemos en ejemplos:

- Si Σ = {a}, entonces aa·aaa = aaaaa = aaa·aa (es conmutativo)
- Si Σ = {a,b}, entonces ab·ba = abba ≠ baab = ba·ab (no es conmutativo)

En resumen, cuando concatenamos cadenas, el orden importa (no es conmutativo), excepto cuando solo tenemos un símbolo disponible, porque entonces todas las cadenas son repeticiones de ese único símbolo y ahí sí da igual el orden.
### Operaciones con palabras y lenguajes

Ya hemos visto la operación de concatenación, veamos otras
#### Palabras
- Reverso de una palabra -> ^R : Σ* --> Σ*
	- Es una biyección dada mediante si w = ε, ε^R = ε, o si ω = x1 · · · xn ∈ Σ*, con xi ∈ Σ, donde definimos que ω^R := xnxn−1 · · · x1 ∈ Σ*.

- Potencia de palabras --> Se define recursivamente a partir de la concatenación. Dada una palabra w ∈ Σ* y un número natural, definimos la potencia w^n, mediante:
	- Si n = 0 entonces w⁰ := ε+
	- Para n >= 1 definimos que ω^n := ω · ω^{n−1}

##### Teorema

>[!Teorema]
>Dado un alfabeto finito Σ y dos palabras ω1, ω2 ∈ Σ∗, entonces tenemos que :
>
>$$(w_1w_2)^R = w_2^Rw_1^R$$
>$$(w_1^n)^R = (w_1^R)^n$$

Esto quiere decir que el reverso de la multiplicación de dos palabras es igual a la multiplicación del reverso de las palabras. Asimismo, debajo se especifica que el reverso de una potencia es lo mismo que la potencia de un reverso.
#### Lenguajes
- Unión de lenguajes --> Dados L1, L2 como un subconjunto de todas las posibles cadenas, tenemos que:

	L1 ∪ L2 = {ω ∈ Σ* | \[ω ∈ L1\] ∨ \[ω ∈ L2\]}.

- Concatenación de lenguajes --> Dados L1, L2 como un subconjunto de Σ*:

	L1 · L2 = {ω1 · ω2 ∈ Σ* | ω1 ∈ L1, ω2 ∈ L2}

- Potencia de lenguajes:
	- Si n = 0, L⁰ = {ε}
	- Si n >= 1, L^n = L · (L^{n-1})

- Clausura transitiva o monoide generado por lenguaje -> Dado un lenguaje L ⊆ Σ* definimos el monoide L* que genera mediante la igualdad siguiente: $$L^*=\bigcup_{n \in N} L^n$$
- Clausura positiva de un lenguaje -> Dado un lenguaje L ⊆ Σ* definimos la clausura positiva L⁺ que genera mediante la igualdad siguiente: $$L⁺ = \bigcup_{n\geq1} L^n$$
#### Ciertas puntualidades
- L1 · L2 no es generalmente conmutativo (L2 · L1)
- Propiedades distributivas

### Gramáticas Formales

>[!TIP] Definición
>Una gramática formal es una cuaterna del tipo G = (V, Σ, Q0, P) donde tenemos que:
>- V es un conjunto finito llamado alfabeto de símbolos no terminales o simplemente, alfabeto de variables.
>- Σ es otro conjunto finito que verifica que la intersección entre V y este nos da el vacío y se denonmina alfabeto de símbolos terminales.
>- Q0 que pertenece a V es la variable que representa el símbolo inicial. 
>- P ⊆ (V ∪ Σ)\* × (V ∪ Σ)\* es el conjunto de producciones (no infinito)

Para operar sobre las palabras, hemos de asociar una dinámica. Hemos de definir cómo operar sobre símbolos no terminales.

#### Sistema de transición










