#### Sección 7.1 - Jerarquía de memoria principal

**Introducción a la jerarquía de memoria**
El diseño de esta jerarquía marca una gran diferencia en el rendimiento del computador.

- **Memoria principal** -> unidad funcional del computador que almacena instrucciones y datos que vaya a usar el procesador. Cuando lanzamos un programa junto con sus datos, se ha de alojar en esta memoria para que el procesador tenga acceso al programa.

- **Existen otros tipos de memoria**
	- Registros
	- Memoria caché
	- Memoria secundaria

- **Tecnologías**
	- Memoria principal -> tecnología de semiconductores
		- *DRAM* -> Ocupa menos espacio y por tanto se puede almacenar más (por unidad de espacio). Es una memoria dinámica de acceso aleatorio.
		- *SRAM* -> Ocupa más espacio y por unidad de espacio se almacena menos en ella. Es una memoria estática de acceso aleatorio
		- DRAM es más barata por bit pero la SRAM es más rápida que la DRAM.
	- Memoria secundaria -> soportes magnéticos, ópticos, etc.
		- Más lentos que las basadas en semiconductores.

##### Terminología básica

**Celda de memoria** -> Unidad mínima de almacenamiento (1 bit)

**Palabra de memoria** -> Agrupación de celdas de memoria que constituye la unidad natural de organización de la misma.

**Unidad direccionable** -> Elemento mínimo con dirección propia. No tiene por qué ser una celda pero lo más habitual es que sea algo más cercano al byte que a otras unidades.

**Unidad de transferencia** -> Número de bits accedidos en una operación de lectura o escritura. Guarda mucha relación con el tamaño de palabra del computador, como sabemos existen cargas o almacenamientos a tamaño de palabra o de byte. Puede tener otros tamaños.

**Densidad de memoria** -> Datos almacenados por unidad de área

**Capacidad de memoria** -> Cantidad de información que puede almacenar.

**Coste por bit** -> Dinero que cuesta la memoria dividido por su capacidad.

**Tiempo de acceso** -> tiempo que tardamos en acceder a un dato.
	**Tiempo del ciclo de lectura** -> tiempo que tardamos en leer un dato.
	**Tiempo del ciclo de escritura** -> tiempo que tardamos en escribirlo.
	Puede ocurrir que ambos tiempos sean iguales o puede pasar que en el tiempo de escritura haya que modificar algo mientras que en la lectura se copie sin más, pues escritura será mayor que lectura.

**Tiempo de ciclo** -> tiempo mínimo que debe transcurrir entre dos accesos consecutivos a memoria.

##### Tipos de memorias

- Por tipo de acceso: Las diferencias están en que las aleatorias se puede acceder de manera aleatoria sin mirar nada más. Sin embargo, en las secuenciales se ha de pasar por todo. Luego en las directas se organizan por zonas cuyo acceso es aleatorio, pero dentro de la zona el acceso es secuencial. Finalmente están las de acceso asociativo a las que se accede por contenido y no por dirección.

- Por persistencia de la información:
	- **Memoria volátil o no volátil** -> Si es no volátil la memoria es persistente en cuanto se acaba la conexión, es decir sigue estando ahí, cosa que no pasa si es volátil.
	- **Memoria de solo lectura** -> Se puede leer en ellas pero no escribir, ahora sí existen algunas donde se puede.
	- **Memoria estática o dinámica** -> En la estática la información perdura hasta que se vuelva a escribir o hasta que se quita la alimentación. Sin embargo las dinámicas están formadas por elementos capacitivos donde la energía vuelve a decaer, obligándonos a darle otro chute de energía, lo cual da una gráfica que se ciñe por picos, el tiempo hasta que le damos otro chute se llama tiempo de refresco.

##### Latencia y ancho de banda

- **Latencia de memoria** -> tiempo transcurrido entre que se pide una información, comienza el acceso a memoria y el instante en el que la memoria tiene disponible esa información y comienza a transmitirla.
- **Velocidad de transferencia o ancho de banda** -> medimos el ancho de banda que es el número de datos transmitidos por unidad de tiempo.

##### Concepto de localidad y jerarquía de memoria

- Concepto de localidad: se debe a la estructura de los programas.
	- **Localidad temporal** Hablamos de que cuando usamos una información, pues muy probablemente se va a volver a usar en muy corto espacio de tiempo.
	- **Localidad espacial** Cuando accedemos a una información, probablemente accederemos a la información que tiene a su alrededor.

