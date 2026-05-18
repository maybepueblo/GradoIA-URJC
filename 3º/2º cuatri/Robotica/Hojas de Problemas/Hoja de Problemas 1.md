1. **Explica qué es un robot y cómo ha evolucionado la robótica desde sus inicios hasta la actualidad, destacando 3 hitos importantes.**

Un robot es toda máquina programable capaz de realizar una tarea con una autonomía total o parcial

Desde la antigüedad hasta la actualidad podemos encontrar una variedad de acontecimientos que colaboraron en el desarrollo de la robótica, siendo algunos notorios los siguientes:
- Término "*autómatas*" en la Antigua Grecia, siendo estos mecanismos simples con poleas y palancas que usaban los griegos para fines lúdicos
- Se acuña el término "robot" por Alek Capek y posteriormente Isaac Asimov define los 3 principios fundamentales de la robótica
- Cabe destacar también el Test de Turing y el paper de McCulloch y Pitts en Cálculo Lógico, que son bases de la inteligencia artifcicial. 

A día de hoy, la comercialización masiva de robots como el Furby o la iRoomba son un fenómeno importante de que la robótica está cada vez más en nuestra vida.

2. **Identifica tres tipos de robots según su clasificación funcional (industrial, médico, de servicio, etc.) y da un ejemplo de aplicación para cada uno.**

- **Industrial**: Robot de soldadura en líneas de automóviles
- **Médico**: Robot quirúrgico
- **De servicio**: Robot Roomba para limpieza del hogar

3. **Explica tres características fundamentales que debe cumplir un sistema para ser considerado un robot. Justifica con un ejemplo.**

Un robot tiene que cumplir lo siguiente:
- **Autonomía**: Un robot debe de tener la capacidad de hacer una tarea por si mismo o bien de forma completa o bien de forma parcial
- **Sensores**: Tiene que tener la capacidad de percibir el entorno que le rodea mediante mecanismos integrados en el mismo
- **Actuadores**: Ha de poder ejecutar acciones gracias a ciertas tecnologías que incorpore el sistema

Por ejemplo, un Roomba de limpieza es un gran ejemplo de robot, pues tiene una **autonomía** completa, pues puede él limpiar toda la sala por su cuenta sin supervisión.

Además, cuenta con una serie de **sensores** para detectar paredes que le rodeen y obstáculos, así como **actuadores** para poder moverse por el terreno, ir limpiando conforme se mueve y esquivar obstáculos.

4. **Destaca dos ventajas y dos desafíos del uso extendido de robots en la sociedad.**

**Ventajas:**
- Proporcionan seguridad laboral a la hora de prevenir riesgos en entornos de peligro como puede ser realizando los mismos robots tareas de soldadura o de corte, que pueden suponer problemas para humanos.
- La eficiencia y autonomía que contemplan estos. El hecho de poder tener en ejecución un robot con costes mínimos y en pie una gran cantidad de tiempo es beneficioso para la industria y para tareas que requieren una gran cantidad de recursos.
**Desafíos**:
- Hay riesgos éticos
- Se pueden sustituir empleos que lleven instaurados por mucho tiempo, lo que presenta un desafío.

5. **Diseña una tarea simple que pueda ser realizada por un robot y justifica qué elementos (sensores, actuadores y software) serían necesarios para llevarla a cabo.**

**Tarea:** Detección de incendios en bosques forestales
- Sensores: Cámaras térmicas, sensores de posicionamiento y ubicación estilo GPS
- Actuadores: Motores para vuelo/movimiento
- Software: Algoritmo de búsqueda/explorativo en un terreno y sistema de aviso en caso de detección.

6. **Compara las características principales de un microcontrolador, un microprocesador y una FPGA. ¿En qué aplicaciones robóticas se usaría cada uno?**


| Elemento         | Propósito/Construcción                                                      | Característica clave     |
| ---------------- | --------------------------------------------------------------------------- | ------------------------ |
| Microcontrolador | Realizado de tareas específicas (e.j control de un actuador o de un sensor) | Su bajo consumo          |
| Microprocesador  | Aplicaciones generales de cálculo                                           | Son muy flexibles        |
| FPGA             | Circuito de puertas lógicas programables                                    | Procesado en tiempo real |
**Aplicaciones**
- **Microcontrolador:** Uso en robots pequeños como en el control de un brazo robot mediante Arduino.
- **Microprocesador:** Manejo de software y línea de ejecución de los procesos de un robot. Uso en robots con procesamiento avanzado (e.j con una Raspberry Pi)
- **FPGA:** Uso para situaciones de baja latencia como en el espacio. Ejecución en tiempo real con imágenes.

7. **Dibuja un esquema básico que muestre la arquitectura de un robot. Incluye los elementos principales (unidad de control, sensores, actuadores, fuente de energía, etc.) y describe brevemente la función de cada uno.**

*Subir esquema*

8. **Explica las diferencias entre una comunicación cableada y una inalámbrica en un robot. Proporciona un ejemplo de cada caso.**

En una comunicación cableada se mantiene la conexión con otros robots o con humanos enteramente mediante medios físicos como cables Ethernet o conexiones usb. Un ejemplo de sistemas que usarían estos procesos son todos aquellos robots estáticos como pueden ser los robots manipuladores.

En cambio, la comunicación inalámbrica es donde, mediante procesos como el Wifi o el BlueTooth, se permite a los robots la comunicación remota, lo cuál es idóneo donde el robot tiene que realizar tareas en movimiento y no posición fija. Un ejemplo puede ser el roomba, que está en conexión mediante el wifi de la habitación donde se encarga de la limpieza.

9. **Describe tres tipos de fuentes de alimentación utilizadas en robots y analiza sus ventajas y limitaciones según el entorno de trabajo.**

- **Batería**
	- **Ventajas**
		- Son ligeras compactas y económicas
	- **Limitaciones**
		- No tienen un tiempo de vida muy prolongado lo que limita significativamente la autonomía del robot, no idóneo para entornos de trabajo donde debe estar funcionando por una cantidad larga de tiempo
- **Célula de combustible**
	- **Ventajas**
		- Tienen una alta densidad energética y proporcionan una muy larga autonomía al robot
	- **Limitaciones**
		- Son caras, lo cuál impide por ejemplo hacerse con una gran cantidad de robots que utilicen esta forma de alimentación ya que puede ser un gasto no asumible
- **Alimentación por cable/continua**
	- **Ventajas**
		- Son idóneas pues la autonomía del robot es ilimitada mientras se le provea de corriente
	- **Limitaciones**
		- Tiene que ser un robot fijo o estático, limita de forma increíble el movimiento del mismo. 

10. **Explica cómo funciona el ciclo de control en un robot típico. Incluye los pasos de sensado, procesamiento y actuación, y pon un ejemplo práctico que lo ilustre**

**Ejemplo:** Robot que evita obstáculos
- **Sensado:** Detección de obstáculos conforme va avanzando mediante el uso de cámaras o un sensor ultrasonidos
- **Procesamiento:** Decide si girar o no según la disposición del obstáculo
- **Actuación:** Dado el procesamiento del robot, ejecutará la acción de girar o seguir en su dirección original.