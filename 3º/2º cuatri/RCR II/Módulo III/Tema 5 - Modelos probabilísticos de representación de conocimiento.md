# Redes Bayesianas
## Introducción
Son herramientas para comprender y resolver problemas relacionados con **sucesos inciertos**. Se conocen como redes de Bayes, redes de creencias, redes de decisión o modelos bayesianos.

Son **gráficos probabilísticos** que se pueden usar para construir modelos de datos a partir de datos/opiniones de expertos. 
- Amplia gama de tareas.
- Específicamente usados para actividades de análisis.

Las redes bayesianas podemos graficarlas, si bien opcional, nos ayuda a entenderlas.
- Cada **nodo representa una variable** -> *discreta* o *continua* 
- Los **enlaces** se usan para **indicar que un nodo influye directamente en el otro**
- Cuando **no existe** un enlace entre dos nodos **no significa** que sean **completamente independientes**, pueden estar conectados a través de otros nodos. 
- No obstante, pueden volverse (in)dependientes en función de la evidencia en otros nodos.
## Representación del conocimiento
- **Modelo Judea Pearl**
	- Modelos causales formados por **nodo concepto y relaciones** entre ellos, definidas por una red.
	- Las **relaciones son de influencia** y se les asocia **medida de probabilidad** que condiciona los aspectos causa y efecto.
	- Manejando adecuadamente la estructura podemos **generar explicaciones** de las conclusiones.
	- Se consideran **grafos sin ciclos** (**poliárboles**)
	- Existen modelos para grafos con ciclos.

![[Pasted image 20260621222634.png]]

Está formada por un **conjunto de nodos** $X_i$ con valores en **dominios finitos** $D_i$.
- *Ejemplo* -> el concepto Edad toma valores en dominio <niño, joven, adulto, viejo>
- Notación: P(X=x | Y=y) = P(x|y) = 0.3

![[Pasted image 20260621222937.png]]

Decimos que los nodos se relacionan mediante **arcos**. El significado es:
- Los valores de X están condicionados por los valores de Y
- Los valores de Y están condicionados por los valores de Z
- La influencia de Z sobre X depende exclusivamente de Y.
Esto es lo que llamamos **Separabilidad Direccional**

Si en un grafo acíclico el nodo Y separa al nodo X del conjunto de nodos $W_1, W_2, ..., W_n$, podemos escribir:$$P(x|y, w_1, w_2, ..., w_n)=P(x|y)$$
Lo cual es un **principio de descomposición de las influencias** en la red y **no un principio de relación de consecuencia lógica**

Tenemos ahora las matrices de probabilidad condicional, ob
tenibles de expertos o estadísticas

![[Pasted image 20260621223232.png]]

X se relaciona con $C_1, C_2, ..., C_n$ de forma que se satisface la tabla de probabilidad.
### Modelo de razonamiento
- Dados:
	- BC con estructura de relaciones entre conceptos y el conjunto de matrices de probabilidad asociada a las relaciones.
	- Hipótesis de probabilidades de valores conocidos en unos nodos borde. 
- Evaluamos:
	- La probabilidad de los nodos de la red que sean consistentes con estos datos.
- Tipo de razonamiento
	- **Predictivo**: Causas -> Efectos
	- **Diagnóstico**: Efectos -> Causas
	- **Intercausal**: Causas <--> Efectos
### Repaso breve
$$P(A|B)=\frac{P(A, B)}{P(B)}$$
Teorema de Bayes:$$P(A|B)=\frac{P(B|A) · P(A)}{P(B)}$$pudiendo A y B ser multivaluadas.

Luego:
$$\begin{align}P(A|B)=\frac{P(B|A) · P(A)}{P(B)}\\P(\neg A|B)=\frac{P(B|\neg A) · P(\neg A)}{P(B)}\end{align}$$
como $P(A|B) + P(\neg A|B) =1$ entonces:$$P(B)=P(B|A)·P(A)+P(B|\neg A)·P(\neg A)$$y$$P(A|B)=\frac{P(B|A)·P(A)}{P(B|A)·P(A)+P(B|\neg A)·P(\neg A)}$$
Si generalizamos:
$$P(A_k|B)=\frac{P(B|A_k)·P(A_k)}{\sum_iP(B|A_i)·P(A_i)}$$
Como $\sum_iP(A_i|B)=1$ la ecuación anterior se puede escribir como:
$$P(A|B)=\alpha P(B|A)·P(A)$$
siendo $\alpha$ una constante de normalización.

