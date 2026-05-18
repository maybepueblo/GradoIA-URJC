# Estructura del temario
El tema se divide en 4 secciones principales:
1. **Concepto de robot**
2. **Historia y evolución de la robótica. Leyes de Asimov**
3. **Aplicaciones de la robótica en la industria**
4. **Aplicaciones de la robótica en la investigación**

---
# Concepto de robot
### Definición
#### ¿Qué es la Robótica?
La **robótica** es:
- Una ciencia que agrupa varias disciplinas de ingeniería
- Se centra en el diseño, operación, estudio y aplicación de autómatas o robots
- Interacciona con otras ciencias y tecnologías emergentes
#### Disciplinas Integradas en la Robótica
La robótica es un campo **multidisciplinario** que integra:

|Disciplina|Especialidad|
|---|---|
|**Electrónica**|Componentes eléctricos y sistemas de potencia|
|**Mecánica**|Estructura física y movimiento|
|**Informática**|Procesamiento de datos y algoritmos|
|**Control**|Regulación y automatización del comportamiento|
|**Especialidades Derivadas**|Control electrónico, Electromecánica, Control digital, CAD/CAM|

---
### 3. ¿Robot?
#### Definición Formal
Un **robot** es:
- Una máquina programable capaz de realizar tareas con autonomía total o parcial
- Sistema que puede operar con diferentes grados de independencia

#### Elementos Principales de un Robot
Todo robot posee cuatro componentes esenciales:
1. **Sensores**
    - Función: Percibir el entorno
    - Capturan información del mundo exterior
    - Ejemplos: sensores de posición, fuerzas, IMUs (acelerómetros y giróscopos), cámaras, LIDAR
2. **Actuadores**
    - Función: Realizar movimientos e interactuar con el entorno
    - Convierten comandos en acciones físicas
    - Ejemplos: motores, cilindros hidráulicos, servos
3. **Controladores**
    - Función: Procesar la información y tomar decisiones
    - Constitucionales electrónicos o sistemas informáticos embebidos
    - Ejecutan algoritmos de control
4. **Programas**
    - Función: Instrucciones para guiar el comportamiento del robot
    - Definen la lógica de operación
    - Permiten adaptar el comportamiento a diferentes tareas
#### Funcionamiento General
El funcionamiento de un robot es análogo al de un computador:
1. **Entrada**: Reciben información del entorno (mediante sensores)
2. **Procesamiento**: La procesan (mediante controladores)
3. **Salida**: Generan acciones en base a su programación (mediante actuadores)
#### Ejemplo Práctico: Boston Dynamics BigDog
Un ejemplo avanzado de robot complejo es el **BigDog** de Boston Dynamics, que incluye:

**Sistemas Sensoriales:**
- Sensores en las articulaciones para medir fuerza y posición
- Giróscopos e IMUs para mantener el equilibrio
- Sistema de cámaras estéreo y LIDAR para navegación

**Sistemas de Actuación:**
- Cuatro actuadores hidráulicos por pierna
- Bomba hidráulica controlada por un motor de combustión interna

**Sistema de Control:**
- Ordenador embebido para navegación y locomoción
- Sistema operativo basado en Unix para control en tiempo real

---
### Ejemplos de robots actuales
- **ACM-R5H**: Robot acuático
- **Roomba**: Robot aspirador (limpieza doméstica)
- **Phantom**: Dron (navegación aérea)
- **Asimo**: Robot humanoide (Honda)
- **Replicator+**: Impresora 3D robótica
- **Da Vinci**: Robot quirúrgico (medicina)
- **Ekso**: Exoesqueleto (rehabilitación)
- **PackBot**: Robot terrestre (tareas de seguridad)

---

# Historia y evolución de la robótica

#### ANTIGÜEDAD
**Concepto de Autómata en Antigua Grecia**
- El término "autómata" (automatos) describe una máquina que imita la figura y movimientos de un ser animado
- Se diseñaban con finalidad lúdica
- Mecanismo: dispositivos hidráulicos, poleas y palancas

**Ejemplos Históricos:**
- **Gallo autómata de la Catedral de Estrasburgo** (aprox. 1350): Ejemplo medieval de automatismo
- **Leonardo da Vinci (Siglo XV)**: Crea el primer autómata de la era moderna - un león mecánico

#### SIGLO XX - Hitos Fundamentales

