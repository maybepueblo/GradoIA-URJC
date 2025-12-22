Esto que sirva a forma de un resumen general de toda la asignatura, recabando desde la teoría pura a las prácticas que hemos ido haciendo con Atauri en clase para poder.
# Introducción
## IoT
El Internet de las cosas o IoT es un paradigma donde objetos físicos equipados con sensores, actuadores y procesadores se interconectan mediante Internet para recopilar y compartir datos. Su objetivo principal es automatizar procesos, optimizar recursos y proporcionar servicios más eficientes.
## Definiciones sobre IACO
- **Inteligencia Ambiental**: Capacidad de entornos físicos para interacturar de forma adaptativa e inteligente con usuarios. Se logra mediante sensores, dispositivos conectados y procesamiento de datos en tiempo real, promoviendo eficiencia, comodidad y seguridad. 
- **Computación Ubicua**: Tecnología integrada en lo cotidiano, siempre disponible y accesible. Busca ofrecer experiencias naturales e intuitivas, como la comunicación entre personas. 
## Características de IACO
1. Sensible al contexto
2. Acceso ubicuo, inalámbrico y transparente
3. Interacción natural y no intrusiva
4. Comportamiento predictivo y adaptativo
5. Provisión de servicios en tiempo real, mejorando calidad de vida
6. Acceso independiente del dispositivo
## Aplicaciones posibles
- Domótica: Automatización del hogar
- Smart Cities: Gestión eficiente del tráfico, agua y residuos
- Salud: Teleasistencia, detectores de caídas y GPS para mayores
- Logística: Seguimiento en tiempo real mediante tecnologías como RFID y NFC
# Arquitecturas
## Conceptos básicos
Entendemos por arquitectura de un sistema los componentes que lo forman, sus funciones y cómo se relacionan entre ellos. Normalmente describimos estas arquitecturas en capas, cada una teniendo su función específica y sus propias formas de comunicarse con otros procesos de cada capa (protocolo).
## OSI (Open Systems Interconnection)
Marco de referencia de 7 capas para transmisión de datos:
1. **Física**; transmisión de bits
2. **Enlace de datos**; formación de tramas y correción de errores
3. **Red**: enrutamiento de paquetes
4. **Transporte**; División y control de errores de segmentos
5. **Sesión**; Gestión de conexiones
6. **Presentación**; Formateo y cifrado
7. **Aplicación**; Interacción con usuario

Cada capa añade info específica para una correcta llegada de los datos. 
### Capa física
Más baja del modelo OSI. Responsable de la conexión física a dispositivos. Esta contiene info en forma de bits. Así, se encarga de transmitir bits individuales de un nodo al siguiente. Al recibir datos, esta capa obtendrá la señal recibida, convirtiéndola en 0s y 1s para posteriormente enviarlos a la capa de enlace de datos, para repetir el proceso a la inversa.
## Arquitectura en IoT
- **Percepción (capa de enlace)**; Sensores y microcontroladores como ESP32 o Raspberry Pi
- **Transporte**: Protocolos red como BT, Zigbee o LoRa
- **Procesado**: Servicio en nube, web, centro de datos. 
- **Aplicación e interfaz**: Servicios finales adaptados al usuario, basados en contexto y necesidades.
### Capa de percepción/enlace (ampliación breve)
También conocida como capa de dispositivos, consta de múltiples elementos: sensores, cámaras, actuadores y dispositivos similares que recopilan datos y realizan tareas.

Por ejemplo, si tenemos un sensor en IoT utilizado en una cadena de montajes puede realizar una comprobación de control de calidad en un robot para verificar si este coloca el fusible de forma correcta detectando el código de colores de los distintos fusibles.

Estos sensores lo que hacen en verdad es convertir parámetros (como ambientales, la luz, temperatura, etc) en señales eléctricas que debe ser leída por un microcontrolador. Estos microcontroladores vienen de múltiples formas y pueden ser desde muy básicos a capaces de correr un sistema operativo
### Capa de transporte (breve correción)
- Tecnología **LAN**:
	- BlueTooth 
	- BTE 
	- Zigbee