![[Pasted image 20260621224541.png]]
## Inferencia

![[Pasted image 20260621224707.png]]

Para el mecanismo de inferencia nos basamos en descomponer la credibilidad asociada a un nodo P(x|e) en base a la teoría bayesiana y la hipótesis de separabilidad direccional.
- x divide e en dos partes:
	- $e_x^+$ evidencia sobre las causas de X
	- $e_x^-$ evidencia sobre los efectos de X

Podemos decir entonces:
$$P(x \mid e) = P(x \mid e_x^-, e_x^+) = \frac{P(e_x^- \mid x, e_x^+) \cdot P(x \mid e_x^+)}{P(e_x^- \mid e_x^+)}$$ por separabilidad direccional $$P(x \mid e) = P(x \mid e_x^-, e_x^+) = \frac{P(e_x^- \mid x) \cdot P(x \mid e_x^+)}{P(e_x^- \mid e_x^+)}$$ donde $$\frac{1}{P(e_x^- \mid e_x^+)}$$ puede considerarse un operador $\alpha$ de normalización $$\lambda(x) = P(e_x^- \mid x) \quad \quad \quad \pi(x) = P(x \mid e_x^+)$$ **Credibilidad** $$Cr(x) = P(x \mid e) = \alpha \cdot \pi(x) \cdot \lambda(x)$$

---

Por otra parte, $\quad \pi(x) = P(x \mid e_x^+) = P(x \mid e_{u_1x}^+, e_{u_2x}^+, \dots, e_{u_nx}^+)$

condicionando sobre $u_1, u_2, \dots, u_n$

$$\pi(x) = P(x \mid e_x^+) = \sum_{u_1 \dots u_n} P(x \mid u_1 \dots u_n) \cdot P(u_1 \dots u_n \mid e_{u_1x}^+, e_{u_2x}^+, \dots, e_{u_nx}^+)$$

teniendo en cuenta que $x$ separa cada $u_i$ del resto

$$P(u_1 \dots u_n \mid e_{u_1x}^+, e_{u_2x}^+, \dots, e_{u_nx}^+) = P(u_1 \mid e_{u_1x}^+) \cdot P(u_2 \mid e_{u_2x}^+) \cdot \dots \cdot P(u_n \mid e_{u_nx}^+)$$

quedando 

$$\pi(x) = \sum_{u_1 \dots u_n} P(x \mid u_1 \dots u_n) \cdot \prod_i \pi_x(u_i)$$

siendo 

$$\pi_x(u_i) = P(u_i \mid e_{u_ix}^+)$$

---

Queda calcular $\lambda_{y_j}(x)$ y $\pi_x(u_i)$ en función de sus nodos vecinos

Desde el punto de vista de x

$$\pi_{y_j}(x) = P(x \mid e_{xy_j}^+) = P(x \mid e - e_{xy_j}^-)$$

$$\pi_{y_j}(x) = Cr_{e - e_{xy_j}^-}(x) = \alpha \cdot \pi(x) \cdot \prod_{k \neq j} \lambda_{y_k}(x)$$

De forma análoga, $\quad \quad \lambda_x(u_i) = P(e_{u_ix}^- \mid u_i)$

condicionando a x y el resto de $u_j$ + separación direccional + bayes + independencia

