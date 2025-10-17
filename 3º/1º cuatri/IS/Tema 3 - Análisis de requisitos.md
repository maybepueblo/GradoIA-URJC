**Definición**
Un **requisito software** son las funciones, características y restricciones que debe cumplir el producto final. Siendo entonces una capacidad o característica que debe poseer un sistema.
## Ingeniería de requisitos
Se le dice al proceso de recopilación, análisis y documentación de los requisitos. Tenemos diversas tareas:
- **Obtener requisitos** -> Identificar y analizar las necesidades del cliente.
- **Analizar y negociar requisitos** -> Refinamos la obtención de necesidades y negocio. Identificamos restricciones
- **Gestionar y documentar/especificar** -> Documentar estas necesidades de forma precisa y no ambigua. Clasificamos requisitos.
- **Validar y verificar requisitos** -> Comprobar que sean detallados, no ambiguos y no duplicados.
- **Evolución de requisitos** -> Actualizar e identificar nuevas necesidades.

**Estudio de viabilidad** -> Determinado por el coste primariamente.

Se firma un contrato por el cual regirnos, para poder poner un límite e intentar no saturarnos de trabajo. Esto brinda una base sólida para el diseño software y reduce los riesgos de implementación.
### Tipos de requisitos
- **Usuario** -> Servicios *Ej. El sistema debe poder identificar al mejor goleador*
- **Sistema** -> Restricciones *Ej. Una de las funciones es identificar a los mejores goleadores por partido en base a unos datos almacenados en tiempo real*
- **Especificación software** -> Lo que necesitamos y sirve de base para el diseño e implementación *Ej. Al registrar al mejor goleador almacenamos su nombre, edad, num goles por partido, media de goles y minutos jugados por partido*
- **Funcionales** -> Todo lo que debe hacer el sistema
- **No funcionales** -> No aportan funcionalidad, pero mejoran aspectos de su funcionamiento.
- **Dominio**
## Entendimiento del problema
Es lo que llamamos entender el dominio del sistema.
- **Modelo de dominio** Describimos los conceptos y términos importantes del dominio, así como los objetos y operaciones importantes. Hemos de hacer un análisis del mismo:
	- Entrevistamos expertos en él
	- Producimos un glosario de términos
	- Describimos objetos y operaciones importantes
	- Usamos si queremos **diagramas de análisis**
- **Modelo de negocio** Describe los procesos asociados al negocio con el objetivo de comprenderlos:
	- Cómo se realiza un proceso de negocio
	- Para cada proceso definir: trabajadores, operaciones y responsabilidades. Identificamos casos de negocio y actores.
	- Representación: diagramas de casos de uso y de actividades.