- **WAN**
	- LoRa
- **GLOBAL**
	- 3G/4G
	- otros...
## Protocolos
- **Serie, I2C, SPI**: Conexiones locales
- **CAN-BUS**: Automoción diseñado por BOSCH, protocolo de bajo nivel y muy complejo que hace énfasis en la seguridad de las comunicaciones, la consistencia de los datos y la garantía de los tiempos de latencia. Todos los elementos electrónicos del coche se comunican por cable usando el protocolo (testigos, velocímetro, etc)
- **TCP/IP vs UDP**: TCP garantiza sesiones y control de errores mientras que UDP es más ligero y rápido
- **One Wire**
# Capa de percepción
## Raspberry Pi
Veamos lo que hace a este microcontrolador una opción tan interesante en el IoT:
- **Bajo coste y pequeño tamaño**: Ronda los 35 euros y tiene un diminuto tamaño que la hace extremadamente portátil
- **Versatil**: Puede ejecutar un gran rango de SO, como Raspi OS, Ubuntu Mate, Windows10 IoT, etc.
- **Conectividad**: Cuenta con excelentes opciones de conectividad como Ethernet, Wi-Fi y Bluetooth
- **Hardware**: Pines GPIO que le permiten conectarse e interactuar con todo tipo de sensores, motores, luces, pantallas y demás

**Pequeña intro a Vim** ``por si acaso``
Editor de texto cuya configuración se hace con un fichero oculto llamado .vimrc. Los Plugins en este editor de texto se instalan a través de Vundle, el cual tenemos que configurar dentro de este archivo oculto.
## Protocolo Serie
Surge en los años 60, transmite datos bit a bit a través de un cable mediante pulsos eléctricos y hay diferentes tipos del mismo, desde lo más antiguo y sencillo como RS232 a otro más moderno como el USB, el I2C o el SPI. 

Nace como alternativa a los problemas de sincro y cableado que ofrecía la comunicación en paralelo, modificando la manera de envío de los datos para hacerlo bit a bit por una misma línea de comunicación en lugar de varios bits a la vez por diferentes líneas. Paralelo si hay que enviar un byte se hace con 8 líneas y todos los bits de un byte se transmiten simultáneamente.
### Parámetros
- **Velocidad de transmisión/Baud rate**: Más distancia de transmisión = menor distancia entre elementos. Rango de 300 a 460800 baudios (más usados = 9600 y 115200)
- **Bits de datos**: Cantidad de bits en transmisión (5, 7, 8 bits como valores típicos)
- **Bits de parada**: Indican el fin de la transmisión, además de usarse para permitir tolerancia en la diferencia de sincronismo en relojes del equipo emisor y receptor (1, 1.5, 2)
- **Paridad**: Verifica si se han producido errores durante la transmisión. Hay cinco tipos: par, impar, marcada, espaciada y sin paridad. La paridad par e impar harán que el número de bits a 1 de la trama sea como la paridad indica, las paridades marcada y espaciada colocan el bit de paridad a 1 y 0 respectivamente. Se forma esta paridad con un único bit.
### Modos de transmisión
1. **Simplex** --> Unidireccional, sólo el emisor o el receptor están activos a la vez
2. **Half Duplex** --> Emisor y receptor activos pero no a la vez. Si emisor transmite, receptor recibe pero no puede enviar y viceversa. 
3. **Full Duplex** --> El emisor y receptor pueden enviar y recibir a la par
### Implementaciones principales
- **RS232**
	- Surge en los 60 pero sigue en uso en la industria, ya que es fiable. El estándar define un protocolo a nivel físico. Desde el conector hasta los niveles de tensión y el tiempo que deben de durar los flancos de subida y bajada. 
	- Full Duplex
	- Voltaje en rango de ±3 a ±15V
	- Máximo 15 metros
- **UART**
	- Universal Asynchronous Receiver Transmitter
	- Dispositivo que controla puertos y dispositivo serie. Integrado en la placa base o en la tarjeta adaptadora del dispositivo.
	- Encargado de recibir bytes y transformarlos a bits para su envío.
