Un SBR separa el conocimiento en **qué sabemos del problema** (hechos) y **cómo resolverlo** (reglas), y deja que un mecanismo automático razone solo. Notación del modelo: **⟨BH, BR, MI⟩**.
## 1. Descripción

### 1.1. Los tres componentes ⟨BH, BR, MI⟩

|Componente|Es|Función|
|---|---|---|
|**BH** — Base de Hechos (= _Memoria de Trabajo_)|Datos, hechos y metas. Listas de símbolos entre paréntesis: `(on A B)`.|Modela el estado del mundo. **Cambia** durante la inferencia (añadir/borrar).|
|**BR** — Base de Reglas|Conjunto de reglas `SI <premisas> ENTONCES <acciones>`.|Aporta cómo resolver.|
|**MI** — Motor de Inferencia|Mecanismo automático.|Razona con BH+BR y decide qué reglas aplicar.|

**BH — dos tipos de hechos:** **permanentes** (invariantes: `(bloque A)`) y **temporales** (cambian: `(on A B)`). Estados: inicial → intermedio → final.

**BR — reglas:**

- LHS = antecedente (premisas) · RHS = consecuente (acciones).
- **Semántica:** si _todas_ las premisas están en la BH, se ejecutan _todas_ las acciones.
- **Variables** (`?x`): ligan con la constante en la **misma posición**; mismo valor en toda la regla. **Reglas de oro:** (1) solo las reglas tienen variables, los hechos **no**; (2) toda variable del consecuente debe ligarse antes en el antecedente.

### 1.2. Motor de Inferencia: dos estrategias

- **Hacia delante** (_forward_): de la BH inicial → dispara reglas → BH final que cumple la consulta. **← la de este tema.**
- **Hacia atrás** (_backward_): del objetivo → subobjetivos → soluciones.

### 1.3. Ciclo de inferencia (forward)

Bucle de 3 pasos hasta parar:

1. **Detección (equiparación)** → halla las reglas compatibles con la BH. El **Conjunto Conflicto (CC)** = instancias aplicables aún no disparadas (puede haber varias instancias de la misma regla).
2. **Selección** → elige UNA instancia del CC según una estrategia (ver tabla).
3. **Disparo** → ejecuta el RHS, modifica la BH (añadir/borrar) → nueva BH para el siguiente ciclo (puede invalidar instancias del CC anterior).

**Parada:** CC vacío, **o** una regla ejecuta un comando de parada.

**Estrategias de selección:**

|Basadas en|Opciones|
|---|---|
|**Reglas**|prioridad explícita · prioridad implícita (orden en BR, Prolog) · refracción (historia) · especificidad (más/menos condiciones)|
|**Instancias**|más antigua = **amplitud** · más nueva = **profundidad**|
|**Objetos**|hechos más recientes · prioridad a patrones comunes|

### 1.4. Eficiencia: algoritmo RETE

**Problema:** reequiparar todas las reglas con toda la MT cada ciclo es ineficiente. **RETE:** **red de nodos** compilada al inicio que construye el CC **de forma incremental**: solo los hechos nuevos atraviesan los filtros afectados, sin reevaluar de cero. **Comparte** los nodos de premisas comunes entre reglas.

### 1.5. Diseño de BC: errores frecuentes (¡una regla NO es código procedural!)

|Antipatrón|Solución|
|---|---|
|Usar `if-then-else` (`EN CASO CONTRARIO`)|Dos reglas independientes, identificando las condiciones excluyentes.|
|`OR` en el consecuente|Dos reglas; conservar precedencia con **prioridades**.|
|Decisiones (`SI` anidado) en el consecuente|**Señalizadores** (hechos-bandera) que activen otra regla. _Borrarlos después._|
|Una regla "lanza" otra (`ENTONCES Rj`)|Igual: señalizadores que activen Rj y borrarlos al ejecutarla.|
|Hecho que debe ser único (recalcular `coste`)|Solo `añadir` deja duplicados → **borrar + añadir**. Pero eso causa **bucle infinito** → usar señalizador o **hecho nuevo** (`coste-final`).|

**Ventajas:** próxima al experto, sintaxis simple, trazable. **Inconvenientes:** conocimiento procedimental difícil de expresar; difícil verificar consistencia global.

