## Qué es y pa qué sirve
Después de ver [[Tema 3 - Lógica]], tenemos una lógica potente pero compleja y lenta para web. Necesitamos algo ligero, especializado en **definir y clasificar conceptos**.

Las **Lógicas de Descripciones (DL)** son una familia de lenguajes lógicos diseñados para representar código estructurado.
- **Objetivo** Describir un dominio usando tres elementos básicos.
- **Uso** Son la base teórica del estándar **OWL**, véase [[Tema 5 - OWL]].

**Los 3 Elementos Básicos**
Es vital distinguir estos tres, porque todo se construye con ellos.
1. **Conceptos (Clases):** Grupos de cosas
	- *Ejemplos:* `Persona`, `Mujer`, `Coche`
	- *En lógica:* Conjuntos de individuos
2. **Roles (Propiedades):** Relaciones binarias entre cosas
	- *Ejemplos:* `tieneHijo`, `conduce`, `amaA`
3. **Individuos (Instancias):** Objetos concretos
	- *Ejemplos:* `Juan`, `SeatIbiza_1234`
## ALC: Una lógica de descripciones básica (Abecedario)
Hay muchas variantes de DL, pero la más importante y básica se llama ALC
### Sintaxis de ALC
La sintaxis se construye a partir de un conjunto de **nombres de conceptos ($C$)** y un conjunto disjunto de **nombres de roles ($R$)**.

|**Tipo de Constructor**|**Notación Estándar (DL)**|**Lógica de Predicados (LPO)**|**Significado Humano (Set Theory)**|
|---|---|---|---|
|**Concepto Atómico**|$A$|$A(x)$|Un concepto simple (ej: `Perro`).|
|**Concepto Universal**|$\top$ (Top)|$True$|Todo el mundo. El universo completo.|
|**Concepto Nulo**|$\perp$ (Bottom)|$False$|Nadie. El conjunto vacío.|
|**Negación**|$\neg C$|$\neg C(x)$|**Complemento:** Todo lo que NO sea C.|
|**Conjunción** (AND)|$C \sqcap D$|$C(x) \wedge D(x)$|**Intersección:** Elementos que son C **Y** D a la vez.|
|**Disyunción** (OR)|$C \sqcup D$|$C(x) \vee D(x)$|**Unión:** Elementos que son C **O** D (o ambos).|
|**Existencial** (SOME)|$\exists r.C$|$\exists y (r(x,y) \wedge C(y))$|Tiene **al menos una** relación $r$ con un $C$.|
|**Universal** (ONLY/ALL)|$\forall r.C$|$\forall y (r(x,y) \rightarrow C(y))$|**Si** tiene relaciones $r$, **todas** deben ser con $C$.|
### Semántica
Se define a través de una interpretación $I=(\Delta^I, ·^I)$ donde:
- $\Delta^I$ es el **dominio**, un conjunto no vacío
- $·^I$ es una función que asocia:
	- Cada nombre de concepto $A$ a un subconjunto $A^I \subseteq \Delta^I$.
	- Cada nombre de rol $r$ a una relación binaria $r^I\subseteq\Delta^I\times\Delta^I$.
La función $·^I$ se extiende a conceptos complejos aplicando operaciones de conjuntos:
- $T^I=\Delta^I$
- $\perp^I = \emptyset$ 
- $(\neg C)^I=\Delta^I \backslash C^I$
- $(C\cup D)^I$ (Conjunción) = $C^I \cap D^I$ equivale a $\phi_x(C)\wedge\phi_x(D)$
- $(C\cap D)^I$ (Disyunción) = $C^I \cup D^I$ equivale a $\phi_x(C)\vee\phi_x(D)$
- $(\exists r.C)^I = \{x \in \Delta^I | \exists y \in con (x,y) \in r^I \wedge y \in C^I\}$
- $(\forall r.C)^I = \{x \in \Delta^I | \forall y \in con (x,y) \in r^I entonces y \in C^I\}$
## Bases de conocimiento: TBox y ABox
En DL, dividimos el conocimiento en dos cajas ("Box"). Una base de conocimiento (BC) en ALC, $K$, se divide normalmente en dos partes: $\langle T,A\rangle$  
### TBox (Terminological Knowledge Base)
Guardamos las **definiciones** y reglas generales del mundo. No hablamos de individuos concretos (Juan), sino de conceptos (Humanos).
- **Inclusión** $C \subseteq D / C \vee D$: Satisface si la interpretación del concepto $C$ es un subconjunto de la interpretación de $D (C^I \subseteq D^I)$. Esto se traduce en LPO como una implicación universal: $\forall x(\phi_x(C)\rightarrow\phi_x(D))$. Lo que es lo mismo, "Todo A es un B (subclase)"
	- *Ejemplo:* $Estudiante \subseteq Persona$ (todo estudiante es una persona)
