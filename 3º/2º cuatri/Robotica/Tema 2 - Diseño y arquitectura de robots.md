microprocesador: sistema operativo y haga ops complejas
microcontrolador: no lleva os y genera información pa actuadores (ops de bajo nivel)
fpga: es reprogramable para cambiar conexiones y amoldarlo a lo necesario
gpu:

# Sensores
Confiar en un único sensor es erróneo

Permiten recibir info del entorno que rodea al robot.

Tipos:
- Posición y desplazamiento
- Movimiento y velocidad
- Fuerza y tacto
- Distancia
- Ambientales
- Visión
- Posicionamiento

## Posición
encoder incremental: no da ángulos, solo velocidad o aceleración.

nombre de codificación 00 01 11 10 00 -> **codificación gray**
## Distancia

LIDAR: se mueve el espejo, no el láser. Para nube de punto vertical también se usan pero esos son verticales

saber fórmulas sobre geometría básica, perímetros círculo, clindro, áreas y demás

## Motores
Potencia del motor$$P=V·I$$
Pérdida del motor $$P=R·I²$$
Corriente $$I=\frac{T}{k_t}=\frac{0.6Nm}{0.2\frac{Nm}{A}}=3A$$
Rendimiento$$𝜂=\frac{P_{mecánica}}{P_{eléctrica}}$$
Pasar de radianes a revoluciones por minuto $$90\frac{rad}{s}·\frac{1 rev}{2\pi rad}·\frac{60s}{1min}=800rpm$$
## Servomotores
Traduce el giro de un motor a ohmios recibido por un potenciómetro que luego vuelve a dar esta resistencia al circuito original en forma de feedback (realimentación)

Se utilizan principalmente en control de posición
## Motores paso a paso
En función de cómo las gire, se consigue más resolución.