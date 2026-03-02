
#### Conexiones inalámbricas

Todo lo hecho hasta el momento ha sido cableado, a continuación veremos como preparar entornos inalámbricos. Estos son algunos protocolos:

Para esto existen varios protocolos, los más típicos son wifi, bluetooth y bluetooth low energy (BLE) aunque existen otros como ZigBee (IEEE 802.15.4), protocolo LoRaWAN y LTE-M, seguido de Narrowband, protocolo (NB-IoT) y la quinta generación de red celular (5G).

##### Factores principales
- **Alcance**: Influida por obstáculos. No es lo mismo un proyecto instalado en una vivienda que a campo abierto.
- **Consumo**: Vital importancia para proyectos con baterías.
- **Ancho de banda**

##### Topología de redes

![[Pasted image 20250118174648.png]]

##### Tecnología Wi-Fi
- Ondas de frencuencia de 2.4GHz a 5GHz. Se subdividen estas bandas en múltiples canales, siendo cada canal compartido por muchas redes diferentes.
- Un dispositivo (router) recibe los datos de Internet y los convierte en ondas de radio. Así, este emite las ondas al área circundante y el dispositivo inalámbrico que inició la solicitud de descarga las captura y las decodifica
- Modulación: consiste en hacer que un parámetro de la onda portadora cambie de valor concorde a las variaciones de la señal moduladora, que es la información a transmitir.
- Topología de estrella, teniendo un dispositivo llamado **Punto de acceso** al que se conectan el resto de dispositivos.
- TCP/IP: cada dispositivo conectado tiene una dirección IP, determinada por el PA y el direccionamiento se realiza a través de estas. 

##### Ventajas e inconvenientes
- **Ventaja**
	- Alta capacidad de transmisión (11-300 Mbit/sg)
	- Baja latencia
	- Rango operativo
- **Inconvenientes**
	- Alto consumo de energía

#### MAC
En ordenadores, la MAC es un identificador de 48bits (6 bloques de dos caracteres hexadecimales) que corresponden de forma única a una tarjeta o dispositivo de red. Es también conocida como dirección física y es única para cada dispositivo.

Se determina y configura en base al IEEE y el fabricante. La mayoría de protocolos de la capa 2 del OSI, véase [[Tema 2 - Arquitecturas]], usan una de las tres enumeraciones manejadas por el IEEE: MAC-48, EUI-48 y EUI-64.

Son únicas a nivel mundial, lo que las diferencia de las ip's que son cambiantes, con lo cual la MAC sí que nos sirve para identificar en un proyecto a x dispositivo de forma permanente
#### BlueTooth (BT) y BlueTooth Low Energy (BLE)
Primero que todo, sabemos que no son iguales. Estos no son compatibles entre sí. Algunos dispositivos antiguos sólo tenían uno de estos, la mayoría a día de hoy tienen ambos.

BLE está pensado para:
- Transmisión de pequeñas cantidades de datos
- Bajo consumo de energía
- Permanece en modo suspensión excepto durante la conexión

##### Arquitectura Cliente-Servidor
- ESP32 funciona como ambos
- Servidor anuncia su presencia para que otros dispositivos lo identifiquen
- Los clientes lo detectan y pueden conectarse a este servidor.

Nos centraremos en una comunicación punto a punto, pero existe también la red de malla y la de emisor.

##### Estructura de protocolo BLE
1. Perfil (nivel más alto)
2. Servicio (colección de información) -> Puede o no, estar centrado en múltiples sensores. Si hay varios sensores, habría tantos servicios como sensores.
3. Características (datos reales) 
4. Propiedades-Valores-Descriptores

![[Pasted image 20250118183907.png]]

#### LoRa
Tecnología de comunicación inalámbrica para IoT, similar a Sigfox, optimizada para enviar pequeñas cantidades de datos a largas distancias con bajo consumo. Es una red LPWAN (Low Power Wide Area Network)
###### Distinción LoRa y LoRaWAN
- LoRa es la tecnología de modulación de radio que usa Chirp Spread Spectrum (CSS) patentada por Semtech
- LoRaWAN es el protocolo de red que usa LoRa como base