---

## 2. CLIPS — Referencia para programar

> CLIPS (_C Language Integrated Production System_): herramienta en C/ANSI de la NASA (1986) para SBR por **encadenamiento hacia delante**. Extras: COOL (OO), FuzzyCLIPS, JESS (Java).

### 2.0. Esqueleto de un programa CLIPS

```clips
; 1) ONTOLOGÍA: plantillas de hechos no ordenados
(deftemplate persona (slot nombre) (slot edad))

; 2) CONOCIMIENTO DEL CASO: hechos iniciales
(deffacts datos
   (persona (nombre Ana) (edad 20))
   (mes enero))

; 3) CONOCIMIENTO DEL DOMINIO: reglas
(defrule mayor-de-edad
   (persona (nombre ?n) (edad ?e&:(>= ?e 18)))
=>
   (assert (adulto ?n))
   (printout t ?n " es adulto" crlf))

; 4) EJECUCIÓN en consola
; CLIPS> (reset)   → carga deffacts + initial-fact
; CLIPS> (run)     → ejecuta el ciclo de inferencia
; CLIPS> (facts)   → inspecciona la MT
```

### 2.1. Base de Hechos (Memoria de Trabajo)

|Tipo de hecho|Forma|Notas|
|---|---|---|
|**Ordenado**|`(edad 14)`, `(alumnos Pepe Juan)`|La **posición importa**; info tipada.|
|**No ordenado** (`deftemplate`)|`(persona (edad 14) (nombre Ana))`|Campos con nombre; orden libre; se pueden omitir slots.|

**`deftemplate`** define la estructura:

```clips
(deftemplate clase "comentario opcional"
   (slot grupo)                 ; slot      = 1 valor
   (multislot alumnos)          ; multislot = lista de valores
   (slot aula (default 116)))   ; valor por defecto
```

**Carga / índices:**

- `deffacts` → bloque de hechos que entran a la MT con `(reset)`. Siempre existe `(initial-fact)` (índice `f-0`).
- **Time-tags:** índice único y secuencial (`f-0`, `f-1`...); **nunca se reasigna** (tras `retract`, el siguiente hecho usa un índice nuevo). Sirve para identificar y medir antigüedad.

**Órdenes de la MT:**

|Orden|Efecto|
|---|---|
|`(facts)`|Lista los hechos.|
|`(assert <hecho>)`|Añade (si no existe).|
|`(retract <índice>)`|Elimina.|
|`(modify <índice> <slot>*)`|Cambia un hecho no ordenado (borra la versión anterior).|
|`(duplicate <índice> <slot>*)`|Clona y modifica, **sin** borrar el original.|
|`(clear)`|Borra hechos **y** construcciones (reinicio total).|
|`(reset)`|Vacía la MT y la agenda, y restaura: `initial-fact` + `deffacts`.|

### 2.2. Base de Reglas (`defrule`)

```clips
(defrule <nombre> [ "doc" ] [ (declare (salience <n>)) ]
   (premisa1) ... (premisaN)
=>
   (accion1) ... (accionM))
```

**Premisas — patrones:**

|Patrón|Significa|Ejemplo|
|---|---|---|
|Constante|Equipara con hecho concreto|`(dato 1 azul rojo)`|
|`?`|comodín de **un** campo|`(dato ? azul $?)`|
|`$?`|comodín de **cero a N** campos|`(dato $? amarillo $?)`|
|`?x`|variable de **un valor** (reutilizable)|`(animal ?x)`|
|`$?x`|variable **multivalor**|`(dato ?x $?y ?z)`|
|`(not (<patrón>))`|se cumple si **NO** existe el hecho (_mundo cerrado_)|`(not (avestruz ?x))`|
|`?ref <- (<patrón>)`|guarda **puntero** al hecho para usarlo en el RHS|`?ref <- (estado ?d estudiante)`|

> **Consistencia:** una variable repetida debe valer lo mismo en todas sus apariciones. Cada combinación distinta de `$?`/hechos genera una instancia distinta en el CC.

**Premisas — restricciones:**

