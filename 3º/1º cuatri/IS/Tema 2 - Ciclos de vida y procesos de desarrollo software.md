## 1. Concepto de Ciclo de Vida

¿Qué es el Ciclo de Vida del Software?

Es el proceso por el que pasa el software en su desarrollo, abarcando desde que se concibe la idea hasta que el software deja de utilizarse o se retira.

**Características principales:**

- Está compuesto por un conjunto de **actividades y tareas** necesarias para producir el software y su documentación.
- Existe una **secuencia temporal** para estas actividades.
- Cada etapa genera una serie de documentos (salida) que sirven de entrada para la fase siguiente.

**Etapas generales:**

1. Análisis
2. Diseño
3. Codificación -> Desarrollo (código) - no estar mucho tiempo programando si quieres dinero
4. Pruebas 
5. Integración -> Mezclar todo el contenido del sistema para una versión final
6. Implantación -> Desplegar el software en máquinas cliente

---

## 2. Modelos de Procesos

Según la norma **ISO/IEC/IEEE 24774:2021**, un modelo de proceso es una representación abstracta consistente en un conjunto de actividades y tareas cuyo objetivo es el desarrollo de un sistema software.

**Función:**

- Son estrategias que ayudan a **organizar** las actividades del ciclo de vida.
- Facilitan el **control** y la **coordinación** del proyecto.
- La elección del modelo depende del tipo de proyecto y de los recursos humanos disponibles.

### Modelo en cascada
Divide el desarrollo en fases, impidiendo que se empiece la siguiente hasta terminar la anterior. 

Terminó siendo un modelo circular, implicando que se vuelve a la primera fase de análisis tras haber terminado el mantenimiento para seguir teniendo en cuenta las nuevas peticiones del cliente.

**Ventajas**
Se adapta cuando el proyecto es complejo y grande, más bien estructurado desde el inicio. 

**Desventajas**
Es limitado, ya que su planteamiento obliga a no pasar de fase hasta terminar la anterior.
### Modelo evolutivo
Posibilidad de mostrar un prototipo sin tener que tener toda su funcionalidad. Esto es flexible, pierdes poco tiempo de trabajo y si gusta la alpha, se sigue el contrato y se va brindando un prototipo más firme cada vez.

**Ventajas**
Entregamos a corto plazo, reduciendo costos. Importa mucho la interfaz del sistema, llegando a dar un 80% de la misma y un 20% de funcionalidades. 

**Desventajas**
Puede tener mala calidad en ciertas etapas, además de que necesitamos buena organización y mucho más hincapié en el diseño
### Modelo en espiral
Combinación del cascada y evolutivo, donde terminamos cuando se acaban los requisitos, siendo cada ciclo una fase del proyecto (incertidumbre por no saber cuántas vueltas son necesarias)

**Fases**
- Planificación
	- Comunicación cliente-empresa
	- Objetivos
	- Alternativas de desarrollo
	- Restricciones
- Análisis riesgos
	- Puntos de fallo y evaluar alterativas
	- Resolver o minimizarlos
	- Riesgos de cada alternativa y sus soluciones 
- Ingeniería
	- Desarrollamos y verificamos el siguiente nivel del producto.
- Evaluación
	- Obtener conformidad del cliente
	- Revisión
	- Planificamos la siguiente vuelta. 
	- Además estimamos recursos necesarios

**Ventajas**
Para proyectos complejos, sirve muy bien en proyectos innovadores y ambiciosos

**Desventajas**
Es complejo evaluar riesgos. Y no es recomendado para proyectos sin ellos, muy costoso si no.
### Modelo incremental
Útil para empresas conformadas por varios equipos. Los incrementos vienen en serie y se terminan solapando partes entre sí.

**Ventajas**
Se entrega un producto útil en los primeros momentos

**Desventajas**
No pueden ser muy grandes, es difícil obtener incrementos equilibrados
### Proceso unificado de desarrollo (RUP)
Rational Unified Process. Compuesto por 4 fases:
- **Inception** -> Idea y visión del proyecto, no tenemos por qué extraer todos los requisitos
- **Elaboration** -> Se terminan de obtener los requisitos y se plantean los primeros prototipos
- **Construction** -> Implementación al 100% y se crea un manual
- **Transition** -> Damos el producto al usuario y hacemos beta testing
#### Metodologías ágiles
Proyecto con poco personal para que la entrega de software sea mucho más rápida, además de perder el aspecto de desarrollo de documentación y de una buena arquitectura de proyecto (proyectos de código libre suelen seguir este esquema de desarrollo)

Lo que sea en menos tiempo, reduciendo docs, diseño y teniendo equipos pequeños, rápidos al cambio.

**Ventajas**
Producto pequeño o mediano y gran implicación del cliente

**Desventajas**
Priorizamos cambios y mantenerlo simple es complejo. 
#### XP (eXtreme Programming)
Entregas frecuente y código simple hecho en parejas. Hay entonces un diseño simple, mínimo e imprescindible. 
#### Scrum
Modelo ágil más usado hoy en día. Con equipos pequeños (7-9 personas por ejemplo, no es fijo)

Basado en "sprints" para hacer entregas, teniendo poca documentación y diseño mínimo, teniendo meetings diarios y revisiones cortas en cada sprint. Hay diferentes actores en el equipo, usando repos para almacenar la información

Organizamos los sprints en una cronología, dando a cada uno de 1 a 4 semanas. Cada día nos reunimos para sincronizar el equipo en corta duración siendo muy ágil. Al final del tiempo de cada sprint se hace un review para ver cómo van los requisitos
#### Kanban
Similar a Scrum pero con uso de tarjetas para gestionar las historias de usuario a realizar (Trello), pero sin roles pre-asignados ni sprints, sino siendo un flujo continuo
#### Otras...
- **Basadas en reutilización de software** (COTS, Generativa, SPL)
- **Orientadas a objetos** (OOAD)
- **DevOps** (Development & Operations)
- **MLOps** (Machine Learning Operations)

> [!NOTE] Sabiduría del profe
Nunca discutir el sueldo neto, te van a engañar con impuestos en el primer minuto. Discute el sueldo bruto anual, que incluye el sueldo y los impuestos con la retencion


---

## 3. Estándar ISO 12207:2017

Este estándar define los procesos del ciclo de vida del software, clasificándolos en diferentes categorías.

### A. Procesos de Soporte

Dan apoyo a otros procesos a lo largo del ciclo de vida.

- **Revisión conjunta:** Reuniones con el cliente y el equipo para revisar el estado del trabajo en una fase determinada.
- **Auditorías:** Determinan si se han conseguido los objetivos y aseguran el cumplimiento del contrato.
- **Resolución de problemas:** Analizar y resolver incidencias surgidas durante el desarrollo, explotación o mantenimiento.
- **Verificación y Validación (V&V):**
    - **Verificación:** Comprobar que el producto cumple con las **especificaciones** y estándares (¿lo estamos construyendo correctamente?).
    - **Validación:** Determinar que el producto cumple con los **requisitos** y necesidades del usuario (¿estamos construyendo el producto correcto?).

### B. Procesos Generales

Proporcionan soporte a nivel de organización.

- **Gestión:** Planificación, seguimiento, control y evaluación del proyecto (uso de herramientas como MS Project).
- **Infraestructura:** Determinar las herramientas y entorno necesario para el desarrollo y explotación.
- **Mejora:** Medir y evaluar los procesos para optimizarlos.
- **Formación:** Planes de capacitación para los empleados.