$$\lambda_x(u_i) = \beta \cdot \sum_x \lambda(x) \cdot \sum_{u_k, k \neq i} P(x \mid u_1 \dots u_k \dots u_n) \cdot \prod_{k \neq i} \pi_x(u_k)$$
### Fórmulas
Después de esta elaboración quedamos con las siguientes fórmulas:
**Creencia** -> $Cr(x)=\alpha·\pi(x)·\lambda(x)$
- La creencia final sobre ti mismo. Lo que tus genes/padres $(\pi(x))$ multiplicado por el feedback de cómo se están comportando tus hijos en el mundo real $(\lambda(x))$
**Información que recibe** -> $\lambda(x)=\prod_j \lambda_{y_j}(x)$
- Si tienes varios hijos ($y_j$) cada uno te da su propia opinión independiente sobre ti ($\lambda_{y_j}(x)$). Para saber el feedback total que recibes de tu descendencia, simplemente multiplicas/combinas los reportes independientes de cada uno de tus hijos.
**Información que envía** -> $\pi(x)=\sum_{u_1...u_n}P(x|u_1...u_i...u_n)\prod_i\pi_x(u_i)$
- Lo que heredas. Para saber que esperamos de ti mismo basado en tus ancestros, tienes que saber lo que cada uno de tus padres te dice $(\pi_x(u_i))$. Esto lo combinamos con las reglas de la genética familiar (tabla de probabilidad condicional $P(x|u_1...u_n)$) considerando todas las combinaciones posibles de cómo podrían estar tus padres.
**Información que le envías a tus hijos** -> $\pi_{y_j}(x)=\alpha·\pi(x)·\prod_{k\neq j}\lambda_{y_k}(x)$
- Le cuentas lo que tus padres te enseñaron más el feedback recibido de todos tus otros hijos salvo el propio hijo $y_j$. 
**Información que envías a uno de tus padres** -> $\lambda_x(u_i)=\beta·\sum_x\lambda(x)\sum_{u_k,k\neq i}P(x|u_1...u_i...u_n)\prod_{k\neq i}\pi_x(u_k)$ 
- Ahora te toca decirle a tu padre $u_i$ cómo te va. Tu reporte se basa en la evidencia que te dan tus propios hijos combinada con la información que estás recibiendo de tus otros padres donde no puede ser el padre al que le envías. Usas las reglas de familia para traducir todo esto en un mensaje que tu padre pueda entender. Beta es una constante para cuadrar las posibilidades al 100%

La **constante de normalización** se calcula en base de los resultados crudos. Siendo la inversa de esa suma total$$\alpha=\frac{1}{SumaTotal}$$
## Observaciones prácticas
- Valores $\pi$ sólo van de causa a efecto (hacia abajo)
- Valores $\lambda$ sólo van de efecto a causa (hacia arriba)
- Un valor que sale de un nodo ($\pi$ o $\lambda$) depende de todos los valores que entran a ese nodo por el resto de arcos (no por el mismo arco)
# MYCIN
## Introducción
Sistema experto basado en reglas para toma de decisiones. Usado para diagnóstico y tratamiento. Se realiza mediante preguntas acerca de los síntomas del paciente.

Teniendo la lista de posibles enfermedades, las ordenaba de acuerdo con la gravedad y la probabilidad de tener al paciente infectado con cada una. Podía luego recomendarte el tratamiento.

Tres partes interrelacionales en MYCIN:
- Sistema de consulta
	- BC para generar recomendación terapéutica
- Sistema de explicaciones
	- Describe razonamiento realizado durante consulta y las conclusiones
- Sistema de adquisición de conocimiento
	- Permite a los expertos actualizar el conocimiento sin saber de programación.
## Representación del conocimiento
Usamos **fórmulación proposicional** para representar declaraciones.

El objetivo es acercarnos a la capacidad de representación de la lógica de predicados, pero sin su complejidad.

La idea principal es plantear declaraciones formuladas en base a tripletas concepto-atributo-valor para representar propiedades específicas de un concepto en un dominio determinado de valores (por ejemplo paciente.fiebre = alta)

Formulamos reglas con estructura:
$$c_i.a_j=v_k,...,c_h.a_r=v_d\rightarrow_gc_l.a_s=v_m$$
Los elementos en la bc siendo las reglas que contienen las tripletas $c.a.v$ que modelan el problema. En base a estas se construyen los árboles mediante el encadenamiento de las reglas. 

Se construyen mediante el siguiente proceso los árboles:
- Se buscan reglas cuyas conclusiones estén relacionadas con el objetivo.
- Se repite la búsqueda de regla anterior, pero teniendo en cuenta que la conclusión esté relacionada con cada premisa. Este paso se repite mientras existan reglas que concluyan sobre alguna premisa  o las premisas son datos conocidos o se pueden averiguar preguntando al usuario.

![[Pasted image 20260621231257.png]]

A diferencia de los sistemas basados en reglas tradicionales, MYCIN usa **grados de certeza sobre la evidencia y las reglas.**
- En un principio usábamos probabilidades estimadas a partir de las frecuencias estadísticas y en caso de no disponer de la info estadística, había juicio subjetivo.
- Se optó mejor por el **Factor de Certeza (FC)** que se expresa a partir de **Medida de Credibilidad (MC)** y **Medida de Incredibilidad (MI)**

