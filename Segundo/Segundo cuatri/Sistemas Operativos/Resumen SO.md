Este es un resumen de la materia de Sistemas Operativos de cara al examen.

**¿Qué es un sistema operativo?**
Programa fundamental encargado de gestionar los recursos del sistema y coordinar la ejecución de los programas.

Sin este, un programa no podría ejecutarse pues no sabría cómo acceder a los recursos necesarios para su misma ejecución.

***Funciones principales de un SO***
1. **Gestión de procesos** -> crear, planificar y terminar procesos. Decidir qué proceso se ejecuta y cuándo.
2. **Gestión de memoria** -> asignar memoria a procesos y liberarla. Asegurar que estos procesos no interfieran entre sí.
3. **Gestión del sistema de archivos** -> organiza y controla el acceso a la información en discos y otros medios.
4. **Gestión de dispositivos** -> actúa como intermediario entre programas y hardware.
5. **Gestión de usuarios y seguridad** -> protege el sistema y los datos. Controla el acceso a los recursos.
6. **Interfaz de usuario** -> ofrece una forma de interactuar con el sistema, o por línea de comandos (CLI) o entorno gráfico (GUI).

**Tipos de sistemas operativos**
- **SO de Escritorio**: Uso personal. Ofrecen una experiencia amigable e interactiva. Optimizados a trabajar con una sola persona a la vez con tareas variadas
	- Entorno gráfico completo
	- Soporte multimedia
	- Énfasis en experiencia del usuario
- **SO de Servidor**: Diseñados para ejecutar servicios red, manejando múltiples usuarios y estar encendido fleje tiempo sin errores.
	- Estabilidad y rendimiento prioritario
	- Escasa interfaz gráfica (o nula)
	- Control remoto, administración de usuarios y recursos
- **SO en Tiempo Real**: Hechos para entornos donde haya que responder dentro de un tiempo exacto y garantizado. Se trata de cumplir plazos de respuesta como en sistemas médicos, de control industrial o vehículos.

**Multitarea y planificación**
Esto es ejecutar muchos procesos "a la misma vez". Se están intercalando muy rápido gracias a la planificación de procesos.

El planificador decide a qué proceso se le da el procesador y por cuánto tiempo. Se hace con diversos algoritmos, según el tipo de sistema.
## Procesos
Son programas en ejecución con su propio espacio de recursos y contexto de ejecución. 
	Dentro, tenemos los hilos, que son unidades de ejecución y comparten los recursos de este proceso.

>[!NOTE] Dato
>os.kill no mata directamente un proceso, sino que envía una señal. El efecto depende de la señal enviada y de si el proceso la maneja o la ignora.

Cada proceso tiene un identificador PID y un proceso padre PPID, formando una estructura jerárquica similar a un árbol de procesos. Estos procesos se ejecutan con ciertos privilegios (como el usuario creador) y el sistema operativo controla qué pueden hacer según sus permisos.

La comunicación entre procesos (IPC) se puede hacer con:
- **Pipes** para enviar datos entre procesos
- **Memoria compartida** para que varios procesos lean y escriban en la misma zona de memoria
- **Semáforos y mutexes** para sincronizar el acceso a recursos y evitar interferencias
- **Sockets** para comunicarse entre procesos incluso en diferentes máquinas

