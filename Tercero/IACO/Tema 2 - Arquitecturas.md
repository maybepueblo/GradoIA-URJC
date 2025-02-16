#### Conceptos básicos

Entendemos por arquitectura de un sistema los componentes que lo forman, sus funciones y cómo se relacionan entre ellos.

Normalmente describimos las arquitecturas en capas, cada una teniendo su función específica y sus propia forma de comunicarse con otros procesos de cada capa (protocolo)

#### OSI (Open Systems Interconnection)

Es un marco de referencia de 7 capas para la transmisión de datos:
1. **Física**: transmisión de bits
2. **Enlace de datos**: formación de tramas y corrección de errores
3. **Red**: enrutamiento de paquetes
4. **Transporte**: División y control de errores de segmentos
5. **Sesión**: Gestión de conexiones
6. **Presentación**: Formateo y cifrado
7. **Aplicación**: Interacción con el usuario

Funciona de la siguiente manera:

![[Pasted image 20250118162346.png]]

Como vemos, cada capa añade información específica para una correcta llegada, y luego, invertimos los pasos.
##### Capa física

Es la más baja del modelo referencia OSI. Responsable de conectar físicamente a los dispositivos. Esta contiene información en forma de bits. Así, se encarga de transmitir bits individuales de un nodo al siguiente. Al recibir datos, esta capa obtendrá la señal recibida y la convertirá en 0s y 1s para posteriormente enviarlos a la capa de enlace de datos, para repetir el proceso a su inversa.

#### Arquitectura IoT
- **Percepción (capa de enlace)**: Sensores y microcontroladores como ESP8266 o Raspberry Pi.
- **Transporte**: Protocolos de red como BT, Zigbee o [[LoRa]].
- **Procesado**: Servicio en la nube, una servicio web, etc.
- **Aplicación e Interfaz**: Servicios finales adaptados al usuario, basados en contexto y necesidades.

#### Protocolos
- **Serie, I2C, SPI**: Conexiones locales
- **CAN-BUS**: Automoción
- **TCP/IP vs UDP**: TCP garantiza sesiones y control de errores mientras que UDP es más ligero y rápido.
#### One wire

##### Protocólo

#### CRC 
Es un sistema robusto, conformado por un byte completo que es mucho más complejo que llegue de forma incorrecta, no como el bit de paridad. 

#### Lectura ROM