* **$MC$ (Medida de Credibilidad)**

$$MC(h, e) = \begin{cases} 
\quad 1 & \text{si } p(h) = 1 \\ 
\frac{\max(p(h|e), p(h)) - p(h)}{1 - p(h)} & \text{en otro caso} 
\end{cases}$$

* **$MI$ (Medida de Incredibilidad)**

$$MI(h, e) = \begin{cases} 
\quad 1 & \text{si } p(h) = 0 \\ 
\frac{\min(p(h|e), p(h)) - p(h)}{0 - p(h)} & \text{en otro caso} 
\end{cases}$$

* **$FC$ (Factor de Certeza)**

$$FC(h, e) = MC(h, e) - MI(h, e)$$
### Factor de certeza
$FC(h)$ -> Es un valor entre -1 y +1 que indica el grado de creencia en una hipótesis $h$ (+1: totalmente seguro, -1: totalmente seguro que falso)
$FC(h, e)$ -> factor de certeza de $h$ basado en la evidencia $e$
$FC(\neg h, e) = -FC(h, e)$ es decir $FC(h, e) + FC(\neg h, e) = 0$
*Ejemplo
- h1 = el organismo es gram-negativo
- h2 = el organismo tiene forma de bastón
- h3 = el organismo es anaerobio
- FC(h1, E) = +0.8: evidencia fuerte de que es gram-negativo
- FC(h2, E) = -0.3: ligera evidencia que no tiene forma de bastón
- FC(h3, E) = +1: se sabe con seguridad que es anaerobio.

Luego...
- **Reglas**: evidencia -> hipótesis $(e \rightarrow h)$
- **$e$ es una fórmula lógica $(\wedge, \vee)$**
- $FC(h, e)$: expresa el grado en que se puede o no confirmar la conclusión $h$ supuesta la evidencia de las premisas $e$.
- Ejemplo
	- Si el organismo es gram-negativo Y tiene forma de bastón Y es anaerobio ENTONCES [hay una evidencia media de que] el organismo es bacteroide (con certeza de 0.6)
- Los grados de certeza se obtienen de:
	- expertos
	- estadísticas (si hay datos)
## Inferencia
Para hacer este proceso, necesitamos **añadir algunos criterios** para propagar la evidencia en el árbol de reglas.
- La propagación se hace desde **abajo hacia arriba**
- Específicamente, se divide en dos partes:
	- **Propagación vertical** de la evidencia desde las premisas hasta la conclusión de la regla, teniendo en cuenta los FC de ambas.
		- **Obtención del FC de las premisas** $FC(e)$ depende de si se trata de conjunciones o disyunciones de las premisas:
			- $FC(A\vee B)=max(FC(A), FC(B))$
			- $FC(A\wedge B)=min(FC(A), FC(B))$
		- **Obtención del FC de la conclusión** $FC(h)$ usando el FC de la regla $FC(h, e)$:
			- $FC(h)=FC(e)·FC(h, e)$ si $FC(e) > 0$, 0 e. o. c
		- Mecanismo simple que trata de hacer una aproximación a la lógica proposicional donde las funciones max y min devuelven los valores 0 y 1 en los límites.
	- **Acumulación horizontal** de la evidencia que converge sobre una misma conclusión procedente de varias reglas (algunas confirmantes y otras desconfirmantes)
		- Se aplica cuando varias reglas inciden sobre la misma hipótesis.
			- Se agrupan los FC positivos por un lado, negativos por otro.
			- Sólo una vez se combinan ambas
			- Se usa el siguiente cálculo dependiendo si los FC son del mismo signo o no:
				- $$FC = \begin{cases} FC1 + FC2 - |FC1| * FC2 & \color{red}{\text{si } FC1 * FC2 > 0 \text{ (mismo signo)}} \\ \frac{FC1 + FC2}{1 - \min(|FC1|, |FC2|)} & \color{red}{\text{en cualquier otro caso}} \end{cases}$$
## Ventajas y desventajas


| **Ventajas**                                                            | **Desventajas**                                |
| ----------------------------------------------------------------------- | ---------------------------------------------- |
| Modelo muy intuitivo                                                    | Inconsistencias en el conocimiento del experto |
| Fácil computación                                                       | No considera relaciones entre premisas         |
| Facilidad para obtener las medidas de certeza (expertos o estadísticas) | No considera relaciones entre conclusiones     |