- **TTL**
	- Implementación de la transmisión en microcontroladores actuales UART, caracterizado por usar los niveles de tensión del microcontrolador (3.3V / 5V) y lógica inversa a RS232
### Diferencias RS232 y TTL
- Susceptible a condiciones externas
	- El voltaje del RS232 ayuda a que sea menos susceptible al ruido, las interferencias y la degradación.
- Min y max voltajes
	- Las tensiones de las señales RS232 son +/-13V y de 0 a 3,3/5V en el TTL
- Microcontrolador
	- TTL > RS232 
- Niveles lógicos
	- Están invertidos
## Serialización de Datos
Proceso de convertir estructuras de datos u objetos complejos en un formato almacenable, transmitible o fácil de compartir entre sistemas, plataformas o lenguajes. Nos permite representar datos como un flujo de bytes que luego se puede reconstruir a su forma original gracias a la deserialización.

Dos categorías principales:
1. **Formatos de texto** (JSON, XML)
2. **Formatos binarios**

El puerto serie envía y recibe arrays de bytes por lo que en muchas ocasiones tendremos que transformar los datos antes de enviarlos y después de recibirlos. Si tratamos de enviar algo que no es, nos saltará un error.
### Formatos binarios
- Menor tamaño
- Más eficientes
- Mejor soporte para datos complejos
- Mayor seguridad
### Métodos de serialización `librería struct para Python`
- Strings a binarios con encode() 
- Números y booleanos con structs
- Objetos/diccionarios con JSON o struct 
### Formatos de texto
- **XML**
	- Ampliamente adoptado para intercambiar y almacenar datos. Se usan etiquetas para definir la estructura de los datos y admite estructuras jerárquicas complejas. Es flexible pero más verborreico/verboso que otros formatos.
	- Surge a finales de los 90 como sucesor de SGML, buscando ser flexible y estándar al estructurar e intercambiar datos. Sin embargo, la complejidad y verbosidad da lugar a cargas sobredimensionadas y por ende, menos eficaz para transmitir por redes o almacenar en bases de datos.
- **JSON**
	- Ligero y legible usado para intercambiar datos entre servicios web y apps. Representa datos como pares clave-valor y admite tipos básicos como cadenas, números, booleanos, matrices y objetos.
	- Superior a XML por simpleza, compacidad y soporte nativo en JS. 
	- Errores comúnes:
		- Errores de sintaxis -> Sintaxis demasiado estricta
		- Limitaciones en tipos de datos -> Conj. extenso de fábrica pero requiere manipulación para añadir estructuras complejas.
		- Mayor tamaño que los formatos binarios.
## One Wire
Si con TTL y RS232 podemos conectar un dispositivo a un mc. Algunos ejemplos que funcionan con dicho protocolo son receptores de GPS o routers. Lógicamente un sistema no suele tener más de un dispositivo de este tipo, y si quisiese 2 necesito una UART para cada uno. Así, en muchos casos querré pinchar más de un dispositivo al mismo puerto. Esto lo permiten protocolos como I2C o OneWire

### Características y componentes básicos
1. Protocolo HalfDuplex que transporta datos y alimenta a los dispositivos que se conecten al bus por medio de una única línea o cable y tierra.
2. Acepta solamente un maestro en el bus y uno o más esclavos, es por tanto, multipunto.
3. El protocolo incluye direccionamiento. Todos los dispositivos de dicha MicroLan debe de tener un ID de 64 bits codificado en la misma.

Tenemos dos tipos de bus serie: con línea de reloj dedicada o sin ella. 

Como ejemplo del primer tipo tenemos el SPI o el I2C, con una línea para datos y otra para sincronización. La ventaja es que la transmisión es más simple, más rápida y más fiable. Pero necesitamos un cable extra para el reloj.

No es problema para estos buses pero si solo tenemos un canal y no hubiera forma de tener señal de reloj en paralelo, no nos queda otra que hacer que la línea cambie de cuando en cuando siguiendo un patrón para que el receptor pueda ajustar su reloj y no se pierda. Las codificaciones que en cada bit cambian una vez se llaman Self Clocking. 