**Estados o fases de un proceso**
Durante su vida, pasa por varios estados:
- **new** inicio del proceso
- **ready** esperando acceso a CPU
- **running** ejecutado en CPU
- **waiting/blocked** esperando evento externo
- **terminated/exit** final del proceso
Hay más estados pero estos son los vitales
### ¿Sockets?
- Punto de conexión que permite que dos programas (procesos) se comuniquen entre sí
- Pueden estar en la misma máquina o en máquinas diferentes conectadas por red.
**¿Cómo funcionan?**
- Cada programa tiene uno y "escucha" o "habla" a través de él.
- Para que funcione, uno abre un socket en modo servidor y otro en cliente.
**¿Uso?**
- Enviar y recibir datos entre programas
- Base de muchas cosas como juegos online, chats...
### ¿Pipes?
Mecanismo que permite la comunicación entre procesos, siendo un canal por donde fluyen datos en forma secuencial.
- Siendo dos procesos creados por un padre común (fork), pueden compartir descriptores de archivo y usar pipes anónimos para comunicarse directamente.
- Si no tienen ese parentesco, deben usar pipes con nombre (FIFO), siendo buffers especiales en memoria que cuentan como archivos virtuales para cambiar datos entre procesos independientes.
## Señales

**¿Qué es una señal en sistemas operativos?**
Es una notificación que el sistema operativo o un proceso puede enviar a otro proceso para que reaccione de alguna forma.

*Ejemplos*
- SIGTERM -> Terminar proceso
- SIGINT -> Interrupción
- SIGKILL -> Forzar la terminación

**¿Quién las puede enviar?**
1. **El sistema operativo automáticamente**
	- SIGSEGV: accede el proceso a memoria no válida
	- SIGFPE: dividir por cero
	- SIGKILL o SIGTERM: si pedimos terminar el proceso
2. **Otro proceso**
	- Funciones como kill(pid, señal) puede enviarlo a otro proceso si tiene permisos
3. **El propio proceso**
	- Puede enviarse una señal a sí mismo
	- O puede decidir su reacción ante otras señales

**¿Qué puede hacer un proceso al recibir una señal?**
1. **Aceptar el comportamiento por defecto**
2. **Capturarla y manejarla con una función propia**
3. **Ignorarla** (no con todas)
	- Señales como SIGKILL o SIGSTOP **no pueden ni ignorarse ni manejarse**
## Concurrencia
Es cuando varios hilos o procesos **parecen** ejecutarse al mismo tiempo
- En un **procesador único**, se logra alternando la CPU entre ellos (muy rápido)
- En un **multiprocesador**, sí se pueden ejecutar realmente al mismo tiempo (en paralelo)

**¿Condición de carrera?**
Es cuando dos o más hilos acceden a la vez a un dato compartido y el resultado depende del orden en el que se ejecutan.
- Por ejemplo, dos hilos incrementando el contador a la vez. Si no lo controlamos, perdemos información.
Las operaciones no son **atómicas** (no se hacen completas de una sola vez)

Para solucionarlo está la **sincronización**, que es el conjunto de técnicas para coordinar estos hilos/procesos y asegurar que no se pisen entre sí cuando usan esos datos compartidos.

**Conceptos importantes**
- **Sección crítica**: Parte del código donde un hilo accede a datos compartidos
- **Exclusión mutua**: Solo **un hilo a la vez** puede estar en la sección crítica
- **Progreso**: Si la sección crítica está libre, **algún hilo debe de poder entrar**
- **Espera limitada**: Ningún hilo debe **esperar por siempre** para entrar
### Semáforos
**Variable especial** controlada por el SO para **gestionar el acceso a recursos compartidos**

Sólo se puede usar con dos operaciones **atómicas**:
- **wait(S)** (también llamada P o down):
	- Intenta entrar en la sección crítica
	- Si el semáforo vale 0 o menos, el hilo se bloquea y espera
	- Si vale más de 0, lo decrementa y continúa
- **signal(S)** también llamada V o up:
	- Sale de la sección crítica o libera el recurso
	- **Incrementa** el semáforo
	- Si hay hilos esperando, **despierta uno**
Al ser operaciones atómicas, no se pueden interrumpir a la mitad

**Tipos de semáforo**:
- **Semáforo Binario** (Mutex)
	- Sólo puede valer 0 o 1. Sirve para que un solo hilo a la vez entre en la sección crítica (como una llave)