|Forma|Conectiva|Equivalente con `test`|Significado|
|---|---|---|---|
|`(test (<expr.bool>))`|—|—|Condición general (notación **prefija**).|
|`?x&~val`|`~` (negación)|`(test (neq ?x val))`|Cualquier valor **menos** `val`.|
|`?x&=(<expr>)`|`=` (valor de retorno)|`(test (= ?x <expr>))`|Solo el valor que **resulta** de `<expr>`.|
|`?x&:(<expr.bool>)`|`:` (predicado)|`(test (<expr.bool>))`|Equipara **si** `<expr.bool>` es `true`.|

```clips
(color ?x&~rojo&~verde)            ; ni rojo ni verde
(dato ?x ?y&=(+ ?x 1))             ; ?y debe ser ?x+1
(valor ?x&:(numberp ?x))           ; ?x numérico
```

**Acciones (RHS):**

- MT: `assert`, `retract`, `modify`, `duplicate`
- E/S: `printout t ... crlf`, `read`, `readline`, `open`, `close`
- Control: `halt` (parar) · `bind ?var <expr>` (variable local)
- Funciones: matemáticas (`+ - * / div max min abs`), multislot (`nth$ length$ member$ create$`...), predicado (`numberp eq...`). Propias con **`deffunction`** (estilo LISP).

### 2.3. Motor de inferencia en CLIPS

Para elegir la regla a disparar: **1.º salience** (entero, por defecto 0, `(declare (salience n))` — _minimizar su uso_); **2.º estrategia**; **3.º arbitrario**.

|Estrategia|Prefiere|
|---|---|
|**Depth** (por defecto)|activación más **reciente** arriba (≈ profundidad)|
|**Breadth**|activación más **antigua** arriba (≈ amplitud)|
|**Complexity**|mayor **especificidad**|
|**Simplicity**|menor **especificidad**|
|**LEX**|compara time-tags de mayor a menor; rellena con ceros; desempata por especificidad|
|**MEA**|como LEX pero priorizando el **primer patrón** de la regla|
|**Random**|número aleatorio|

> ⚠️ **No confundir:** _Depth_ = profundidad (recientes), _Breadth_ = amplitud (antiguas).

**Especificidad** = nº de comparaciones del **antecedente**. Suma 1 por: comparación con constante · comparación con variable ya ligada · llamada a función en `test`/valor-retorno (`:`,`=`). **No** cuentan: booleanas (`and/or/not`) ni funciones anidadas.

```clips
(defrule ej (item ?x ?y ?x)
   (test (and (numberp ?x) (> ?x (+10 ?y)) (< ?x 100))) =>)
;  ?x repetido + numberp + > + <  →  Especificidad = 5  (and y +10 no cuentan)
```

---

## 3. Ejemplos

**Proceso de diseño:** modelo (qué importa) → ontología (vocabulario) → conocimiento del dominio (reglas generales) → conocimiento del caso (`deffacts`) → consultas.

### 3.1. Mundo de los circuitos (inferencia + propagación)

Modelar un circuito lógico para deducir sus salidas. Ontología: `puerta`, `circuito`, `estado-terminal` (deftemplates) + `conexion` (hecho ordenado); señales `TRUE`/`FALSE`.

Las 3 puertas comparten esqueleto; solo cambia la operación de salida:

|Puerta|Señal de salida|
|---|---|
|AND|`(and ?se1 ?se2)`|
|OR|`(or ?se1 ?se2)`|
|XOR|`(not (eq ?se1 ?se2))`|

```clips
(defrule logica-AND
   (puerta (id-puerta ?p) (tipo AND)
           (id-entrada-1 ?e1) (id-entrada-2 ?e2) (id-salida-1 ?s1))
   (estado-terminal (id-elemento ?p) (id-terminal ?e1) (senyal ?se1))
   (estado-terminal (id-elemento ?p) (id-terminal ?e2) (senyal ?se2))
=>
   (assert (estado-terminal (id-elemento ?p) (id-terminal ?s1)
                            (senyal (and ?se1 ?se2)))))
```

Más reglas: `logica-conexion` (terminales conectados comparten señal), `conexion` (conmutatividad), `leer-entradas` (`read`), `imprimir-salidas`. _El circuito C resulta ser un **sumador completo de 1 bit** (s1 = suma, s2 = acarreo)._