Tenemos cinco componentes básicos en el One Wire: 
1. **Presencia o reset**; Llevamos al bus a bajo durante 480/600 microsegundos. El condensador se descarga y como resultado todos los devices se reinician. Luego libera la línea y esta vuelve a alto. Los esclavos OneWire (OW) esperan un momento y llevan al bus a nivel bajo entre 60/240 us. Así se determina que hay al menos un elemento conectado. 
2. 3. **Escribir 0/1**; Código morse. Para un dato el máster lleva a cero el bus. Entre 1/15 us = 1s, si no, entre 60us es 0s. 
4. **Leer 0/1**; Se envía un pulso y se muestrea. Si el chip quiere enviar un 1, no hará nada. Si es 0, mantendrá la línea durante unos 15us
5. **CRC**
	- ¿Qué pasa si el protocolo falla? Pues que podríamos enviar o recibir datos erróneos, pero hay formas de detectarlo. 
	- No se usa aquí pero es el bit de paridad la más sencilla. En una transmisión serie, se usa. Se fuerza a que el número de unos sea par o impar añadiendo un bit a 1 o a 0 según haga falta. Al recibir el byte, se comprueba que el número de unos corresponde a lo acordado y si no, pues error. 
		- Sólo permite detectar un número impar de errores
## Interfaces de usuario
En IoT, han de ser sencillas, cuanto más, mejor.

En muchas ocasiones un dispositivo está en entorno hostil: fábricas, intemperie, etc. Además de que muchos tienen que ser MUY baratos y el hardware para interfaces es caro y frágil. Lo más común por tanto, es reducir las interfaces a unos pocos botones, algunas señales luminosas, pitidos, etc.

Para casos más complejos, una buena solución es conectar el mc al móvil mediante bluetooth, un web/socket y usar el móvil como interfaz.
## I2C (Inter-IC)
Abreviatura de Inter-IC es un tipo de bus diseñado por Philips Semiconductors a principios de los 80s, que utilizamos para conectar circuitos integrados. Es un bus que permite conectar varios chips al mismo bus. Utiliza el modelo maestro/esclavo. Se utiliza además dentro de una misma placa de dispositivo para conectar diferentes componentes como memorias o pantallas.
### Características
- Bus multimaestro-multiesclavo
- Dos cables, uno de reloj (SCL) y otro de datos (SDA)
- Direccionamiento de 7 bits
- Pull-up en SDA
### Conexión
Como se comentaba antes, usa dos cables para intercambiar info. Uno se utiliza para el reloj y otro para enviar y recibir los datos. Este hecho soluciona los problemas de sincro que vimos en One Wire y permite que la comunicación sea más rápida. SDA en reposo estará en nivel alto (pull-up). Además de SCL y SDA tenemos GND y Vcc.
### Protocolo de comunicación
- Condición inicial: bus libre que significa que estén ambas señales en alto
- Secuencia
	- Condición de inicio
	- Dirección del dispositivo a seleccionar (7 bits y octavo para la operación de lectura/escritura)
	- Bit de reconocimiento que indica al maestro que el esclavo reconoce la solicitud y está en condiciones de comunicarse.
	- Transmisión de datos
	- Condición de parada
# Capa de Transporte

## Conexión inalámbrica
Para esto existen varios protocolos, los más típicos son wifi, bluetooth y bluetooth low energy (BLE). Aunque existen otros como Zigbee (IEEE 802.15.4), LoRaWAN y LTE-M, seguido de Narrowband, NB-IoT y la quinta generación de red celular (5G)
### Factores principales
- **Alcance**: Influida por obstáculos. No es lo mismo un proyecto instalado en una vivienda que a campo abierto. 
- **Consumo**: Vital importancia para proyectos con baterías
- **Ancho de banda**