- **Semáforo Contador**
	- Puede valer cualquier número entero positivo. Lo usamos para limitar el acceso a recursos múltiples, como plazas de parking.

**¿Por qué usarlos?**
- Aseguran la **exclusión mutua**
- Evitan errores por **condiciones de carrera**
- Son **eficientes**: si un hilo no puede entrar, se bloquea y NO gasta CPU

***Problemas clásicos de semáforo***
- **Productor-Consumidor**: coordinar un proceso que llena un buffer y otro que lo vacía.
- **Lectores-Escritores**: lectores leyendo a la vez pero solo un escritor.
## Hilos
### Kernel
Parte principal del SO que controla y gestiona todo el hardware y recursos del computador, como CPU, memoria y dispositivos.

**Tipos de hilos**
- **De usuario**: El programa los controla directamente, sin que el kernel se entere. Fáciles y rápidos de crear, pero no se sabe de su existencia.
- **De kernel**: Aquí sí se sabe de cada uno y puede asignarles tiempos de CPU, gestionarlos y aprovechar varios procesadores

**Significado de "mapear" hilos de user a kernel**
Así emparejamos/conectamos hilos de user a los hilos del kernel. Define así cuantos hilos de kernel podemos usar para manejar los de usuario.

**Modelos de relación entre tipos de hilos**
1. **Muchos a uno**
	- Muchos hilos creados por el programa (user) **usan un solo hilo del kernel**
		- Esto dice que aunque el programa tenga varios hilos, el sistema sólo ve uno
		- Si un hilo se bloquea, todos los demás también
2. **Uno a uno**
	- Cada hilo creado por el programa tiene **su propio hilo en kernel**
		- El SO puede manejar cada hilo individualmente
		- Esto permite que los hilos se ejecuten al mismo tiempo en varios procesadores
3. **Muchos a muchos**
	- Muchos hilos del programa se pueden "emparejar" con varios hilos del kernel pero no necesariamente uno a uno.
		- Esto mezcla ventajas: permite crear muchos hilos, pero el kernel solo maneja algunos para optimizar.
## Planificación

**¿Por qué es importante gestionar la memoria?**
Para que un programa se pueda ejecutar, debe de estar en RAM. El SO se encarga de repartir y organizar la memoria.

**Direcciones y MMU**
Al compilar un programa, sus instrucciones hacen referencia a direcciones **lógicas o virtuales**. Pero la memoria física usa **direcciones físicas**.

La MMU es un hardware especial que traduce automáticamente las direcciones virtuales a físicas.

**Asignación Contigua** (modelo antiguo)
En sistemas más simples, a cada proceso se le asignaba un bloque de memoria **contiguo**. Esto generaba dos tipos de desperdicio:
- **Fragmentación externa**: hay memoria libre, pero no está toda junta
- **Fragmentación interna**: se le da al proceso más de lo que necesita, y lo que sobra se desaprovecha.
Se intentaba solucionar con **compactación** (reorganizar memoria para juntar lo libre), pero era muy costoso.

**Paginación: solución moderna a la fragmentación externa**
Permite que la memoria de un proceso no esté junta, sino dividida en partes que pueden estar dispersas en la RAM.
- **¿Qué es una página y un marco?**
	- **Página** Es un bloque de memoria virtual de un proceso. Todos los procesos dividen su espacio en páginas del mismo tamaño, por ejemplo, 4KB.
	- **Marco (frame)** Es un bloque de la memoria física del mismo tamaño que una página
	Al ejecutar un proceso, sus páginas se cargan en marcos disponibles, aunque no estén seguidos entre sí.
- **Tabla de páginas**
	Cada proceso tiene una, que dice en qué marco está cada página suya. La dirección virtual se divide en dos partes:
	- **Número de página** sirve como índice para buscar en la tabla de páginas
	- **Desplazamiento** indica la posición dentro de esa página