### 3.2. Modelar acciones: jarras de agua (espacio de estados)

Estado = hecho; regla = acción (antecedente = precondiciones, consecuente = sucesor).

|Implementación|Idea|Consecuencia|
|---|---|---|
|**1 — Destructiva**|la regla borra el estado previo|un solo estado activo; **sin marcha atrás**|
|**2 — Árbol de búsqueda**|mantiene todos (hijo recuerda al `padre`)|reglas aplicables = agenda; **completa con Breadth**|

Plantilla y patrón de acción (referenciar el padre con `<-`, crear sucesor con `assert`/`duplicate`):

```clips
(deftemplate situacion (slot padre) (slot litros-en-cuatro) (slot litros-en-tres))

(defrule llenar-cuatro-del-grifo
   ?nodo <- (situacion (litros-en-cuatro ?c) (litros-en-tres ?t))
   (test (< ?c 4))
=>
   (assert (situacion (padre ?nodo) (litros-en-cuatro 4) (litros-en-tres ?t))))
```

8 acciones: llenar-{cuatro/tres}-del-grifo, vaciar-{cuatro/tres}-en-pila, llenar/vaciar entre jarras (cada una con su `test` de precondición). _Ejercicio: evitar ciclos/estados repetidos añadiendo premisas `not` que comprueben que el estado no existe ya._

### 3.3. Modelar cambio: mundo de los bloques (efecto + marco)

**Problema:** estados parcialmente caracterizados → no se puede usar un `deftemplate` fijo. **Solución:** hechos ordenados con el **nombre del estado** como argumento: `(on C A S0) (clear C S0)...`

- **Axiomas de EFECTO** → reglas que asertan lo que **cambia** con la acción. Generan estado nuevo con `(gensym*)` y dejan rastro con un hecho `(move ...)`.
- **Axiomas de MARCO** (_frame_) → reglas que **arrastran lo que NO cambia** al estado nuevo (una por par propiedad/acción). Sin ellas se perdería el contexto válido del estado anterior.

```clips
(defrule efecto-move
   (clear ?x ?s1) (clear ?z&~?x ?s1) (on ?x ?y&~?z ?s1)
=>
   (bind ?s2 (gensym*))                 ; nuevo nombre de estado
   (assert (on ?x ?z ?s2)) (assert (clear ?y ?s2)) (assert (clear T ?s2))
   (assert (move ?s1 ?s2 ?x ?y ?z)))

(defrule marco-move-1                    ; clear ≠ ?z persiste
   (move ?s1 ?s2 ?x ?y ?z) (clear ?u&~?z ?s1)
=> (assert (clear ?u ?s2)))

(defrule marco-move-2                    ; on cuyo bloque ≠ ?u persiste
   (move ?s1 ?s2 ?u ?v ?z) (on ?x&~?u ?y ?s1)
=> (assert (on ?x ?y ?s2)))
```

**Traza (Breadth), torre C/A/B en S0:**

|Ciclo|Regla|Resultado|
|---|---|---|
|1|`efecto-move`|aplica `move(C,A,T)` → `gen1`: `(on C T gen1)`, `(clear A gen1)`, `(clear T gen1)`, `(move S0 gen1 C A T)`|
|2|`marco-move-1`|`clear(C)` persiste → `(clear C gen1)`|
|3–4|`marco-move-2`|`on(B,T)` y `on(A,B)` persisten en `gen1`|
|5|`efecto-move`|`move(C,T,A)` → `gen2`...|

---

## Glosario rápido

· **BH/MT** Base de Hechos / Memoria de Trabajo 
· **BR** Base de Reglas 
· **MI** Motor de Inferencia 
· **LHS/RHS** antecedente/consecuente 
· **Equiparación** emparejar reglas↔hechos 
· **CC/Agenda** instancias aplicables no disparadas 
· **Disparo** ejecutar RHS + actualizar BH 
· **RETE** construcción incremental del CC 
· **Especificidad** nº de comparaciones del antecedente 
· **Salience** prioridad explícita 
· **Time-tag** índice único del hecho 
· **Mundo cerrado** lo que no está en la MT es falso 
· **Efecto/Marco** lo que cambia / lo que persiste tras una acción.