- **Equivalencia ($C  \equiv D / C \space º \space D$)**: Se satisface si $C^I=D^I$. Si el concepto $C$ es atómico, este axioma se llama **Definición.** Esto se traduce en LPO como una doble implicación universal: $\forall x(\phi_x(C)\leftrightarrow\phi_x(D))$. En otras palabras, "A es exactamente lo mismo que B"
	- *Ej*: $Hombre \equiv Persona \space\sqcap Masculino$ (Ser hombre es ser Persona y Masculino)   
### ABox (Assertional Knowledge Base)
Guardamos los hechos concretos sobre individuos
- **Asertos de conceptos ($C(a)$)**: Afirma que el individuo $a$ pertenece al concepto $C (a^I \in C^I)$. Se traduce a LPO como $\phi_x(C)$ con la variable $x$ reemplazada por la constante $a$.
	- Juan es un hombre -> $Hombre(Juan)$ 
- **Asertos de roles $r(a, b)$:** Afirma que el individuo $a$ está relacionado con el individuo $b$ a través del rol $r(\langle a,b\rangle\in r^I)$
	- Juan tiene hijo a Pedro -> $tieneHijo(Juan, Pedro)$ 

### Resumen
- **TBox**: "Todos los profesores son empleados" (Regla)
- **ABox:** "Juan es profesor" (Dato)
## Inferencia en lógicas de descripciones
El objetivo de la inferencia es responder automáticamente a consultas y extraer conocimiento implícito de la Base de Conocimiento $K=\langle T,A\rangle$.

Los principales mecanismos de conocimiento:

|**Mecanismo**|**Pregunta Típica**|**Objetivo y Definición Técnica**|
|---|---|---|
|**Satisfacibilidad**|¿Tiene sentido el concepto $C$?|Verificar si existe al menos un modelo donde $C$ no sea vacío ($C^{\mathcal{I}} \neq \emptyset$).<br><br>  <br><br>_Ejemplo:_ Si defines "Círculo Cuadrado" ($Circulo \sqcap Cuadrado$) y son disjuntos, el concepto es **Insatisfacible** (nadie puede serlo).|
|**Subsunción**|¿Es $C$ un tipo de $D$?<br><br>  <br><br>($C \sqsubseteq D$)|Comprobar si **todo** individuo de $C$ es necesariamente un individuo de $D$ ($C^{\mathcal{I}} \subseteq D^{\mathcal{I}}$).<br><br>  <br><br>Es la base para clasificar la jerarquía automáticamente (saber quién es hijo de quién).|
|**Equivalencia**|¿Son $C$ y $D$ lo mismo?<br><br>  <br><br>($C \equiv D$)|Verificar si $C$ subsume a $D$ y $D$ subsume a $C$.<br><br>  <br><br>Significa que siempre tienen exactamente los mismos individuos ($C^{\mathcal{I}} = D^{\mathcal{I}}$).|
|**Disyunción**|¿Son $C$ y $D$ incompatibles?|Verificar si la **intersección** de ambos es vacía ($C \sqcap D \equiv \perp$) o si $C$ es una subclase de "NO D" ($C \sqsubseteq \neg D$).<br><br>  <br><br>_Corrección:_ En tu tabla original ponía unión ($\cup$), lo cual estaba mal. Buscamos que **no tengan nada en común**.|
|**Consistencia**|¿Tiene sentido la Base de Conocimiento ($K$)?|Determinar si existe algún modelo posible que respete **todas** las reglas de la TBox y los hechos de la ABox a la vez. Si hay una contradicción (ej: Juan es Hombre y los Hombres no son Personas), $K$ es inconsistente.|
|**Instancia**|¿Es $a$ un $C$?<br><br>  <br><br>($K \models C(a)$)|Comprobar si el individuo $a$ pertenece al concepto $C$ en todos los modelos.<br><br>  <br><br>**Servicios derivados:**<br><br>  <br><br>• **Recuperación:** "Dame todos los alumnos" (Encontrar todos los $x$ tal que $Alumno(x)$).<br><br>  <br><br>• **Realización:** "Dime todo lo que es Juan" (Encontrar los conceptos más específicos a los que pertenece Juan).|