La **MMU** traduce tal que:
1. Usa el número de página para mirar en la tabla de páginas del proceso
2. Encuentra el marco físico correspondiente
3. Suma el desplazamiento para obtener la dirección física exacta

Esta técnica **elimina la fragmentación externa**, pero **introduce fragmentación interna** si no se llena completamente la última página.

**Optimización TLB**
La traducción de direcciones puede ser lenta si hemos de mirar siempre en la tabla de páginas (RAM). Existe por ello el TLB, pequeña caché que guarda las traducciones más recientes. 
- Si la traducción está en el TLB (**hit**): se accede muy rápido
- Si no está (**miss**) se accede a la tabla, se traduce y se guarda en el TLB

**Protección y compartición**
- Cada entrada puede tener **bits de protección** y un bit **válido/inválido**
	- **Válido** la página está cargada en RAM y es accesible
	- **Inválido** no está cargada (puede estar en disco o no ser legal)
- Se pueden compartir **páginas entre procesos**, lo que ahorra memoria. Basta con que diferentes tablas de páginas apunten al mismo marco

**Paginación multinivel**
Si el espacio de direcciones virtuales es muy grande, la tabla de páginas puede ocupar demasiada memoria.
	***Solución*** dividir la tabla de páginas en varias partes
Por ejemplo en paginación de dos niveles:
- Se usa la dirección virtual (p1, p2, d)
	- **p1** índice tabla exterior
	- **p2** índice tabla interior
	- **d** desplazamiento
Reduce el tamaño de tablas, puede requerir más accesos a memoria (el TLB)

**Memoria virtual y paginación bajo demanda**
Esta permite ejecutar programas más grandes que la RAM real. No cargamos todas las páginas del proceso al empezar, solo las necesarias.
- **Paginación bajo demanda** las páginas se cargan a medida que se acceden
- Si se accede a una página no cargada, se produce un **fallo de página**
	1. El SO comprueba que la página es válida
	2. Encuentra un marco libre
	3. Carga la página desde disco al marco
	4. Actualiza la tabla de páginas
	5. Reintenta la instrucción

La **tasa de fallos de página** debe mantenerse baja, porque leer del disco es mucho más lento que de la RAM.

**Sustitución de páginas**
Al no haber marcos libres (fallo de página), hay que sacar una página de la RAM para la nueva, llamado reemplazo de página. 
- **Bit de modificación** si la página fue modificada, hay que escribirla al disco antes de sacarla
- Si no, se descarta directamente

**Algoritmos de reemplazo**
- **FIFO** se saca la más antigua. Es simple, pero no siempre eficaz
- **OPT (óptimo)** ideal teórico, saca la que no se usará en más tiempo. No se puede implementar directamente.
- **LRU** saca el que más tiempo lleva sin usarse. Muy bueno pero dificil de implementar de forma exacta.
- **Reloj** LRU eficiente. Recorre las páginas en forma circular. Si el bit de uso es 0, la reemplaza; si es 1, le da una segunda oportunidad (lo pone a 0 y sigue buscando)

**Hiperpaginación** (Trashing)
Situación crítica donde el sistema **pasa más tiempo cargando y sacando páginas que ejecutando código**

Ocurre cuando hay muchos procesos activos y cada uno tiene muy pocos marcos. Resultado:
- Muchos fallos de página
- Baja eficiencia
- El SO carga más procesos para compensar... esto agrava el problema

*Solución*
- Controlar el **conjunto de trabajo** de cada proceso
- Si la suma de todos los conjuntos supera la memoria disponible. **suspende procesos** y libera marcos

**Tamaño de página ¿grande o pequeño?**
- **Páginas pequeñas**
	- Menos fragmentación interna pero tablas más grandes lo que es igual a más accesos a disco
- **Páginas grandes**
	- Tablas más pequeñas, siendo E/S más eficiente pero mucha más fragmentación interna.
La tendencia moderna es usar **tamaños grandes** o incluso **múltiples tamaños** según uso.