Es común tener que lidiar con redes de rango amplio caracterizadas por subredes con rangos más pequeños basados en protocolos que ahorren energía. Por ende, puede clasificar los protocolos antes mencionados en su rango de cobertura típico y en sus casos de uso y aplicación. Se pueden llegar a dividir en tres clasificaciones principales;
- Comunicación de corto alcance
- Comunicación de rango medio
- De largo alcance
Existen un gran número de protocolos de comunicación para crearte una red de área personal (WPAN) que tenga un alcance de pocos metros hasta 50m. El más usado es el bluetooth, en su forma clásica para transferencias de datos síncronas o BLE para redes multinodos de baja potencia.

Tienen estos una topología típica en estrella, pero en casos de IoT a veces se usan redes en malla, por ejemplo en detectores de incendio en un bosque. 
## WiFi
Transmite información por el aire con ondas de radio, que son un tipo de radiación electromagnética con longitudes más largas que la luz infrarroja. 

Las ondas WiFi tienen frecuencia de entre 2.4 GHz a 5GHz. Estas dos bandas se subdividen en múltiples canales, siendo cada canal compartido por varias redes. Así, al descargar los datos a través de WiFi, un router inalámbrico recibe los datos de Internet a través de banda ancha para luego convertirlo a ondas de radio. Entonces emite las ondas al área circundante y el dispositivo inalámbrico que ha iniciado la solicitud las captura y las decodifica.

Este envío se consigue a través de la modulación de la señal portadora. Básicamente esta consiste en hacer que un parámetro de la onda cambie de valor de acuerdo con las variaciones de la señal moduladora.

Nuevamente el WiFi presenta una topología en forma de estrella, teniendo un dispositivo conocido como el Punto de Acceso al que se conectan todos los otros dispositivos.

Está montado sobre TCP/IP, así que cada dispositivo tiene una dirección IP determinada por el AP, y el direccionamiento se realiza a través de estas. 
### Ventajas e inconvenientes
- **Ventaja**
	- Alta capacidad de transmisión (11-300 Mbit/sg)
	- Baja latencia
	- Rango operativo
- **Inconvenientes**
	- Alto consumo de energía
## MAC
En ordenadores, la MAC es un identificador de 48bits (6 bloques de dos caracteres hexadecimales) que corresponden de forma única a una tarjeta o dispositivo de red. Es también conocida como dirección física y es única para cada dispositivo.

Se determina y configura en base al IEEE y el fabricante. La mayoría de protocolos de la capa 2 del OSI, usan una de las tres enumeraciones manejadas por el IEEE: MAC-48, EUI-48 y EUI-64.

Son únicas a nivel mundial, lo que las diferencia de las ip's que son cambiantes, con lo cual la MAC sí que nos sirve para identificar en un proyecto a x dispositivo de forma permanente
## BlueTooth (BT) y BlueTooth Low Energy (BLE)
Primero que todo, sabemos que no son iguales. Estos no son compatibles entre sí. Algunos dispositivos antiguos sólo tenían uno de estos, la mayoría a día de hoy tienen ambos.

BLE está pensado para:
- Transmisión de pequeñas cantidades de datos
- Bajo consumo de energía
- Permanece en modo suspensión excepto durante la conexión
### Arquitectura Cliente-Servidor
- ESP32 funciona como ambos
- Servidor anuncia su presencia para que otros dispositivos lo identifiquen
- Los clientes lo detectan y pueden conectarse a este servidor.

Nos centraremos en una comunicación punto a punto, pero existe también la red de malla y la de emisor.
### Estructura de protocolo BLE
1. Perfil (nivel más alto)
2. Servicio (colección de información) -> Puede o no, estar centrado en múltiples sensores. Si hay varios sensores, habría tantos servicios como sensores.
3. Características (datos reales) 
4. Propiedades-Valores-Descriptores
## LoRa
Tecnología de comunicación inalámbrica para IoT, similar a Sigfox, optimizada para enviar pequeñas cantidades de datos a largas distancias con bajo consumo. Es una red LPWAN (Low Power Wide Area Network)
### Distinción LoRa y LoRaWAN
- LoRa es la tecnología de modulación de radio que usa Chirp Spread Spectrum (CSS) patentada por Semtech
- LoRaWAN es el protocolo de red que usa LoRa como base