Así LoRaWAN es el protocolo de comunicación de largo alcance usado a menudo para crear redes de área amplia de bajo consumo con un alcance operativo de entre 300m a 10km. Entre los principales protocolos LPWAN, este es de los más usados. 

A hablar de LoRa y LoRaWAN tenemos que especificar que ambos términos son diferentes: LoRaWAN es un protocolo cuya capa PHY se basa en modulación LoRa mientras que la capa de Control de Acceso al Medio (MAC) es una arquitectura de red abierta regulada por LoRa Alliance. LoRa en cambio está basada en CSS que se refiere a la capa física. LoRa está patentada por Semtech, el cuál es el único productor de chips transceptores LoRa. 

Por ende, en pila de protocolos OSI, LoRaWAN (capa de red) se basa en LoRa (capa física) como se ve a continuación:

![[Pasted image 20250118184641.png]]

Otra diferencia más es la topología de red, ya que LoRa solo permite enlaces punto a punto mientras que LoRaWAN define todas las reglas para crear una topología de múltiples estrellas compuesta por muchos nodos finales LoRaWAN y gateways. 
##### Modulación
LoRa modula símbolos en bloques en los que aumenta o disminuye la frecuencia de la señal portadora. Estos bloques se llaman chirps: up-chirps y down-chirps. 

Esta modulación tiene muchos parámetros. Algunos son:
- **Frecuencia portadora** Depende de la región operativa
- **Ancho de banda** Generalmente establecida en 125 kHz pero puede llegar hasta 250 kHz o incluso 500 kHz
- **Factor de propagación** Define cuantos chirps se envían por segundo. Valor grande es igual a más tiempo en el aire el símbolo y más gasto energético. Esto mejora el rango, pero reduce la velocidad de los datos disponibles y el tamaño de la carga útil de mensajes.
- **Potencia de transmisión** Energía irradiada por la antena. Puede variar desde -4 dBm hasta 20 dBm, pero distintas regiones pueden tener diferentes límites de potencia. 
- **Sync Word** Diferenciación de LoRas que usan las mismas bandas de frecuencia
##### Ventajas LoRa  
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
##### Cómo utilizar LoRa  
Existen dos opciones principales para implementar LoRa en proyectos IoT:

1. **Crear una red propia**: Implica adquirir chips LoRa y desarrollar gateways y nodos. Ofrece flexibilidad pero requiere mantenimiento.
2. **Utilizar un operador de red**: Contratar servicios de conectividad LoRaWAN con operadores, evitando el mantenimiento propio, aunque con el riesgo de que el operador retire el servicio.

Además, existen:
- **Comunidades abiertas**: Desarrolladas por comunidades de entusiastas.
- **Redes privadas**: Utilizadas en aplicaciones como ciudades inteligentes, agricultura y logística.
- **Redes de operadoras**: Servicios pagados ofrecidos por operadores de telecomunicaciones que integran LoRaWAN con sus servicios tradicionales.
#### LoRaWAN

LoRaWAN es un protocolo LPWAN diseñado para conectar dispositivos IoT mediante la tecnología LoRa. Define la arquitectura de red y el protocolo de comunicación, permitiendo la gestión de la infraestructura.

A diferencia de otras tecnologías como 3G, 4G, WiFi, Bluetooth, NB-IoT o SigFox, LoRaWAN destaca por su adaptabilidad en escenarios donde las redes móviles y WiFi no son óptimas. Es ideal para proyectos IoT que requieren bajo consumo de energía y transmisión de pequeños volúmenes de datos.

LoRaWAN gestiona el enrutamiento entre gateways y nodos finales. Su especificación inicial (versión 1.0) se presentó en junio de 2015, consolidándose como una solución robusta para redes IoT de largo alcance y baja potencia.