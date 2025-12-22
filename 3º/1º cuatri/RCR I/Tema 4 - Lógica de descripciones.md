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
## Inferencia en lógicas de descripciones
## ALC como lógica de primer orden (LPO)
## Extensiones de ALC