Así LoRaWAN es el protocolo de comunicación de largo alcance usado a menudo para crear redes de área amplia de bajo consumo con un alcance operativo de entre 300m a 10km. Entre los principales protocolos LPWAN, este es de los más usados. 

A hablar de LoRa y LoRaWAN tenemos que especificar que ambos términos son diferentes: LoRaWAN es un protocolo cuya capa PHY se basa en modulación LoRa mientras que la capa de Control de Acceso al Medio (MAC) es una arquitectura de red abierta regulada por LoRa Alliance. LoRa en cambio está basada en CSS que se refiere a la capa física. LoRa está patentada por Semtech, el cuál es el único productor de chips transceptores LoRa. 

Por ende, en pila de protocolos OSI, LoRaWAN (capa de red) se basa en LoRa (capa física) como se ve a continuación:

Otra diferencia más es la topología de red, ya que LoRa solo permite enlaces punto a punto mientras que LoRaWAN define todas las reglas para crear una topología de múltiples estrellas compuesta por muchos nodos finales LoRaWAN y gateways. 
### Modulación
LoRa modula símbolos en bloques en los que aumenta o disminuye la frecuencia de la señal portadora. Estos bloques se llaman chirps: up-chirps y down-chirps. 

Esta modulación tiene muchos parámetros. Algunos son:
- **Frecuencia portadora** Depende de la región operativa
- **Ancho de banda** Generalmente establecida en 125 kHz pero puede llegar hasta 250 kHz o incluso 500 kHz
- **Factor de propagación** Define cuantos chirps se envían por segundo. Valor grande es igual a más tiempo en el aire el símbolo y más gasto energético. Esto mejora el rango, pero reduce la velocidad de los datos disponibles y el tamaño de la carga útil de mensajes.
- **Potencia de transmisión** Energía irradiada por la antena. Puede variar desde -4 dBm hasta 20 dBm, pero distintas regiones pueden tener diferentes límites de potencia. 
- **Sync Word** Diferenciación de LoRas que usan las mismas bandas de frecuencia
### Ventajas LoRa  
LoRa es una tecnología destacada para aplicaciones de IoT debido a sus numerosas ventajas:

- **Alta tolerancia a las interferencias**: Garantiza una comunicación estable incluso en entornos con ruido.
- **Bajo coste**: Las infraestructuras y radios para dispositivos finales son económicas en comparación con otras redes.
- **Alta sensibilidad**: Capaz de recibir datos con una sensibilidad de hasta -168 dB.
- **Conexión punto a punto**: Permite una comunicación directa y exclusiva entre dos dispositivos.
- **Bajo consumo de energía**: Diseñada para operar con poca energía, prolongando la vida útil de las baterías y reduciendo la intervención humana.
- **Largo alcance y cobertura**: Funciona en entornos urbanos y rurales, con un alcance teórico de hasta 20 km en zonas abiertas.
- **Alta capacidad**: Un único gateway puede conectar miles de dispositivos, escalable con la adición de más gateways.
- **Frecuencias de trabajo**: Opera en bandas sin licencia (433 MHz en Asia, 868 MHz en Europa, 915 MHz en América), menos saturadas y con mejor propagación.

Estas características hacen de LoRa una tecnología ideal para aplicaciones IoT que requieren largas distancias y dispositivos sin conexión eléctrica directa.
### Cómo utilizar LoRa  
Existen dos opciones principales para implementar LoRa en proyectos IoT:
1. **Crear una red propia**: Implica adquirir chips LoRa y desarrollar gateways y nodos. Ofrece flexibilidad pero requiere mantenimiento.
2. **Utilizar un operador de red**: Contratar servicios de conectividad LoRaWAN con operadores, evitando el mantenimiento propio, aunque con el riesgo de que el operador retire el servicio.

Además, existen:
- **Comunidades abiertas**: Desarrolladas por comunidades de entusiastas.
- **Redes privadas**: Utilizadas en aplicaciones como ciudades inteligentes, agricultura y logística.
- **Redes de operadoras**: Servicios pagados ofrecidos por operadores de telecomunicaciones que integran LoRaWAN con sus servicios tradicionales.
### LoRaWAN