Sobre estos elementos se construye el sistema de memoria organizado en niveles jerárquicos. 

El nivel más alto es el que está más cerca del procesador, y el de más abajo, el que menos. Cuanto más cerca del procesador la memoria es más pequeña y más rápida (además de más cara), mientras que si estamos más lejos, la memoria es más grande y más lento (además de más lento).

##### Jerarquía de memoria: niveles

Cuando estemos en un nivel, acudiremos a buscar una información y puede ocurrir que:
- La información esté disponible -> acierto
- No lo esté -> fallo

Si hay un acierto accedemos a la información a la velocidad de ese nivel de memoria (nos interesa que el nivel esté muy cerca del procesador para que se ocurra un acierto ahí y que la velocidad de acceso sea muy elevada). Podemos calcular esto con:

- **Tasa de aciertos** -> % de accesos a memoria encontrados en el nivel buscado.
- **Tiempo de acierto** -> nos mide el rendimiento en función del tiempo necesario para acceder al nivel en el que hemos buscado.

Si los datos no se encuentran en el nivel porque no está la info disponible, pues se produce un fallo. Hemos de bajar al nivel inmediatamente al nivel inferior, el cual es superior, lo que supone una penalización por fallo. Hemos, en el nivel inferior, de encontrar la información que nos interesa, copiarla y llevarla al nivel que nos interesa para acceder a él, para luego completar el acceso. Podemos medirlo con:

- **Tasa de fallo** -> % de accesos a memoria en que los datos NO están en el nivel buscado.
- **Penalización por fallo** -> tiempo para reemplazar el bloque del nivel del fallo por el bloque correcto, que estará en el nivel inmediatamente inferior, más el tiempo para suministrar este bloque al procesador.

##### Medición del rendimiento

¿Cómo se mide?

Tiempo medio de acceso a memoria = tiempo de acierto * tasa de aciertos + penalización por fallo * tasa de fallos. 

Si hay varios niveles en la jerarquía:

- Tiempo medio de acceso a memoria-n1 = tiempo de acierto-n1 * tasa de aciertos-n1 + penalización por fallo-n1 * tasa de fallos-n1. 
- Penalización por fallo-n1 = tiempo de acierto-n2 * tasa de acierto-n2 + penalización por fallo-n2 * tasa de fallos-n2. 
- Tiempo medio de acceso a memoria-n1 = tiempo de acierto-n1 * tasa de aciertos-n1 + (tiempo de acierto-n2 * tasa de acierto-n2 + penalización por fallo-n2 * tasa de fallos-n2)  * tasa de fallos-n1

##### Concepto de localidad

Se debe a la estructura de los programas y es algo intrínsicamente humano. Somos seres por lo tanto muy secuenciales, que quiere decir que accedemos a los datos de forma ordenada, tendemos a trabajar con datos que tengamos cerca o directamente los próximos. 
- Esto es lo que dicta la **localidad espacial** que dicta que si accedemos a un dato, muy probable es que accedamos a los datos cercanos.
- La **localidad temporal** sin embargo trata de argumentar que si usamos una instrucción o dato, probablemente volvemos a acceder a ese dato o instrucción en breve.


##### Estructura y tecnología de la memoria principal

Empleamos actualmente semiconductores, que tienen tres tipos de señales:

- Señal de dirección: imprescindible para usar la memoria principal
- Líneas de datos: si es para lectura pues tendremos una salida de líneas de datos, pero si es para lectura tendremos entonces una lectura de datos.
- Si tenemos un ancho de dirección de M bits, decimos que tenemos 2 elevado a M elementos direccionables en la memoria, la salida es el ancho de la palabra de computador, si este es N bits, pues tendremos esos bits en la salida.
- Disponemos de señales de control como la señal de selección de chip (CS), la de lectura y escritura (WE), la señal de habilitación de la salida (OE) y la señal de habilitación de direcciones para las memorias DRAM.

