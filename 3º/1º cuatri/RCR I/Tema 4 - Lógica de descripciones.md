## Introducción y fundamentos
Es una familia de formalismos de representación del conocimiento basados en lógica. Su objetivo principal es describir un dominio en términos de:
- **Conceptos (Clases)**: Colecciones de objetos con características comunes (*ej: curso, profesor, universidad*) 
- **Roles (Relaciones/Propiedades)**: Vinculos binarios entre individuos (*ej: imparteCurso, asisteACurso*)
- **Individuos**: Instancias concretas ($ej: Luis, Ana, Aula006$)
Los lenguajes específicos de DL se distinguen por el conjunto de constructores que permiten formar conceptos y roles complejos, y por el conjunto de axiomas que permiten añadir hechos sobre estos elementos.

**Relación con la Web Semántica:** Son la base lógica de OWL (Web Ontology Language), una recomendación del W3C usada para describir ontologías
## ALC: Una lógica de descripciones básica
### Sintaxis de ALC
La sintaxis se construye a partir de un conjunto de **nombres de conceptos ($C$)** y un conjunto disjunto de **nombres de roles ($R$)**.

| Tipo de concepto            | Notación            | Lógica de predicados                    | Descripción / Significado                                                        |
| --------------------------- | ------------------- | --------------------------------------- | -------------------------------------------------------------------------------- |
| **Concepto Atómico**        | $A$                 | $A(x)$                                  | Un nombre de concepto                                                            |
| **Concepto Universal**      | $\top o \gt$        | Cierto (True)                           | La superclase de todas las clases                                                |
| **Concepto Nulo**           | $\perp o \space ?$  | Falso (False)                           | La subclase de todas las clases                                                  |
| **Negación**                | $\neg C$            | $\neg \phi_x(C)$                        | Conceptos que no pertenecen a C                                                  |
| **Conjunción**              | $C \cup D$          | $\phi_x(C)\wedge\phi_x(D)$              | Elementos que son a la vez C y D                                                 |
| **Disyunción**              | $C \cap D$          | $\phi_x(C)\vee\phi_x(D)$                | Elementos que son C o D (o ambos)                                                |
| **Restricción Existencial** | $\exists r.C(9r.C)$ | $\exists y(r(x,y)\wedge\phi_y(C))$      | Elementos que están relacionados por el rol r con al menos un elemento de tipo C |
| **Restricción de Valores**  | $\forall r.C(8r.C)$ | $\forall y(r(x,y)\rightarrow\phi_y(C))$ | Elementos donde todos aquellos relacionados por el rol r deben ser de tipo C     |
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
## Bases de conocimiento ALC
Una base de conocimiento (BC) en ALC, $K$, se divide normalmente en dos partes: $\langle T,A\rangle$  
### TBox (Terminological Knowledge Base)
Contiene los axiomas que describen la estructura del dominio y las relaciones entre conceptos.
- **Axiomas de inclusión** $C \subseteq D / C \vee D$: Satisface si la interpretación del concepto $C$ es un subconjunto de la interpretación de $D (C^I \subseteq D^I)$. Esto se traduce en LPO como una implicación universal: $\forall x(\phi_x(C)\rightarrow\phi_x(D))$ 
- **Axiomas de equivalencia ($C  \equiv D / C \space º \space D$)**: Se satisface si $C^I=D^I$. Si el concepto $C$ es atómico, este axioma se llama **Definición.** Esto se traduce en LPO como una doble implicación universal: $\forall x(\phi_x(C)\leftrightarrow\phi_x(D))$
### ABox (Assertional Knowledge Base)
Describe una situación concreta mediante hechos sobre individuos.
- **Asertos de conceptos ($C(a)$)**: Afirma que el individuo $a$ pertenece al concepto $C (a^I \in C^I)$. Se traduce a LPO como $\phi_x(C)$ con la variable $x$ reemplazada por la constante $a$.
- **Asertos de roles $r(a, b)$:** Afirma que el individuo $a$ está relacionado con el individuo $b$ a través del rol $r(\langle a,b\rangle\in r^I)$
Un modelo de $I$ debe satisfacer todos los axiomas de $T$ y $A$ 
## Inferencia en lógicas de descripciones
El objetivo de la inferencia es responder automáticamente a consultas y extraer conocimiento implícito de la Base de Conocimiento $K=\langle T,A\rangle$.

Los principales mecanismos de conocimiento:

| Mecanismo            | Consulta/Definición                          | Objetivo                                                                                                                                                                                                                                             |
| -------------------- | -------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Satisfacibilidad** | ¿Es $C$ satisfacible?                        | Determinar si existe un modelo de $I$ de $T$ tal que la interpretación de $C$ no sea vacía $(C^I\neq \emptyset)$. Si un concepto es insatisfacible (ej: A \cup \neg A), indica un error de modelado.                                                 |
| **Subsunción**       | ¿Es $C$ subsumido por $D(C\subseteq_r D)$?   | Comprobar si $C^I \subseteq D^I$ para cada modelo $I$ de $T$. Es la base para la **Clasificación de la TBox** (obtener la jerarquía de subsunción)                                                                                                   |
| **Equivalencia**     | ¿Son $C$ y $D$ equivalentes $(C\equiv_r D)$? | Se verifica si $C^I = D^I$ para cada modelo $I$ de $T$                                                                                                                                                                                               |
| **Disyunción**       | ¿Son $C$ y $D$ disjuntos?                    | Se verifica si $C \cup D \equiv \space \perp$ o$C\subseteq_r \neg D$. Esto significa que $C^I \cap D^I = \emptyset$ para cada modelo $I$ de $T$                                                                                                      |
| **Consistencia**     | ¿Es $K$ consistente?                         | Determinar si existe algún modelo de $K$                                                                                                                                                                                                             |
| **Instancia**        | ¿Es $a$ instancia de $C$?                    | Comprobar si $a^I\in C^I$ para cada modelo $I$ de $T$. Usado para la **Recuperación de Instancias** (obtener todos los individuos $a$ que son instancia de $C$) y la **Realización** (encontrar todos los conceptos $C$ de los que $a$ es instancia) |

## ALC como lógica de primer orden (LPO)
Es una fragmentación de LPO. Puede ser interpretada y traducida directamente a esta.
- Los nombres de conceptos se interpretan como **predicados unarios**
- Los nombres de roles se interpretan como **predicados binarios**
- Los conceptos se traducen a fórmulas con una variable $x$libre
**Ejemplo de Traducción de Equivalencia:** La equivalencia $Empleado≡Persona∪∃trabajaPara.Empresa$ se traduce a LPO como: $$∀x(Empleado(x)↔(Persona(x)∧∃y(trabajaPara(x,y)∧Empresa(y))))$$
## Extensiones de ALC
Existen diversas extensiones de ALC que aumentan su expresividad
1. **Roles Inversos (**I**): ALCI**
 - Permite usar r− (rol inverso)
 - Semántica: (r−)I={⟨y,x⟩∣⟨x,y⟩∈rI}
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
