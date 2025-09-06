# Espacios de estados y técnicas de planificación

## 1. Heurísticas para la búsqueda en el espacio de estados
### Introducción a las heurísticas
- **Definición:** Una heurística es una función que estima el costo o la distancia desde un estado actual hasta el objetivo. Es una regla general que ayuda a decidir qué camino tomar en una búsqueda.
	- ***Ejemplo*** En un problema de logística donde se deben entregar paquetes una heurística simple podría ser el número de paquetes no entregados todavía. Cuantos más falten, más lejos se está de la meta.
- **Propósito** Guiar la búsqueda de forma eficiente, reduciendo el espacio de estados necesario a explorar y el tiempo para encontrar la solución
### Funciones heurísticas en planificación STRIPS
- En planificación clásica una heurística puede medir el número de acciones necesarias para llegar al objetivo.
	- **Importante** Calcular una solución exacta en planificación puede ser muy costoso (NP-Completo) pero las heurísticas permiten estimaciones rápidas y razonables.
	- **Heurísticas admisibles** Son aquellas que nunca sobrestiman el costo real. Crucial para algoritmos como $A^*$  que garantizan encontrar la solución óptima si esta heurística es admisible
### Enfoques parar crear heurísticas
1. **Problemas aproximados**
	- Se simplifica el problema original eliminando o relajando condiciones
	- **Ejemplo:** Se eliminan todas las precondiciones de las acciones, cualquier acción pudiendo ejecutarse en todo momento. Esto permite estimar el costo como el número de objetivos no cumplidos
		- *Ejemplo práctico*: En un problema de preparar café, si ignoramos precondiciones como tener agua caliente, café molido se puede ejecutar la acción, pero será una estimación optimista (subestimará el costo real)
2. **Independencia de subobjetivos**
	- Se trata cada subobjetivo como independiente y se suma el costo de resolver cada uno
	- **Limitaciones**
		- *Optimista:* Si hay interacciones negativas (ejemplo: una acción para un subobjetivo arruina otro), la heurística subestima el costo real.
		- *Pesimista*: Si hay redundancias (ejemplo: una misma acción resuelve múltiples subobjetivos), la heurística sobrestima el costo
	- *Ejemplo:* En ruta de entrega, calcular el costo de entregar cada paquete por separado ignorando que algunos camiones pueden compartir rutas
3. **Supresión de efectos negativos**
	- Se eliminan los efectos negativos de las acciones, enfocándose en lo positivo
	- **Ventaja** Reduce conflictos entre acciones y proporciona una estimación más precisa
	- *Ejemplo* Si el objetivo es lograr `A ∧ B ∧ C` y hay acciones que producen `A, B y C` pero también efectos no deseados, ignoramos estos últimos, simplificando el cálculo. 
## 2. Heurísticas para planificación de orden parcial (POP)
### Introducción a la planificación de orden parcial
- **Definición** POP descompone el problema en subproblemas, véase [[Tema 9 - Resolución de problemas con planificación]], sin requerir un orden total de las acciones desde el inicio.
	- *Ejemplo*: Planificar un viaje implica subproblemas como reservar vuelos, hoteles y transporte local, pero no es necesario decidir el orden exacto de todas las acciones de antemano
- **Desventaja** No representa estados directamente, lo que dificulta estimar la distancia al objetivo
### Heurísticas básicas en POP
- **Recuento de precondiciones abiertas**
	- Se cuentan las precondiciones no satisfechas en el plan actual
	- *Ejemplo* Para ir de casa a la oficina, las precondiciones abiertas son "estar en casa" y "estar en la parada de guagua". La heurística básica devuelve un 2.
	- **Problemas**
		- Sobrestima si una acción resuelve múltiples precondiciones
		- Subestima interacciones negativas
### Heurísticas avanzadas en POP
- **Selección de precondiciones abiertas**
	- Se elige la precondición con menos opciones para satisfacerla, acelerando la búsqueda
	- *Ejemplo* Con múltiples rutas para llegar a la oficina se priorizan las precondiciones con menos alternativas
- **Mejoras**
	- Eliminar precondiciones ya satisfechas en el estado inicial
	- Considerar acciones que resuelven múltiples objetivos simultáneamente
### Ejemplo detallado
- **Problema** Llegar a la oficina desde casa
	- Acciones
		1. Caminar a la parada de guagua. Requiere estar en casa
		2. Tomar la guagua. Requiere estar en la parada
	- **Heurística básica**: 2 precondiciones abiertas ("en casa" y "en parada")
	- **Heurística avanzada** Si hay otra opción como "tomar el tren" se selecciona la precondición con menos alternativas (ejemplo: "en parada de guagua" solo tiene una acción que la satisface)