Hay tres tipos grandes: La ROM, SRAM y la DRAM.
	- Existen una gran variedad de ROM como las programables, ejemplos son PROM, EPROM, EEPROM o las Flash, que son las actuales que permiten el almacenamiento de la BIOS.
	- Las SRAM tienen señal de selección de chip, el output enable y el write enable.
		- En los biestables D, se organizan por filas y columnas y cada celda de la memoria tiene un codificador que permite seleccionar la fila, la celda en función de la información aportada a la que vamos a acceder.
		- Se pueden implementar de muchas maneras, para ahorrar circuitería las estructuramos en forma de conjunto de tablas donde los bits superiores seleccionan filas y las de abajo columnas que permiten. Las memorias RAM estáticas son más rápidas pues permiten lo comentado, pero incluir esto en su interior necesita más espacio. 
	- En contra, las dinámicas (DRAM) se almacenan en un condensador, como este se descarga, hay que refrescarla. Tenemos entonces ciclos para lectura, ciclos para escritura y ciclos para refrescar antes de que pierda la carga. No tienen la capacidad de codificación de la SRAM y hay que pasarles lo que conocemos como rascas (row access stroke, column access stroke). Estas memorias son más lentas pero tienen más capacidad ya que necesitan menos espacio. Además de que no conviene menospreciarlas puesto que se han pasado por técnicas.

##### Mapa de memoria principal 

Totalidad del espacio de memoria que podemos direccionar, donde dependemos de la cantidad de memoria que podemos destinar del procesador, lo que tiene que ver con el ancho del bus de direcciones, el número de zócalos que posea la placa base multiplicado por el tamaño máximo con el que fabricamos los respectivos módulos y el rango de direcciones que permite manejar el controlador de la placa base.

La memoria está alineada a múltiplos de 4, cada dirección de memoria almacenaremos 1 byte y cada palabra empezará en una dirección múltiplo de 4.
##### Memorias entrelazadas

Para mejorar el comportamiento de las memorias tenemos diferentes técnicas, pudiendo organizar la memoria en elementos más autónomos llamados bancos. Estos nos permite accesos independientes entre distintas configuraciones.

Alternativas en el entrelazado:

- Podemos acceder a todos los módulos simultáneamente o acceder en instantes diferentes.

- Dar la misma dirección a cada módulo (entrelazado simple) o bien permitir direcciones diferentes (entrelazado complejo)

- Cada módulo con posiciones consecutivas (entrelazado de orden superior) o módulos consecutivos con posiciones consecutivas (entrelazado de orden inferior).

##### Memorias multipuerta

Merece la pena mencionarlas, que consisten en memorias de más de un puerto completo para direcciones datos y control, pueden cumplir más de una petición en cada ciclo, es una cuestión hardware que o bien se tiene o nada.
##### Fiabilidad y códigos de paridad



El análisis de la fiabilidad es que deben de ser fiables.

#### Sección 7.2 - Jerarquía de memoria cache

La memoria cache es más rápida y pequeña que el resto. Esta contiene las instrucciones y los datos recientes, además de los supuestos datos que vamos a usar a continuación. Si tenemos los datos en la cache, tardamos mucho menos que teniendo que tomar los datos de la memoria secundaria.

Cabe destacar que en la memoria cache no cabe toda la información, por lo cual tenemos que ir metiendo en ella lo que vamos usando. Si hay que traer información se trae por bloques, trayendo el bloque donde están los datos que queremos usar. 


> [!NOTE] Definición de memoria caché
> Es el primer nivel de la jerarquía de memoria tras los registros, su contenido es el subconjunto del contenido de la memoria principal. La cache se divide en bloques conocidos como líneas. La memoria principal se divide en bloques de igual tamaño que las líneas de caché. Se diseña basada en el principio de localidad.

Diseño basado en el principio de localidad:
- Localidad espacial: si un objeto es accedido, los objetos cercanos tienen gran probabilidad de ser accedidos en poco tiempo. 
- Localidad temporal: el objeto accedido tiene muchas probabilidades de volver a ser referenciado en un futuro cercano.
- Conjunto de trabajo (working set): ventana temporal para maximizar localidad
- Distancia de reutilización (reuse distance): nº de bloques que se acceden entre dos accesos consecutivos.

**Contenido de una línea de cache**

La cache se suele componer por contenido basura, que luego iremos validando para saber si dicho contenido es relevante o no. Cada entrada de la línea cache contiene la información del bloque, que son los datos, la etiqueta y este bit de validez.

**Políticas**

- Política de ubicación
- Política de sustitución
- Política de actualización

**Correspondencia directa**

Cada bloque de memoria se corresponde a una línea fija de la cache. Si por ejemplo tenemos un tamaño de palabra de 32 bits y un desplazamiento de 1 byte, necesitaríamos 2 bits. 

Vamos a poner un caso práctico teniendo en cuenta la siguiente tabla:


| Dirección de bloque              | Desplazamiento de bloque                                  |
| -------------------------------- | --------------------------------------------------------- |
| Etiqueta   \|   Índice de bloque | Desplazamiento de palabra    \|    Desplazamiento de byte |

