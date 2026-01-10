## 1. ¿Por qué necesitamos otra lógica?

La Lógica Clásica (la de toda la vida) es binaria y estática: una frase es Verdadera o Falsa en el mundo real. Punto.

Pero en el razonamiento humano usamos matices que la lógica clásica no captura bien:

- **Necesidad:** "Es _necesario_ que $2+2=4$" (No podría ser de otra forma).
    
- **Posibilidad:** "Es _posible_ que llueva mañana" (Podría pasar o no).
    
- **Tiempo:** "Será verdad en el futuro".
    
- **Conocimiento:** "El agente A _sabe_ que P".
    

La **Lógica Modal** extiende la clásica añadiendo operadores para expresar estos "modos" de verdad.

---

## 2. Sintaxis: Los Nuevos Símbolos

A los símbolos de siempre ($\wedge, \vee, \neg, \rightarrow$) añadimos dos operadores modales principales:

1. **$\square$ (Box / Cuadrado):** Indica **Necesidad**.
    
    - Se lee: _"Es necesario que..."_ o _"Obligatoriamente..."_
        
2. **$\Diamond$ (Diamond / Rombo):** Indica **Posibilidad**.
    
    - Se lee: _"Es posible que..."_
        

### Dualidad (La relación entre ellos)

Al igual que $\forall$ y $\exists$ están conectados, $\square$ y $\Diamond$ son duales. Se pueden definir uno en función del otro:

- **$\square \phi \equiv \neg \Diamond \neg \phi$**
    
    - _Traducción:_ "Es necesario" = "No es posible que no ocurra".
        
- **$\Diamond \phi \equiv \neg \square \neg \phi$**
    
    - _Traducción:_ "Es posible" = "No es necesario que no ocurra".
        

---

## 3. Semántica: Los Mundos Posibles (Semántica de Kripke)

Aquí está la clave para entender este tema. Para evaluar si algo es "necesario" o "posible", no nos basta con mirar el mundo real. Tenemos que imaginar **escenarios alternativos**.

Un **Modelo de Kripke** ($M$) se define como una tupla $<W, R, V>$:

1. **$W$ (Mundos):** Un conjunto de mundos posibles ($w_1, w_2, \dots$).
2. **$R$ (Relación de Accesibilidad):** Flechas que conectan mundos.
    - Si hay una flecha de $w_1 \to w_2$ (escrito $w_1 R w_2$), significa que desde el mundo 1 **podemos ver** o acceder al mundo 2.
    - _Esto es vital:_ Lo que es "posible" o "necesario" depende de a qué mundos puedes llegar.
3. **$V$ (Valuación):** Dice qué fórmulas son verdaderas en cada mundo concreto (ej: en $w_1$ llueve, en $w_2$ hace sol).

### ¿Cuándo es verdad una fórmula modal?

Evaluamos la verdad **dentro de un mundo $w$**:

- **$\square \phi$ es VERDAD en $w$ si:**
    - $\phi$ es verdad en **TODOS** los mundos accesibles desde $w$.
    - _(Si no ves ningún mundo, $\square \phi$ es verdad por defecto)._
- **$\Diamond \phi$ es VERDAD en $w$ si:**
    - $\phi$ es verdad en **AL MENOS UN** mundo accesible desde $w$.

---

## 4. Sistemas Axiomáticos y Propiedades de $R$

No todas las lógicas modales son iguales. Dependiendo de cómo sean las "flechas" ($R$) entre los mundos, tendremos diferentes reglas lógicas. Esto da lugar a los **Sistemas Modales** ($K, T, D, S4, S5$).

El sistema básico se llama **K** (por Kripke). Si añadimos propiedades a la relación $R$, obtenemos sistemas más potentes:

| **Sistema** | **Axioma Característico**                                  | **Propiedad de R requerida** | **Significado Humano**                                                                          |
| ----------- | ---------------------------------------------------------- | ---------------------------- | ----------------------------------------------------------------------------------------------- |
| **K**       | $\square(\phi \to \psi) \to (\square\phi \to \square\psi)$ | Cualquiera                   | Distribución básica (Lógica mínima).                                                            |
| **D**       | **(D)** $\square \phi \to \Diamond \phi$                   | **Serial**                   | "Si es obligatorio, es posible". (No hay callejones sin salida, siempre ves al menos un mundo). |
| **T**       | **(T)** $\square \phi \to \phi$                            | **Reflexiva**                | "Si es necesario, entonces es verdad aquí". (Lo necesario ocurre en la realidad).               |
| **S4**      | **(4)** $\square \phi \to \square \square \phi$            | **Transitiva**               | "Si es necesario, es necesario que sea necesario". (Introspección positiva).                    |
| **B**       | **(B)** $\phi \to \square \Diamond \phi$                   | **Simétrica**                | "Si es verdad, es necesario que sea posible". (Los caminos son de ida y vuelta).                |
| **S5**      | **(5)** $\Diamond \phi \to \square \Diamond \phi$          | **Euclídea** (+Refl+Trans)   | "Si es posible, es necesario que sea posible". (Todos los mundos están conectados entre sí).    |

> **Nota de Examen:**
> - **Reflexiva:** Todo mundo se ve a sí mismo ($w R w$).
> - **Transitiva:** Si $w_1 \to w_2$ y $w_2 \to w_3$, entonces $w_1 \to w_3$.   
> - **Simétrica:** Si $w_1 \to w_2$, entonces $w_2 \to w_1$.  
> - **Serial:** Desde todo mundo sale al menos una flecha.


---

## 5. El Método de Tableaux (Razonamiento)

Para demostrar si una fórmula es válida, usamos árboles semánticos (Tableaux), igual que en lógica clásica, pero con reglas nuevas para $\square$ y $\Diamond$.

**Reglas clave:**
1. **Regla $\Diamond$ (Posibilidad): Crea un mundo nuevo.**
    - Si tienes $\Diamond A$ en el mundo $w_i$, creas un nuevo mundo $w_j$ y pones $A$ en él.
2. **Regla $\square$ (Necesidad): Propaga a mundos existentes.**
    - Si tienes $\square A$ en $w_i$, tienes que copiar $A$ en **todos** los mundos $w_j$ que ya sean accesibles desde $w_i$.

**Procedimiento:**
1. Niegas la fórmula que quieres probar.
2. Desarrollas el árbol aplicando reglas.
3. Si todas las ramas se cierran (contradicción en todas partes), la fórmula original era válida.