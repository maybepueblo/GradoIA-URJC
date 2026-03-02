#### Protocolo Serie

##### Datos breves
- Surgido en los años 60
- Transmite datos bit a bit a través de un cable
- Hay diferentes tipos de este, desde lo más antiguo y sencillo como RS232 a otro más moderno como el USB, el I2C o el SPI.

##### Parámetros
Estas conexiones por serie se definen en base a cuatro parámetros:
- Velocidad de transmisión (baudios): A mayor distancia de transmisión, menor distancia entre elementos. Rango de 300 a 460800 baudios, pero las más usadas son las de 9600 y la de 115200.
- Bits de datos: cantidad de bits en la transmisión. Como valores típicos están el 5, 7 y 8.
- **Bits de parada**: Indican el fin de la transmisión además de usarse para permitir tolerancia en la diferencia de sincronismo en relojes del equipo emisor y receptor. (1, 1.5, 2)
- **Paridad**: Verifica si se han producido errores durante la transmisión. Hay cinco tipos: par, impar, marcada, espaciada y sin paridad. La paridad par e impar harán que el número de bits a 1 de la trama sea como la paridad indica, las paridades marcada y espaciada colocan el bit de paridad a 1 y 0 respectivamente. Se forma esta paridad por un único bit.

##### Modos de transmisión
1. **Simplex** --> Unidireccional, sólo el emisor o el receptor están activos a la vez.
2. **Half-Duplex** --> Ambos activos pero no a la vez. Si el emisor transmite, el receptor recibe pero no puede enviar y viceversa. (bidireccional alternado)
3. **Full-Duplex** --> El emisor y el receptor pueden enviar y recibir a la par (bidireccional simultáneo)
##### Implementaciones principales

- **RS232** 
	- Surgió en los 60 pero sigue en uso sobretodo de forma industria, ya que es fiable. El estándar define un protocolo a nivel físico. Desde el conector hasta los niveles de tensión y el tiempo que deben durar los flancos de subida y bajada. 
	- Es **Full Duplex**
	- Voltaje en el rango de ±3 a ±15V
	- Máximo 15 metros
- **UART**
	- Universal Asynchronous Receiver Transmitter
	- Dispositivo que controla puertos y dispositivos serie. Integrado en la placa base o en la tarjeta adaptadora del dispositivo. 
	- Encargado de recibir bytes y transformalos a bits para su envío.
- **TTL**
	- Implementación de la transmisión en los microcontroladores actuales UART, caracterizado por usar los niveles de tensión del microcontrolador (3.3/5V) y lógica inversa a R232.

###### Diferencias RS232 vs TTL
- Susceptible a condiciones externas
	- El voltaje del RS232 ayuda a que lo sea frente al ruido, interferencias y degradarse. 
- Min y max voltajes
	- Son de +/- 13 V y de 0 a 3.3/5 V respectivamente
- Emparejar con un microcontrolador
	- TTL > RS232 para este ámbito
- Niveles lógicos
	- Están invertidos entre estas dos implementaciones

#### Serialización de Datos

Proceso de convertir estructuras de datos u objetos complejos en un formato almacenable, transmitible o fácil de compartir entre sistemas, plataformas o lenguajes. Nos permite representar datos como un flujo de bytes que luego puede reconstruirse a su forma original mediante deserialización.

Dos categorías principales:
1. **Formatos de texto** (JSON, XML)
2. **Formatos binarios**
##### Formatos binarios
- Menor tamaño
- Mayor eficiencia
- Mejor soporte para datos complejos
- Mayor seguridad
##### Métodos de serialización
- Strings a binario con encode()
- Números y booleanos con structs
- Objetos/diccionarios con JSON o struct
##### Formatos de texto