- **Etiqueta** --> Sirve para verificar si el bloque buscado está o no en la cache.
- **Índice de bloque** --> Sirve para saber en qué bloque (línea) de cache debe estar en la información.
- **Desplazamiento de palabra** --> Son q bits que seleccionan la palabra dentro del bloque.
- **Desplazamiento de byte** --> Son p bits que seleccionan el byte dentro de la palabra.

Teniendo una memoria de 32 bits con 4 bits de ancho de palabra y un tamaño de 2 KiB, halla los correspondientes bits a cada unidad:

 - Para el caso del desplazamiento de byte, sabemos que 32 bits significan un desplazamiento de 2 bits.
 - Así, el desplazamiento de palabra supone unos 2 bits de igual forma.
 - El índice de bloque es una potencia de 2, lo cual tenemos que si 2 KiB es 2048 bits = 2^11. Entonces tenemos que 2^11/2^4 = 2^7 lo cual es 128. Por tanto, el índice de bloque es de 7 bits.
 - Finalmente, sumamos todos los bits dados anteriormente y lo restamos al tamaño general de 32 bits, quedando que la etiqueta se conforma por 32 bits.

Cuando direccionamos un objeto para buscarlo en la cache en pos de saber si está:
1. Identificamos la línea en la que hay que buscar -> m = Dirección de bloque módulo número de líneas de la cache.
2. Si el bloque es válido, continuamos, si no, FALLO
3. Se consulta la etiqueta del bloque almacenado en la línea m y si coincide con la etiqueta del que buscamos, ACIERTO, si no, FALLO

**Ventajas de la correspondencia directa**

- Ventajas(tiempo)
	- Simple, poco compleja y bajo consumo.
	- El hit time (tiempo de acceso con acierto) es rápido 
- Desventajas

**Memoria cache plenamente asociativa**

En este caso, cuando buscamos un objeto hemos de comparar la etiqueta del bloque accedido con todas las líneas válidas en paralelo. Si la etiqueta coincide pues es un ACIERTO, si no, FALLO.

- Ventajas: no tenemos conflictos
- Desventajas: se necesita un comparador para cada línea - coste muy elevado

**Cache asociativa por conjuntos**

Ahora, en vez de tener un índice de bloque, tenemos un índice de conjunto. Puesto que ahora las líneas se agrupan en ellos, cada uno con **n** líneas. Aquí tenemos que identificar el conjunto en el que hemos de buscar siendo m la dirección de bloque módulo. Así, comparamos la etiqueta del bloque buscado con todas las etiquetas válidas del conjunto m en paralelo. Si coincidimos ACIERTO, si no, FALLO.

**Comparación entre políticas de ubicación**

En la comparación directa, buscamos simplemente en uno, si no está en uno, pues nada, en los otros buscamos o en conjunto o de forma completa, lo cual puede aportarnos mayor flexibilidad y menor posibilidad de fallar en la búsqueda. Así, se puede resumir como que en la comparación directa buscamos en un bloque, en la plenamente asociativa buscamos exhaustivamente y la asociativa por conjuntos se limita al tamaño de dichos objetos.

**Grado de asociatividad**

Se podría considerar que toda memoria posee cierto grado de asociatividad. Si una memoria es totalmente asociativa, podríamos decir que por ejemplo es una memoria de conjuntos cuyo tamaño de conjunto es igual al completo del bloque, en su contrariedad, el inverso significaría muchos conjuntos de unidad mínima de dicho bloque.

**Política de reemplazamiento**

Cuando una cache plenamente asociativa está llena y hay un fallo, hemos de seleccionar un bloque para sustituirlo y meter el bloque, existen diversas formas:
- LRU -> Reemplazamos el bloque menos utilizado recientemente
- Random -> Reemplazamos aleatoriamente
- FIFO -> se reemplaza el bloque que lleva más tiempo en la cache
- LFU -> reemplazamos el bloque menos usado.

Estas políticas se usan también en caches asociativas por conjuntos si el conjunto seleccionado para la búsqueda está lleno. Por otro lado, dentro de las cache de correspondencia directa, sólo habría un candidato a ser reemplazado.

**Políticas de escritura**