LoRaWAN es un protocolo LPWAN diseñado para conectar dispositivos IoT mediante la tecnología LoRa. Define la arquitectura de red y el protocolo de comunicación, permitiendo la gestión de la infraestructura.

A diferencia de otras tecnologías como 3G, 4G, WiFi, Bluetooth, NB-IoT o SigFox, LoRaWAN destaca por su adaptabilidad en escenarios donde las redes móviles y WiFi no son óptimas. Es ideal para proyectos IoT que requieren bajo consumo de energía y transmisión de pequeños volúmenes de datos.

LoRaWAN gestiona el enrutamiento entre gateways y nodos finales. Su especificación inicial (versión 1.0) se presentó en junio de 2015, consolidándose como una solución robusta para redes IoT de largo alcance y baja potencia.
## udpSocket
A veces necesitaremos enviar secuencias de datos a otros dispositivos y un mensaje de MQTT o una consulta http no es eficiente. Por ejemplo, si queremos muestrear un parámetro cientos o miles de veces por segundo y queremos enviarlo a un pc para procesarlos o graficarlos allí ya que el mc no tiene recursos suficientes. 

Una posible solución sería el puerto serie, pero ha de ser cableado. Si queremos que sea inalámbrico podríamos usar BT y otra posibilidad si tenemos WiFi es un socket.

Los sockets UDP (no como los websockets) no tienen sesiones y son más sencillos y rápidos. Tienen un cliente y un servidor y el mayor problema quizá es conocer la IP del server. Pero cada proyecto se puede adecuar a esto de forma efectiva

Si bien todo suena muy bonito, porque puede teóricamente alcanzar velocidades cercanas incluso a 1 GB/s, no garantiza la entrega, así que en redes congestionadas podrías experimentar pérdidas de paquetes, afectando la transmisión.
# Capa de procesamiento
## MQTT
También conocido como Message Queuing Telemetry Transport, es un protocolo de mensajería ligero y eficiente diseñado para dispositivos con recursos limitados, como los de IoT. Se desarrolló en 1999 para la industria del petróleo y el gas, y se ha convertido en un estándar clave para la comunicación en IoT.

Es simple, escalable y capaz de operar en redes de bajas potencia, lo que contribuye a su éxito continuo.  Se inventó pensando en un protocolo con el ancho de banda mínimo y una pérdida de batería mínima, pero mejoró a lo que es actualmente. 
### Funcionamiento de MQTT
- **Modelo publicación/subscripción** Los clientes publican mensajes en un broker (agente) y se suscriben a temas específicos para recibir esos mensajes.
	- Desacoplamiento espacial: el editor y el suscriptor no conocen la ubicación de la red del otro y no intercambian información como sus IP o números de puerto
	- Desacoplamiento de tiempo: editor y suscriptor ni tienen conectividad de red al mismo tiempo.
### Componentes de MQTT y proceso de conexión: Clientes y Agentes
- Cliente MQTT: Puede ser editor (envía mensajes) o un suscriptor (los recibe)
- Broker MQTT: Coordina la comunicación entre clientes, filtrando y distribuyendo mensajes.
### Proceso de conexión
Los clientes inician la conexión al enviar un mensaje de CONECTAR al broker. Este confirma la conexión establecida con mensaje CONNACK. Requieren de TCP o IP para comunicarse.

Destaca esta arquitectura controlada por eventos gracias a su capacidad para gestionar mensajes de tamaño reducido y claramente definidos. Introduce el concepto de Calidad de Servicio con niveles 0, 1 y 2, adaptando entregas a necesidades específicas
### Beneficios
- **Ligero**: Encabezado de mensaje de 2 a 5 bytes.
- **Altamente compatible**
- **Confiable**: Tres niveles de Calidad de Servicio
	- Nivel 0 (lanzar y olvidar): Se envía el mensaje una vez sin esperar confirmación, lo que reduce el ancho de banda.
	- Nivel 1 (entregado al menos una vez): Debe confirmar el cliente la entrega. Se asegura que los mensajes se entregan al menos una vez
	- Nivel 2 (entregar sólo una vez): Nivel más demandante pero más confiable, ya que esperamos a que el cliente confirme antes de volver a enviar otro mensaje, borrando la posibilidad de duplicados.
