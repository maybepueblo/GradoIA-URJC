#### MQTT
También conocido como Message Queuing Telemetry Transport, es un protocolo de mensajería ligero y eficiente diseñado para dispositivos con recursos limitados, como los de IoT. Se desarrolló en 1999 para la industria del petróleo y el gas, y se ha convertido en un estándar clave para la comunicación en IoT.

Es simple, escalable y capaz de operar en redes de bajas potencia, lo que contribuye a su éxito continuo.  Se inventó pensando en un protocolo con el ancho de banda mínimo y una pérdida de batería mínima, pero mejoró a lo que es actualmente. 

##### Funcionamiento de MQTT
- **Modelo publicación/subscripción** Los clientes publican mensajes en un broker (agente) y se suscriben a temas específicos para recibir esos mensajes.
	- Desacoplamiento espacial: el editor y el suscriptor no conocen la ubicación de la red del otro y no intercambian información como sus IP o números de puerto
	- Desacoplamiento de tiempo: editor y suscriptor ni tienen conectividad de red al mismo tiempo.

##### Componentes de MQTT y proceso de conexión: Clientes y Agentes
- Cliente MQTT: Puede ser editor (envía mensajes) o un suscriptor (los recibe)
- Broker MQTT: Coordina la comunicación entre clientes, filtrando y distribuyendo mensajes.

###### Proceso de conexión
Los clientes inician la conexión al enviar un mensaje de CONECTAR al broker. Este confirma la conexión establecida con mensaje CONNACK. Requieren de TCP o IP para comunicarse.

Destaca esta arquitectura controlada por eventos gracias a su capacidad para gestionar mensajes de tamaño reducido y claramente definidos. Introduce el concepto de Calidad de Servicio con niveles 0, 1 y 2, adaptando entregas a necesidades específicas
##### Beneficios
- **Ligero**: Encabezado de mensaje de 2 a 5 bytes.
- **Altamente compatible**
- **Confiable**: Tres niveles de Calidad de Servicio
	- Nivel 0 (lanzar y olvidar): Se envía el mensaje una vez sin esperar confirmación, lo que reduce el ancho de banda.
	- Nivel 1 (entregado al menos una vez): Debe confirmar el cliente la entrega. Se asegura que los mensajes se entregan al menos una vez
	- Nivel 2 (entregar sólo una vez): Nivel más demandante pero más confiable, ya que esperamos a que el cliente confirme antes de volver a enviar otro mensaje, borrando la posibilidad de duplicados.
- **Seguridad**: Soporta autenticación y cifrado 
- **Abierto**

##### Limitaciones
- No tiene cifrado ni autenticación, lo que hace que el mensaje corra el riesgo de ser interceptado. 

#### Diferencias entre MQTT y REST

![[Pasted image 20250118192403.png]]


| En MQTT mantenemos la conexión y podemos compartir pings para mantenerla abierta                          | HTTP sólo crea una conexión cuando toca enviar una petición                          |
| --------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| **La cabecera más pequeña de MQTT solo tiene 2 Bytes**                                                    | **La más pequeña de HTTP es de 26 bytes**                                            |
| **MQTT es capaz de transportar datos crudos en binario**                                                  | **HTTP requiere codificación en base 64 para ello**                                  |
| **En apps industriales, MQTT permite propagar configs nuevas de los dispositivos mediante suscripciones** | **Las configs nuevas deben solicitarse explícitamente mediante un sondeo periódico** |
**¿Cuál es más rápido?**
MQTT, el cual en redes 3G es 93 veces más rápido, 8 veces menos tráfico y 170 veces menos energía en receptores.

#### Sensibilidad al contexto
Una de las características mencionadas en [[Tema 1 - Introducción a IACO]] para los sistemas de inteligencia ambiental, es la sensibilidad al contexto, donde el comportamiento del sistema cambia según este mismo. Por ejemplo, un sistema de calefacción puede ajustarse según las personas presentes en una casa.

**Detección de presencia**:
- Se pueden usar **balizas Bluetooth (iBeacons)** para detectar la presencia de personas u objetos en un entorno.
- También se puede escanear dispositivos **Bluetooth Low Energy (BLE)** para detectar teléfonos móviles, aunque en dispositivos **Android** la dirección MAC cambia por motivos de seguridad.

#### TinyML
Rama de ML enfocada en implementar y diseñar modelos de aprendizaje automático para dispositivos embebidos como Raspi, Arduino y ESP32. Al tener estos dispositivos limitaciones de energía y capacidad de cómputo, se utilizan librerías especializadas.

