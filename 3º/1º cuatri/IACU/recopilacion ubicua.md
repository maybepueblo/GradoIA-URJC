# T1.Introducción:
## Definiciones:
- **Inteligencia Ambiental:** la capacidad de los **entornos físicos** de interactuar con los usuarios de manera inteligente y adaptativa. Usando sensores para crear entornos que puedan entender, resolver y anticipar las necesidades de las personas.
- **Computación Ubicua:** tecnología **disponible** en todo momento y en todas partes. Integrar en la vida cotidiana de manera casi invisible (sin barreras para su uso y de forma natural).
## Características:
- **Sensible al contexto**.
- **Acceso ubicuo**.
- **Interacción natural**.
## Aplicaciones de la IoT:
- Smart Cities.
- Domótica.
- Salud y forma física.
- Agricultura.
- Logística.
# T2.Arquitectura:
## Modelo OSI (Open Systems Interconnection):
1. **Capa de aplicación**: las apps crean los datos e interaccionan con el usuario.
2. **Capa de presentación**: los datos se formatean y cifran.
3. **Capa de sesión**: gestión de conexiones.
4. **Capa de transporte**: los datos se dividen en segmentos y control de errores.
5. **Capa de red**: se almacenan en paquetes y se enrutan.
6. **Capa de enlace de datos**: los paquetes se enmarcan y se envían al siguiente dispositivo.
7. **Capa física**: transmisión de bits.
## Arquitectura IoT:
1. **Percepción**: sensores.
2. **Transporte**: protocolos wifi, bt, ble, Zigbee o LoRa.
3. **Procesado**: centro de datos y servicio web.
4. **Aplicación**: Interfaz de usuario sensible al contexto (adaptada a sus necesidades).
# Capa de Percepcción:
## Serie:
Nace para mandar bit a bit por un **mismo cable** en vez de por distintos cables en paralelo. USB, I2C, SPI, ...
**Bit de paridad** (comprobar errores).
- **Método Simplex**: (unidireccional) solo el receptor o el emisor están activos a la vez. La radio o la tele.
- **Método Half-Duplex**: tanto emisor como receptor están activos, pero no a la vez. Si uno emite el otro acepta, pero no puede enviar. Internet.
- **Método Full-Duplex**: tanto emisor como receptor pueden transmitir al mismo tiempo. Comunicaciones por smartphone.
### Implementación:
- **RS232** es full duplex, max 15m de cable.
- **TTL** es la que se usa ahora con UART.
**UART** es el dispositivo que controla los puertos y dispositivos serie en las placas base. Está deshabilitada por defecto en Raspi.
### RS232 vs TTL:
- **RS232** al tener más rango de voltajes es **menos susceptible al ruido**.
- Los **niveles lógicos** de RS232 y TTL **están invertidos**, los "1"s y "0"s invertidos entre sí.
## Serialización:
Puerto serie solo puede enviar arrays de bytes. La serialización permite transformar los datos en estos.
### Formatos:
- Texto: XML y JSON.
- Binarios: int, string, float, ...
## One Wire:
Conectar **varios dispositivos a un mismo puerto**. Bidireccional **(half-duplex)** 2 cables sensor y tierra, aunque normalmente son 3 (pa alimentar al cacharro con el último). Cada bus tiene **solo 1 maestro y varios esclavos**. **Los esclavos no pueden iniciar la escritura, el maestro tiene que querer leer**. En reposo la linea se mantiene el pull up. **CRC** como el bit de paridad pero un byte pa q sea más complejo que llegue mal.
## I2C:
**Permite varios maestros**. **Más rápido que one** wire ya que tiene un **reloj (sincronización)**. 2 cables, uno pa datos y otro pa reloj. El **uid (la dirección de un cacharro) no es universal**: 2 dispositivos del mismo fabricante tienen la misma dirección. 
## Otros:
- SPI: igual q i2c.
- BUS CAN: el de coches que es super seguro (ningún dato se pierde).
# Capa de Transporte:
Los protocolos se dividen alcance y ancho de banda. topología de estrella pa bl o ble y malla. 
## Wifi:
El router recibe los datos de internet de banda ancha y los **transforma en ondas de radio**. 5GHz penetra menos las paredes, pero la usa menos gente. **Modulamos la señal en AM y FM**. Topología de **red de estrella con el punto de acceso (router)**. 50m, y buen ancho de banda, pero consume mucho. La MAC es universal, la ip varía. 
## BLE:
**Menor rango, modelo cliente servidor**. En el caso de la punto a punto solo un par cliente servidor. UUID identificador universal. **BLE no es Bluetooth**. Características write, read y **notify**: notifica de el cambio de un valor y así el servidor no tiene que estar solicitándolo todo el rato.
## LoRa:
**Long Range, pequeñas cantidades de datos a largas distancias, con consumo reducido**. **LoRaWAN es el protocolo y LoRa es la tecnología de modulación de radio**. LoRa es la señal de radio y LoRaWAN es el protocolo.
**Bajo consumo de energía y 20km**. Se mezclan los mensajes ya que están en un medio compartido, pa separarlos y que le lleguen a un destinatario en concreto se puede poner un id, o configurar para que llegue a un nodo específico o cifrar o usar otra frecuencia. Alta tolerancia a las interferencias y bajo coste.
# Capa de Procesamiento:
## MQTT:
**Protocolo de mensajería eficiente y ligero. Se apoya en protocolo de transporte como TCP/IP**. Ancho de banda mínimo. Agente MQTT (BROKER) recibir y filtrar los mensajes. Si queremos asegurar una conexión segura y que solo un dispositivo concreto sea el que se suscriba, hacemos que el topic sea su **MAC**. Al broker nos conectamos con su **IP**.
### Calidad o QoS: 
- **Nivel 0**: lanzar y olvidar.
- **Nivel 1**: se reenvía el mensaje hasta que confirmen que lo recibieron.
- **Nivel 2**: se espera a que confirme el mensaje antes de enviar otro.

**No es muy seguro**, no tiene cifrado o autentificación default, pero se le puede poner. Es **más rápido y eficiente que http** y http tampoco tiene: 
- **Última voluntad**: si uno se desconecta repentinamente, el broker avisa a los demás del mismo topic.
- **Retención de mensajes**: cuando uno recién se suscribe recibe una actualización de estado sobre el resto de clientes.

Ya que **http solo abre conexión cuando necesita mandar un mensaje y mqtt siempre**. **Mosquitto** es el broker más popular.
## TinyML:
Rama de ML enfocada en implementar y modelos de **ML para dispositivos embebidos** como Raspi, Arduino y ESP32.
# Otras Cosas que dijo en clase:
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