Si escribimos solo en la cache y no en la memoria principal también tenemos una inconsistencia. Para solucionarlo podemos o bien escribir siempre en ambas, o escribir en retardo:
- Escribir en ambas -> Escritura a través (write-through). Lo malo es que las escrituras en memoria principal son lentas, pero para ello podemos usar un buffer de escritura que escriba de forma independiente en paralelo, pero si este buffer se llena, el procesador ha de parar. 
- Retardo -> las escrituras modifican el cache, no la mem principal. La línea de cache modificada sólo se escribe en memoria principal cuando hay que reemplazarla ante un fallo. Aquí necesitamos un bit de modificación en cada línea conocido como un bit sucio.

**Fallos de cache**

**Opciones para mejorar el rendimiento**

- Aumentar el tamaño de la cache, el grado de asociatividad, y el tamaño de bloque bajan los fallos, pero conllevan aumentar el tiempo de acceso y el coste para las dos primeras mejoras y la penalización de fallo para la última. 
- Reducir la penalización de fallo, aumentando el ancho de banda entre memoria cache y memoria principal, reduciendo así los accesos a memoria principal y escribir en mem principal mientras el procesador hace otras cosas. 
- Memorias cache separadas para instrucciones y datos dan mayor ancho de banda pero mayor tasa de fallos que una unificada.
- Memoria cache multinivel -> Conformada por una cache primaria diseñada para tener un tiempo de acierto muy bajo, una cache secundaria pensada para disminuir la tasa de fallos. Esta cache secundaria tendrá tamaño y tiempo de acceso mayores, y si hay fallo en ella, hemos de acceder a la mem principal. 

**Memoria principal frente a memoria cache**

Se suele acceder de la memoria a los buses de control que luego pasarán nuestros datos, se puede realizar de diversas formas, dejando más carga a los buses o aumentando el ancho de banda, lo cual reduciría la penalización de fallo. 

**Interfaz procesador - cache - memoria principal**

El procesador tarda un ciclo únicamente en acceder a la cache, mientras que la cache tarda múltiples ciclos en hacer un acceso a la mem principal. 

#### Sección 7.3 - Memoria virtual


> [!NOTE] Memoria virtual
> Espacio creado en disco para proporcionar a un proceso la ilusión de que tiene toda la memoria para él. Esto se hace para aliviar la carga de la memoria principal cuando hay un número exorbitado de procesos en ejecución.

##### Mapas virtuales

Cada proceso tiene su propio mapa virtual. El nivel más arriba de la jerarquía es la memoria principal y el menor es el disco duro. Es decir, podemos o bien traerlo de la zona imaginaria o bien usar la información si ya se encuentra donde la necesitamos. 

El mapa se divide en bloques llamados páginas, las unidades en las que dividimos estas páginas se conoce como marcos de páginas. Este reparto lo asigna el SO.

##### Proceso de traducción

Cuando un proceso aporta una dirección de memoria, el espacio virtual es mucho mayor que el espacio físico. Por ello, hemos de hacer un proceso de traducción entre espacios. Encontramos la página que deseamos y hemos de buscar en una dirección física el dónde alojarla.

Esto asegura una serie de cuestiones que nos son ventajosas. Son procesos sofisticados que realiza el SO.

##### Fallos de página

Puede suceder que queramos acceder a una información que todavía no está grabada en dirección física, lo que significaría un fallo de página.

El SO desaloja esto del procesador y deja que trabaje otro proceso.

##### Tabla de páginas

Una solución a nuestros fallos es esta. La tabla de páginas indexa la memoria:
- Una entrada por página virtual.
- Una TP por proceso activo.
- Reside en memoria (registro de tabla de páginas)
- Cada entrada tiene un bit de validez
	- 0 si la pág. no está en mem. principal.
	- 1 si la pág. es válida y la entrada contiene el número de pág. física
- No hay etiquetas
- La gestiona el SO

##### TLB - Translation Lookaside Buffer

Buffer de traducción de direcciones
	- Sólo contiene las correspondencias de tablas de páginas
	- Cada etiqueta contiene una parte del número de pág. virtual.
	- Cada campo de datos contiene un número de pág. físico.
	- Cada entrada tiene bit de referencia y bit de suciedad.

Básicamente es una caché especial para traducciones.

En cada referencia buscamos el número de página virtual en la TLB:

- Acierto: Se nos entrega directamente la dirección física asociada a una virtual.
- Fallo

**Ejemplo TLB**

Se realiza un acceso a un sistema que cuenta con una TLB y se sabe que se producirá un fallo de página. Completa el proceso en el orden correcto:

![[Pasted image 20240519012506.png]]



