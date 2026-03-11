![[InfografíaTema2RCR2.png]]
## Fundamentos de los sistemas basados en reglas (SBRs)
Los SBR son mecanismos de inferencia automática que usan una representación del conocimiento dividida en tres componentes principales: <BH, BR, MI>.
- **Base de Hechos (BH) o Memoria de Trabajo**: Representa el modelo del mundo mediante aserciones y datos.
	- Contiene hechos **permanentes** y **temporales**
	- Modela el inicio, mitad y final del problema mediante añadir y borrar hechos.
- **Base de Reglas (BR):** Agrupa el conocimiento sobre cómo solucionar el problema.
	- Sintáxis: `SI <Premisas (Antecedentes)> ENTONCES <Acciones (Consecuente)>`.
	- Tenemos reglas **constantes** o **variables**. Las segundas se tienen que ligar al valor en toda la regla y todas las variables del consecuente tienen que estar relacionadas con el antecedente. Los hechos NO contienen variables.
- **Motor de Inferencia (MI):** Mecanismo que razona sobre BH aplicando BR.
	- **Encadenamiento hacia delante** (hechos iniciales para llegar a soluciones) o **hacia atrás** (parte de consulta u objetivo buscando subobjetivos)
## Ciclo de Inferencia y Eficiencia
El MI encadenando hacia delante opera mediante un ciclo de razonamiento repetitivo:
1. **Detección (Equiparación):** Determina las reglas compatibles con la BH actual. Genera lo llamado **Conjunto Conflicto (CC)** que son las instancias de reglas aplicables no disparadas todavía (puede haber varias instancias de la misma regla).
2. **Selección**: Aplica estrategias para resolver el CC y elegir una única instancia de regla. Se basan las preferencias en:
	- ***Reglas***
		- Prioridad explícita: asignamos prioridades a cada regla
		- Prioridad implícita: orden de las reglas en la BR (Prolog)
		- Refracción: Historia de una regla
		- Especificidad: Preferir reglas con más/menos condiciones
	- ***Instancias***
		- Más antigua en el CC (amplitud)
		- Más nueva en el CC (profundidad)
	- ***Objetos***
		- Reglas aplicadas a los objetos (hechos) más recientes
		- Prioridad explícita: asignar prioridades a los patrones más comunes de la BH
	- ***Combinaciones de las mencionadas***
3. **Aplicación (Disparo):** Se ejecutan las acciones de la regla seleccionada, modificando la BH. Esto crea un nuevo ciclo, pudiendo eliminar reglas del CC anterior. El ciclo para si CC queda vacío o si una regla ejecuta un comando de parada
- **Algoritmo RETE (Redundancia Temporal):** Soluciona la ineficiencia del primer paso (equiparar todas las reglas contra todos los hechos en cada ciclo). Compila una red de nodos al inicio que actualiza el CC deforma incremental solo con cambios de memoria, compartiendo partes comunes entre reglas.
	- Sólo los nuevos atraviesan los filtros afectados evitando reevaluar todo de cero.
## Diseño de Base de Conocimientos: Errores frecuentes y evaluación
Al usar reglas, es crucial evitar estructuras procedimentales clásicas:
- **No usar *if-then-else***: Mejor reglas independientes identificando las condiciones excluyentes.
- **No usar ORs ni elementos de decisión (if anidados) en el consecuente:** Acciones directas. Debemos crear reglas separadas y gestionar la precedencia introduciendo "señalizadores" (hechos temporales) que fuercen la prioridad (hay que borrarlos luego).
- **Las reglas no llaman a otras reglas:** Nuevamente, debemos afirmar hechos señalizadores para activar la regla que deseamos.
- **Bucles infinitos o duplicación de estados:** Ocurre si una regla borra y mete de nuevo el hecho que la activa, o si no manejamos la actualización exclusiva de un valor (ej. múltiples costes para un envío). Se arregla con señalizadores o nuevos tipos de hechos.
- **Ventajas e Inconvenientes:** Pŕoxima al experto, sencilla y trazable. Pero dificulta expresar conocimiento puramente procedimental y verificar la consistencia global. 
## Implementación en CLIPS
CLIPS es una herramienta en C/ANSI para SBR por encadenamiento hacia delante.

