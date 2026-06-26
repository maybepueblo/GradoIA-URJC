# Introducción
Este tipo de lógica nos permite representar y razonar con **información imprecisa**. Es una **generalización** de la **lógica clásica**.
# Conjuntos borrosos
## Conjuntos clásicos
- Dado universo $E$, un conjunto $A\subseteq E$ se representa mediante su **función característica**, $\upvarphi_A:E\rightarrow\{0, 1\}$. Esto asigna a cada elemento del universo o 0 para no pertenecer a A, o 1 para indicar que sí pertenece.
## Conjuntos borrosos
 - Dado universo $E$, un conjunto $A\subseteq E$ se representa mediante su **función característica**, $\mu_A:E\rightarrow\{0, 1\}$. Esto asigna a cada elemento del universo un valor entre 0 y 1 que indica el grado de pertenencia del elemento al conjunto.
# Operaciones con conjuntos borrosos
Dados dos conjuntos borrosos $\mu_A$, $\mu_A$ $: E\rightarrow[0, 1]$, ¿cómo definir los conjuntos borrosos $\mu_{A\cap B},\mu_{A\cup B},\mu_{A'}:E\rightarrow[0,1]$?
- **Requisito básico:** los conectivos borrosos han de ser una **extensión** de los correspondientes **conectivos clásicos**.
- Solución habitual:
	- $\mu_{A\cap B}(x)=T(\mu_A(x),\mu_B(x)), con T:[0, 1]²\rightarrow[0,1]$ 
	- $\mu_{A\cup B}(x)=S(\mu_A(x),\mu_B(x)) con S:[0, 1]²\rightarrow[0,1]$
	- $\mu_{A'}(x)=N(\mu_A(x)) con N: [0, 1] \rightarrow [0,1]$

| μA(x) | μB(x) | T = μA∩B(x) | S = μA∪B(x) | N = μA'(x) |
| :---: | :---: | :---------: | :---------: | :--------: |
|   0   |   0   |      0      |      0      |     1      |
|   0   |   1   |      0      |      1      |     1      |
|   1   |   0   |      0      |      1      |     0      |
|   1   |   1   |      1      |      1      |     0      |
## Intersección: normas triangulares
Decimos que una norma triangular o **t-norma** es una función $T:[0,1]²\rightarrow [0, 1]$ conmutativa, asociativa, monótona no decreciente y tal que $T(x, 1) = x$ para todo $x \in [0,1]$

Las T-normas más habituales son:
- $T(x, y)= Min(x, y)$ -> (t-norma mínimo)
- $T(x, y) = Prod(x, y) = x·y$ -> (t-norma producto)
- $T(x, y)=W(x, y)=Max(0,x+y-1)$ -> (t-norma de Lukasiewicz)

Propiedades más importantes:
- $T(x, 0)=0$ para todo $x\in[0, 1]$
- Para toda t-norma T, $\forall x, y\in [0, 1] T(x, y)\leq Min(x, y)$
- $\forall x, y\in[0, 1]: W(x, y)\leq Prod(x, y)\leq Min(x, y)$
- La única t-norma que cumple la idempotencia es $Min$

Usando el *ejemplo*: "Juan pertenece a los estudiantes altos y medios"

Si suponemos una altura de 178cm y $\mu_{Alto}(178)=0.7$, $\mu_{Medio}(178)=0.4$ entonces:
$$\mu_{Alto\cap Medio}(178)=T(\mu_{Alto}(178), \mu_{Medio}(178))=T(0.7, 0.4)$$
Si usásemos la t-norma "Prod":$$\mu_{Alto\cap Medio}(178)=0.7·0.4=0.28$$
## Unión: conormas triangulares
Una conorma triangular o **t-conorma** es una función $S: [0,1]² \rightarrow [0,1]$ conmutativa, asociativa, monótona no decreciente y tal que $S(x, 0)=x$ para todo $x \in [0, 1]$

Las T-conormas más habituales:
- $S(x, y) = Max(x, y)$ -> (t-conorma máximo)
- $S(x, y) = Prod*(x, y) = x + y - x·y$ -> (t-conorma producto)
- $S(x, y) = W*(x, y) = Min(1, x+y)$ -> (t-conorma de Lukasiewicz)

Supongamos una altura de 178cm, y $\mu_{Alto}(178)=0.7, \mu_{Medio}(178)=0.4$, entonces:$$\mu_{Alto\cup Medio}(178)=T(\mu_{Alto}(178), \mu_{Medio}(178))=T(0.7, 0.4)$$
Si usásemos la t-conorma $Prod^*$:
$$\mu_{Alto\cup Medio}(178)=0.7+0.4-0.7·0.4=0.28$$
## Complementario (Negación)
Una **negación fuerte** es una función $N:[0, 1]\rightarrow[0,1]$ que cumple:
- $N(0)=1$
- $N(1)=0$
- es no creciente (si $x\leq y$ entonces $N(y)\leq N(x)$)
- es involutiva $(\forall x\in [0, 1]N(N(x))=x)$
Claramente la más usada es $N(x)=1-x$
## Dualidad
En conjuntos (Ley de Morgan):
- $A\cup B\equiv(A'\cap B')'$
- $A\cap B\equiv(A'\cup B')'$
Sea T una t-norma, S una t-conorma y N una negación fuerte:
- $T^* (r, s)=N(T(N(r), N(s)))$ es la **t-conorma dual** de T
- $S^* (r, s)=N(S(N(r), N(s)))$ es la **t-norma dual** de S
- T es la t-norma dual de S si y sólo si S es la t-conorma dual de T.

*Ejemplos* tomando $N(x)=1-x$
- Min(x, y) --- Max(x, y)
- Prod(x, y) --- Prod*(x, y)
- W --- W*
## Modificadores lingüísticos
### Externos
$\mu_{MP}(x)=\alpha(\mu_P(x))$ con $\alpha:[0,1]\rightarrow[0,1]$
- Ejemplos: muy, moderadamente...
- Suele usarse:$$\begin{align}\mu_{MUY P}(x)=(\mu_P(x))^2\\\mu_{MOD P}(x)=(\mu_p(x))^{1/2}\end{align}$$
### Internos
$\mu_{MP}(x)=\mu_P(\alpha(x))$ con $\alpha:E\rightarrow E$
- Ejemplo: antónimos (alto/bajo, joven/viejo, grande/pequeño...)
- Normalmente: $\mu_{aP}(x)=\mu_P(\alpha(x)) con \alpha:E\rightarrow E$, $\alpha(\alpha(x))=x$
- No confundir *antónimo* con *negación* (normalmente $\mu_{aP}(x)\leq\mu_{NO P}(x)$)
- Típicamente, cuando $E = [a, b]$ de la recta real, se suele tomar$$\begin{align}\alpha:[a, b]\rightarrow [a, b]\\\alpha(x)=a+b-x\end{align}$$
## Variable lingüística
Está definida por un nombre de variable y un conjunto de términos que son los valores que puede tomar. Cada término se representa mediante un conjunto borroso.

![[Pasted image 20260622204711.png]]
# Lógica borrosa
Son **lógicas multivaluadas**, siendo las más frecuentes las lógicas borrosas estándar en las que los valores de verdad pertenecen al intervalo [0,1]. 

**Grados de verdad**
Decimos que es $P(x)$ siendo esto "x es P", representado por $\mu_P(x)$ siendo $\mu_P:E\rightarrow[0,1]$

**Fórmulas lógicas**
- Conjunción $(P(x) \wedge Q(y))$: $\mu_{P\wedge Q}(x, y)=T(\mu_P(x), \mu_Q(y))$, T T-norma 
- Disyunción $(P(x) \vee Q(y))$: $\mu_{P\vee Q}(x, y)=S(\mu_P(x), \mu_Q(y))$, S T-conorma
- Negación $(\neg P(x))$: $\mu_{\neg P}(x)=N(\mu_P(x))$, N negación fuerte
- Implicación $(P(x) \rightarrow Q(y))$
## Implicación en lógica borrosa
$P(x) \rightarrow Q(y)$ (**"Si x es P, entonces y es Q"** donde P y Q son predicados borrosos).
- Solución: ${\mu_{P\rightarrow Q}(x, y)=J(\mu_P(x), \mu_Q(y))}$ 
	- Algunas funciones habituales:
		- Mamdani: T = Min; J(x, y) = Min(x, y)
		- Larsen: T = Prod; J(x, y) = x·y
		- Lukasiewicz: T = W; J(x, y) = Min(1, 1 - x + y)
		- Kleene-Dienes: S = Max; J(x, y) = Max(1 - x, y)
		- Reichenbach: S = Prod*; J(x, y) = 1 - x + x·y
# Inferencia borrosa
Reglas de inferencia clásica del *Modus Ponens* (MP)
$$\begin{array}{c} p \rightarrow q \\ p \\ \hline q \end{array}$$
Luego, tenemos que generalizarlo:
$$\begin{array}{c} P(x) \rightarrow Q(y) \\ P^*(x) \\ \hline Q^*(y) \end{array}$$
Siendo $P^*$ y $Q^*$ predicados borrosos que representan una cierta modificación de los predicados P y Q.

El **objetivo** es calcular $Q^*(y)$

## Regla Composicional de Inferencia (RCI) de Zadeh
La conjunción de las premisas se realiza con una t-norma T. Pasando al 
final a verse así:$$MP: \mu_{Q^*}(y)=sup_{x\in X}T(\mu_{P\rightarrow Q}(x, y), \mu_{P^*}(x))$$