|Año|Evento|Importancia|
|---|---|---|
|**1920**|Karel Čapek acuña el término "robot"|Origen del término usado hoy|
|**1939**|Elektro presentado en la Feria de Nueva York|Primer robot humanoide comercializado|
|**1941**|Isaac Asimov formula las 3 Leyes de la Robótica|Marco ético fundamental para robots|
|**1943**|McCulloch y Pitts publican paper sobre cálculo lógico|Bases de la inteligencia artificial|
|**1950**|Alan Turing publica "Computing Machinery and Intelligence"|Propuesta del Test de Turing|
|**1961**|Unimate en General Motors|Primer robot industrial efectivo|
|**1966**|Shakey presentado|Primer robot móvil de propósito general|
|**1974**|Intel 8080 en producción masiva|Procesadores miniaturizados para robots|
|**1981**|Robots SCARA en líneas de montaje|Avance en manufactura|
|**1985**|Término "Realidad Virtual" (J. Lanier)|Expansión de interfaces humano-máquina|
|**1988**|Primer chatbot (R. Carpenter)|Interacción conversacional robótica|

#### ERA MODERNA (1995 - Actualidad)

|Año|Evento|Significado|
|---|---|---|
|**1995**|Dron militar MQ-1 Predator|Robotización de operaciones militares|
|**1997**|IBM Deep Blue vence a Kasparov en ajedrez|IA supera al humano en juegos complejos|
|**1998-99**|Furby y AiBO se comercializan|Robots de compañía accesibles al público|
|**2000**|Honda presenta ASIMO|Humanoides avanzados|
|**2002**|iRobot lanza Roomba|Robotización del hogar|
|**2004**|Spirit y Opportunity aterrizan en Marte|Rovers para exploración extraplanetaria|
|**2011**|Apple presenta Siri|Asistentes personales inteligentes|

---
### Leyes de Asimov
Conjunto de normas éticas formuladas por el escritor de ciencia ficción **Isaac Asimov** en 1941, que establecen principios para el comportamiento de robots:
#### Primera Ley (Máxima Prioridad)
**"Un robot no debe dañar a un ser humano o, por inacción, permitir que un ser humano sufra daño"**
#### Segunda Ley (Obediencia Condicionada)
**"Un robot debe obedecer las órdenes dadas por los seres humanos, excepto cuando entren en conflicto con la Primera Ley"**
#### Tercera Ley (Autopreservación Limitada)
**"Un robot debe proteger su propia existencia siempre y cuando dicha protección no entre en conflicto con la Primera o Segunda Ley"**

**Jerarquía de Leyes:** Primera > Segunda > Tercera (conflictos se resuelven por orden de prioridad)

---
# Aplicaciones de robótica en industria

#### Sectores de Aplicación
**Manufactura:**
- Robots de ensamblaje (montaje de componentes)
- Robots de soldadura (unión de piezas)
- Robots de pintura (acabado de productos)
**Logística:**
- Robots de manipulación (movimiento de piezas)
- Robots de transporte (desplazamiento de cargas)
- Robots de almacenamiento (gestión de inventarios)
**Control de Calidad:**
- Inspección automatizada
- Pruebas automatizadas
- Verificación de especificaciones
#### Ventajas Competitivas
1. **Eficiencia y Precisión**
    - Aumentan la velocidad de producción
    - Reducen errores y variabilidad
    - Mejoran la consistencia del producto
2. **Reducción de Costes**
    - Disminuyen costes operacionales a largo plazo
    - Optimizan el uso de materiales
    - Reducen necesidades de personal en tareas repetitivas
3. **Mejora de la Seguridad Laboral**
    - Eliminan trabajadores de entornos peligrosos
    - Reducen accidentes laborales
    - Mejoran las condiciones de trabajo
#### Ejemplo Práctico
**ABB en líneas de montaje**: Robots industriales naranjas utilizados en manufactura automotriz y otras industrias pesadas

---
### Aplicaciones de robótica en investigación

#### Exploración Espacial
- **Rovers**: Vehículos autónomos para exploración planetaria
    - Ejemplo: **Sojourner en Marte** (1997) - primer rover que operó exitosamente en otro planeta
    - Otros: Spirit, Opportunity, Curiosity, Perseverance
- **Robots en la Estación Espacial Internacional**: Manipuladores para reparaciones y experimentos
#### Medicina
- **Cirugía robótica**: Sistemas como Da Vinci para procedimientos de precisión extrema
- **Exoesqueletos**: Aumentan la fuerza humana y ayudan a personas con movilidad limitada
- **Robots de rehabilitación**: Asisten en la recuperación de pacientes
#### Monitorización Ambiental
- **Drones**: Vigilancia de flora y fauna
- **Recopilación de datos**: Estudios sobre cambio climático, biodiversidad
- **Acceso a zonas de difícil acceso**: Selvas, montañas, océanos
#### Inteligencia Artificial
- **Robots cognitivos**: Sistemas que aprenden y adaptan su comportamiento
- **Experimentación**: Pruebas de algoritmos de IA
- **Recolección de datos**: Información del mundo real para entrenar sistemas