- **Seguridad**: Soporta autenticación y cifrado pero no vienen por defecto
- **Abierto**
### Limitaciones
- No tiene cifrado ni autenticación por defecto, lo que hace que el mensaje corra el riesgo de ser interceptado y que tengamos que manipular para poder darnos ese extra necesario de seguridad.
## TinyML
Rama de ML enfocada en implementar y diseñar modelos de aprendizaje automático para dispositivos embebidos como Raspi, Arduino y ESP32. Al tener estos dispositivos limitaciones de energía y capacidad de cómputo, se utilizan librerías especializadas.
## Consumo 
Si queremos alimentar un mc con batería es importante aprender a dormir al dispositivo durante largos periodos de tiempo o la batería se agotará muy rápido. 

OJO!!! Cuando el dispositivo está dormido el ordenador no encuentra el puerto USB. Por ello, si no tenemos cuidado y dormimos el ESP nada más arrancar podemos inutilizarlo ya que no podríamos volver a programarlo.

Algunas soluciones a esto son:
- Esperar un tiempo prudente en la función setup antes de dormir
- Dormirlo en una función que chequee el valor de un pin y no lo duerma si está a 0V. Conseguiremos V uniendo el pin con un cable a tierra. Si le ponemos el cable evitamos que se duerma, si lo quitamos se podrá dormir. 

Para leer el consumo podemos usar un medidor USB. Aunque el problema no es tanto el cúanto consumen en el momento sino que no tenga el dispositivo un modo de bajo consumo, por ejemplo, la Raspberry Pi no tiene, pero la ESP sí. 
### Demás cosas
- **TCP/IP**: Protocolo más usado en internet: http y ssh. **UDP** es más ligero, sin sesiones ni control de errores. **Web socket (tcp) y socket (udp)**: si te importa la integridad de los datos TCP y si es la velocidad, UDP.
- El **puerto de serie no necesita sesión**, no hace falta que los dos estén arrancados para que se envíen las cosas.
- **NFC** es el protocolo inalámbrico con el enlace más corto.
- **MQTT** es solo mensajería, **no se almacenan valores**.
- **Pull Up** es que está a 5 voltios.
- Android tiene una medida de seguridad que hace que su **MAC sea dinámica por BLE**, así que no se puede identificar de quién es el móvil. No se puede usar el esp, pero la raspi si tiene bt además de ble.
- Al **conectar 2 raspi por serie**, que lo q salga por tx entre por rx tienen que estar **conectadas a la misma tierra**.
- La librería **one wire** de arduino está **desactualizada** y no funciona con los xiao.
- Alimentar el esp con baterías hay q dormirlo. Si se duerme no se encuentra por usb. **No se puede dormir el esp nada más arrancar** pq si no no se podrá volver a programar.
- El **gpio 2** es un pin configurable para entrada o salida.
- **Zigbee** pequeñas cantidades de datos en distancias cortas.
# Resumen Protocolos:
## Por cable:
### Un solo dispositivo:
- **RS232:** máquinas de producción o sitios con ruido.
- **TTL:** sensores.
### Varios al mismo cable:
- **One Wire**: un solo maestro y chill.
- **I2C**: varios maestros y más rápido.
## Inalámbrico: 
### Distancias Largas:
- **LoRa**.
### Distancias Cortas/Medias:
#### Mucho ancho de banda:
- **Wifi**: streaming de video y archivos tochos.
- **MQTT**: muchos nodos y con eficiencia energética.
#### Menos ancho de banda:
- **Bluetooth**: Sonido, control remoto y transferencias locales.
- **BLE**: que consuma poca energía. Wearable y sensores con notificación. 
- **Zigbee**: no requiere de un dispositivo central y va duro con redes de maya. Redes IoT a gran escala 10/100m.
- **NFC**: seguridad y rapidez. Pagos, autentificación y emparejamiento rápido.