## ALC como lógica de primer orden (LPO)
Es una fragmentación de LPO. Puede ser interpretada y traducida directamente a esta.
- Los nombres de conceptos se interpretan como **predicados unarios**
- Los nombres de roles se interpretan como **predicados binarios**
- Los conceptos se traducen a fórmulas con una variable $x$ libre
**Ejemplo de Traducción de Equivalencia:** La equivalencia $Empleado≡Persona∪∃trabajaPara.Empresa$ se traduce a LPO como: $$∀x(Empleado(x)↔(Persona(x)∧∃y(trabajaPara(x,y)∧Empresa(y))))$$
## Extensiones de ALC
Existen diversas extensiones de ALC que aumentan su expresividad
1. **Roles Inversos (I**): ALCI
 - Permite usar r− (rol inverso)
 - Semántica: $(r−I)={⟨y,x⟩∣⟨x,y⟩∈rI}$
 - Ejemplo: Se puede definir Asignatura utilizando 9imparte−.Profesor
2. **Restricciones Numéricas (**Q,N**): ALCQ/ALCN**
 - Permiten establecer límites en la cantidad de individuos relacionados
 - **Cualificadas (**Q**):** Restringen la cuenta a un concepto específico C
	- (≤nr.C) y (≥nr.C)
	- Ejemplo: Persona∪(≤4 sigue.Espan˜ol) (Personas que siguen a menos de 5 españoles)
 - **No Cualificadas (**N**):** Cuentan todos los relacionados (equivalente a r.⊤)
	- (≤nr) y (≥nr)
	- Ejemplo: Persona∪(≥3 posee) (Personas que poseen tres o más cosas)
3. **Otras Extensiones Comunes**
 - **Transitividad de roles (S**): r+ (ej: _antepasado de_)
 - **Subroles (H): r1​⊆r2​**
 - **Nominales (O**): Clases "cerradas" definidas por una enumeración de individuos (ej: {a, b, c} o ColorSemaforo≡{Rojo, Ambar, Verde})

**Ejemplos de Lenguajes DLs:** ALCI (ALC con roles inversos), ALCQI (ALCI con restricción numérica cualificada), y **SHIQ** (ALCQI con transitividad de roles y subroles)
## Ejemplo Práctico de Definición
Definamos el concepto de "**Padre Feliz**". *Definición:* Un hombre que tiene algún hijo y que TODOS sus hijos son médicos o abogados.

**Traducción a DL** $$PadreFeliz \equiv Hombre \sqcap\exists tieneHijo.\top\sqcap\forall tieneHijo.(Medico\sqcup Abogado)$$
**Desglose:**
1. *Hombre:* Es un hombre
2. $\sqcap$ Y...
3. $\exists tieneHijo.\top$: Tiene al menos un hijo (de cualquier tipo $\top$). Esto evita el caso del padre sin hijos
4. $\sqcap$ Y...
5. $\forall tieneHijo.(Medico\sqcup Abogado)$ Todos los hijos que tenga (si tiene) deben ser médicos o abogados