- **XML**
	- Ampliamente adoptado para el intercambio y almacenamiento de datos. Utilizamos etiquetas para definir la estructura de los datos y admitir estructuras jerárquicas complejas. Es más flexible pero más prolijo que otros formatos.
	- Surge a finales de los 90 para suceder a SGML. Sin embargo, la complejidad y verbosidad de XML da lugar a cargas de datos sobredimensionadas, lo que lo hace menos eficaz para transmitir por redes o almacenar en bases de datos.
- **JSON**
	- Ligero y legible para intercambiar datos entre web y aplicación. Representa datos como pares clave-valor y admite tipos de datos básicos como cadenas, números, booleanos, matrices y objetos.
	- Se considera superior a XML por su simpleza, compacidad y soporte nativo en JavaScript. 
	- Aun así, tiene ciertos errores comúnes:
		- Errores de sintaxis -> Sintaxis demasiado estricta
		- Limitaciones en tipos de datos -> Conjunto extenso de fábrica pero requiere manipular para poder añadir estructuras un poco más complejas.
		- Mayor tamaño comparado con formatos binarios

#### One Wire

Es un protocolo diseñado para conectar múltiples dispositivos a un único puerto.

##### Características
1. Es Half Duplex, transporta datos y alimenta a los dispositivos que se conecten al bus por medio de una única línea o cable y tierra.
2. Acepta solamente un maestro en el bus y uno o más esclavos, por lo que se dice que es multipunto. 
3. El protocolo incluye un sistema de direccionamiento. Cada dispositivo de la MicroLan debe tener un ID de 64 bits codificado en la misma

##### Componentes básicos

*Siendo "us" microsegundos*

Con One Wire, tenemos cinco componentes básicos:
1. **Presencia o reset**: Master lleva a bus a nivel bajo entre 480 y 600us. El condensador se descarga y como resultado todos los dispositivos conectados se reinician. Acto seguido el máster libera la linea y esta vuelve a nivel alto. Los esclavos One Wire al iniciarse esperan un momento y llevan el bus a nivel bajo entre 60 y 240us. Así, el master determina que tenemos al menos un elemento conectado.  
2. 3. **Escribir 0 y escribir 1**: Código morse. Para un dato máster lleva a cero el bus brevemente. Si es un poco más de 1us y hasta 15us el receptor interpreta un 1s. Si es más largo, 60us, el receptor interpreta un cero.
4. **Leer 0 y 1**. El master envía un pulso y muestrea. Si el chip quiere enviar un 1, no hará nada. Si es 0 lo que quiere comunicar, mantendrá la línea durante unos 15us.
5. **CRC**: Verificar errores en el protocolo para evitar el envío de datos erróneos.
 
#### Interfaces de usuario

Cuanto más sencillas, mejor. En muchas ocasiones los dispositivos están en condiciones hostiles como las fábricas, al intemperie... Pueden estar bajo sol, lluvia, llenos de polvo y vibraciones.

Muchos dispositivos además han de ser barato y el hardware dedicado a interfaces es caro y susceptible a estropearse. Lo más común entonces es que estas interfaces se reduzcan a un par de botones, algunas señales luminosas, pitidos y minúsculas pantallas. 

En casos más complejos es más eficiente conectar el microcontrolador a un móvil mediante bt, socket o websocket, para usar el móvil como interfaz.

#### I2C (Inter-IC)

##### Características
- Bus multimaestro-multiesclavo
- Usa dos cables: SCL (reloj) y SDA (datos)
- Direccionamiento de 7 bits
- Pull-up en SDA

##### Procotolo de comunicación 
- Condición inicial: bus libre (ambas señales en alto)
- Secuencia
	1. Condición de inicio
	2. Dirección del dispositivo (7 bits)
	3. Bit de lectura/escritura
	4. Bit de reconocimiento (ACK)
	5. Transmisión de datos
	6. Condición de parada

##### Particularidades
- Direcciones no únicas entre dispositivos
- Permite múltiples dispositivos del mismo tipo
- Ampliamente usado en sensores y pantallas
- Soluciona problemas de sincronización
- Mayor ancho de banda que otros protocolos

