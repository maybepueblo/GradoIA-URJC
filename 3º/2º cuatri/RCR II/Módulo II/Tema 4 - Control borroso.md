# Sistemas de inferencia borrosos

![[Pasted image 20260626233839.png]]

Partimos de este sistema originalmente, veamos sus procesos:
- **Borrosificación:** Convertir valor nítido en un conjunto borroso
- ![[Pasted image 20260626233924.png]]
- **Desborrosificación**: Obtener un valor nítido a partir de un conjunto borroso
	- Métodos más habituales:
		- Centro de gravedad -> $cg = \frac{\int xf(x)dx}{\int f(x)dx}$
		- Media de máximo
	- **Cálculo del centro de gravedad**
		- Algunas figuras geométricas conocidas
			- Rectángulo -> punto medio
			- Triángulo rectángulo -> a 1/3 del cateto
		- Se puede hacer por partes
			- Dividimos el área de la figura en $i$ partes -> $cg = \frac{\sum_i cg_i · A_i}{\sum_i A_i}$
- Dado un conjunto de reglas y hechos, aplicamos la RCI a las reglas. 
- Si hay varias reglas cuya conclusión se proyecta sobre la misma variable ($q_1(y), q_2(y), ..., q_n(y)$), aplicamos una función S de **agregación** (S suele ser una t-conorma), obteniendo $Q(y)=S(q_1(y), q_2(y), ..., q_n(y))$ 
- Una vez obtenido el conjunto borroso resultado $\mu_{Q^*}(x)$ podemos obtener:
	- un **valor cualitativo**
		- algún criterio de proximidad
	- un **valor numérico**
		- centro de gravedad
## Valor cualitativo
Si $y$ toma valores en $\{Q_1, Q_2, ..., Q_n\}$, aquella cualificación $y=Q_i$ tal que $\mu_{Qi}(x) \geq \mu_{Q^* }(x)$ será aceptable
- En caso de que no haya ningún $Q_i$ que lo cumpla, se usa algún criterio de proximidad.
	- Ejemplo de función de distancia:
		- $d = \sqrt{\alpha (A_i-A)² + \beta (cg_i - cg)^2)}$  con $\alpha + \beta = 1$ 
	- Sean $A, A_i$ áreas de las distribuciones de posibilidad y $cg, cg_i$ centros de gravedad del valor cualitativo $i$. 
## Base de conocimiento
Formada por reglas de forma:
$$
\begin{align}
R_1: Si \space x = A_1(x) \wedge y=A_2(y) \wedge...\rightarrow z=Q(z) \\
R_2: Si \space x = A'_1(x) \wedge y=A'_2(y) \wedge...\rightarrow z=Q'(z) \\
R_3: Si \space x = A''_1(x) \wedge y=A''_2(y) \wedge...\rightarrow z=Q''(z)
\end{align}
$$
- Buscamos obtener el conjunto borroso para la variable $z$ 
- Nota: las reglas también pueden incluir el conectivo $\vee$ 
## Motor de inferencia borroso
Aplica Modus Ponens

$$
\begin{array}{l}
x = A_1(x) \land y = A_2(y) \rightarrow z = Q(z) \\
x = B_1(x) \land y = B_2(y) \\
\hline
\hspace{6cm} {z = Q^*}
\end{array}
$$

- Los valores de entrada ($B_1(x)$ y $B_2(y)$) pueden ser nítidos o borrosos.
- Recordamos que $\mu_{Q^*}(y)=max_{x\in X}T(\mu_{P^*}(x), \mu_{P\rightarrow Q}(x, y))$ tenemos que $\mu_{Q^*}(z)=max_{x, y}T(B_1(x)\wedge B_2(y), A_1(x)\wedge A_2(y)\rightarrow Q(z))$ 
- Según la t-norma e implicación que usemos la respuesta puede ser más o menos intuitiva
### **Método de Mamdani**
* Implicación y t-norma = Min, t-conorma = Máx $$ \begin{aligned} \mu_{Q^*}(z) &= \max_{x,y} T(B_1(x) \land B_2(y), A_1(x) \land A_2(y) \rightarrow Q(z)) \\ \mu_{Q^*}(z) &= \max_{x,y} \min[\min[B_1(x),B_2(y)], \min[\min(A_1(x),A_2(y)), Q(z)]] \\ \mu_{Q^*}(z) &= \min(\text{NA}, Q(z)), \end{aligned} $$ siendo $\text{NA} = \min(\text{NA1}, \text{NA2}) \quad (\max(\text{NA1}, \text{NA2}) \text{ si el conectivo es } \lor)$ $$ \text{NA1} = \max_x [\min(B_1(x), A_1(x))] \qquad \text{NA2} = \max_y [\min(B_2(y), A_2(y))] $$
![[Pasted image 20260627000340.png]]

Si hay varias reglas, combinamos mediante una t-conorma, en este caso $S=Max$ 
### Procedimiento general de inferencia
- Se tienen m reglas y datos $x=B_1(x), y=B_2(y), ...$
- Para **cada regla**
	- Se calcula el nivel de ajuste $NA_i$
	- Se obtiene $\mu_{Qi^*}(z)=min(NA_i, Q_i(z))$
- **Agregamos** los resultados
	- $\mu_{Q^*}(z)=\cup\mu_{Q_i^*}(z)$ -> t-conorma = Max
- Se **desborrosifica:** transformamos $\mu_{Q^*}(z)$ en un valor numérico
	- Centro de gravedad
	- Media de los z con posibilidad máxima
# Controladores borrosos
## Descripción
- El **control de un sistema** S:
	- Garantiza una determinada respuesta en la salida de S próxima a un valor de referencia a pesar del medio en que opera S
- Control **clásico**:
	- Modelización matemática mediante sistemas de ecuaciones diferenciales a menudo no lineales
- Control **borroso**:
	- Una de las apps más importantes y exitosas
	- Alternativa al control clásico cuando:
		- no es posible encontrar una descripción matemática precisa
		- o resulta demasiado compleja
## Esquema

![[Pasted image 20260627000951.png]]
## Motor de inferencia borroso
El control se formula mediante una BC formada por reglas que relacionan las variables de estado del proceso con la variable de control de la forma:
$$
\begin{align}
R_1: Si \space x = A_1(x) \wedge y=A_2(y) \wedge...\rightarrow z=Q(z) \\
R_2: Si \space x = A'_1(x) \wedge y=A'_2(y) \wedge...\rightarrow z=Q'(z) \\
R_3: Si \space x = A''_1(x) \wedge y=A''_2(y) \wedge...\rightarrow z=Q''(z)
\end{align}
$$
El objetivo es, considerando las reglas y usando un motor de inferencia, enviar en cada instante info al sistema sobre las acciones de control.
## Controlador borroso
Las $A_i^k, Q^k$ son etiquetas cualitativas con dominio similar a <NA, NM, NP, Z, PP, PM, PA> siendo NA (negativo alto), NM (negativo medio), NP (negativo pequeño), Z (nulo), PP (positivo pequeño), PM, PA.

Un ejemplo de posible variable lingüística es:

![[Pasted image 20260627001248.png]]