**La Memoria de Trabajo (Base de Hechos en CLIPS)**
- **Hechos ordenados:** Posición relevante, no tienen tipos estrictos y se definen entre paréntesis (ej `(edad 14)`).
- **Hechos no ordenados (`deftemplate`):** Abstracciones con nombre. `slot` para valores únicos y `multislot` para listas. Al instanciarlos, el orden no importa y se pueden omitir campos. 
- **Hechos iniciales (`deffacts`):** Bloques de hechos que se cargan automáticamente. Siempre existe el `initial-fact`.
- **Índices (time-tags):** CLIPS asigna un índice temporal único y secuencial a cada hecho (ej. `f-0`, `f-1`) para identificarlo y conocer su antigüedad. 
- **Órdenes de consola:** `(facts)` lista, `(assert)` añade, `(retract)` elimina, `(modify)` cambia valores y borra la anterior versión al completo, `(duplicate)` clona y hace cambios sobre la copia, `(clear)` borra todo el sistema, `(reset)` restaura al estado inicial .
**La Base de Reglas (`defrule`)**
- **Patrones y Comodines**: El antecedente evalúa patrones contra la MT. Los comodines abarcan valores irrelevantes: `?` (un campo) y `$?` (cero a N campos)
- **Variables:** Extraen datos de los hechos para usarlos. Siguen la lógica `?x` (un valor) o `$?x` (multivalor). Deben equiparar con el mismo valor en todas sus ocurrencias dentro de la regla.
- **Ausencia (`not`):** La regla se dispara si *no* existe un hecho, basándose en la *Hipótesis del mundo cerrado*
- **Direcciones de hechos** `?ref <- (patron)` guarda el puntero del hecho en una variable para poder alterarlo (ej borrarlo) en el consecuente.
- **Restricciones** De premisa `(test(<expr>))` evalúa funciones booleanas, comparaciones y predicados (ej. `numberp`).
	- Conectivas: Modifican el emparejamiento de variables con `&~` (no igual a), `&=` (igual al valor de retorno en una expresión), y `&:` (debe cumplir un predicado booleano). 
- **Acciones (Consecuente)**: Comandos de MT, E/S (`printout`, `read`), parada (`halt`) y asignación local (`bind`). Admite numerosas funciones predefinidas (matemáticas, de strings) y creación de funciones propias tipo LISP (`deffunction`).
**El Motor de Inferencia en CLIPS**:
- Para elegir qué regla disparar en el paso 2 del ciclo, CLIPS primero evalúa la **prioridad explícita** `(declare (salience X))`.
- Luego aplica una de estas **Estrategias de resolución:**
	- *Depth* (por defecto): Prefiere activaciones más recientes (amplitud)
	- *Breadth*: Prefiere activaciones más antiguas
	- *Complexity:* Prefiere reglas con mayor **especificidad**
	- *Simplicity:* Menos especificidad
	- *LEX:* Compara time-tags de mayor a menor; desempata por especificidad.
	- *MEA:* Igual que LEX, pero da peso absoluto al primer patrón de la regla. 
	- *Random:* Aleatorio
## Modelado Avanzado: Resolviendo Problemas
El diseño de la BC implica definir el modelo, la ontología, el conocimiento del dominio (reglas generales) y el del caso (datos específicos).
- *Ej.* En el problema lógico de puertas y circuitos, se usa topología como estado inicial y aplicamos reglas de conocimiento de puertas lógicas (AND, OR, XOR, ...) para inferir y propagar valores de señales.
- **Modelado de cambio en espacio de estados (Ej. Mundo de bloques o Jarras de agua):**
	- **Implementación 1 (Destructiva):** La regla borra el estado previo. Solo un estado activo a la vez. No hay marcha atrás si hay errores.
	- **Implementación 2 (Árbol de búsqueda):** Mantiene todos los estados generando enlaces jerárquicos (hijo recuerda a su padre). Funciona con estrategias de *Breadth* para exploración de soluciones completas.
	- Para modelar saltos entre estados se usan dos conceptos:
		1. **Axiomas de efecto** -> Reglas que describen qué propiedades nuevas aparecen como resultado de una acción. (Mover un bloque C sobre A deja T libre)
		2. **Axiomas de marco (Frame axioms):** Reglas esenciales para decir que NO cambia tras una acción, evitando perder info contextual válida del estado anterior (Mover C sobre A no altera B respecto a T). 