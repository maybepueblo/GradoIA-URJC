## SI
### Sistema
Definido como cosas que ordenadamente relacionadas entre sí contribuyen a un determinado objetivo. Estos están limitados, siendo todo lo situado fuera de los límites como entorno. Este sistema toma elementos del entorno como materias primas para devolver salidas.
### Sistema de Información
**Datos** -> Elementos que permiten describir ciertos eventos, actividades o transacciones
**Información** -> Proviene de la ordenación de datos de forma que éstos tengan un significado concreto para el que recibe e incluso un valor determinado
**Conocimiento** -> Evaluada por persona dentro de un contexto
#### Definición
Un SI es un conjunto de elementos, ordenadamente relacionados entre sí de acuerdo con unas ciertas reglas, que aporta al sistema objeto (es decir, a la organización a la cual sirve y que le marca las directrices de funcionamiento) la información necesaria para el cumplimiento de sus fines, para lo cual tendrá que recoger, procesar y almacenar datos, procedentes tanto de la misma organización como de fuentes externas, facilitando la recuperación, elaboración y presentación de los mismos
### Componentes
![[Pasted image 20250227225355.png]]
### Gestión y ayuda a tomar decisiones
- Nivel estratégico
	- Elaborar planes
	- Objetivos generales
- Nivel táctico
	- Control de gestión
	- Objetivos específicos
- Nivel operacional 
	- Tareas administrativas
## De sistemas tradicionales a bases de datos
### Clásico : Orientados a Proceso
- **Estructura**: Almacena datos en archivos individuales en el disco duro.
- **Acceso**: Gestiona solo el acceso físico a los datos.
- **Organización**: Los datos no están necesariamente organizados de manera estructurada.
- **Seguridad**: Menos opciones de seguridad y control de acceso.
- **Escalabilidad**: Menos eficiente para manejar grandes volúmenes de datos.
- **Redundancia**: Mayor probabilidad de duplicación de datos.
#### Desventajas
- Ocupar inútil memoria
- Aumento proceso
- Inconsistencia
- Dependencia
- No son apropiados para ayuda
### BD : Orientado a Datos
- **Estructura**: Almacena datos en estructuras (p.e.tablas) organizadas que pueden estar relacionadas entre sí.
- **Acceso**: Gestiona tanto el acceso físico como lógico a los datos.
- **Organización**: Los datos están organizados de manera estructurada y pueden ser fácilmente consultados.
- **Seguridad**: Ofrece opciones avanzadas de seguridad y control de acceso.
- **Escalabilidad**: Más eficiente para manejar grandes volúmenes de datos.
- **Redundancia**: Minimiza u controla la duplicación de datos mediante distinto mecanismos
## Ventajas e inconvenientes
### Ventajas
Datos
- Independencia
- Mejor disponibilidad
- Mayor eficiencia
Resultados
- Coherencia
- Valor informativo
- Normalizada documentación
Usuarios
- Acceso rápido y sencillo
- Facilidades para compartir
- Flexibilidad
### Inconvenientes
- Coste
- Instalación costosa
- Necesidad de personal especializado
- Implantación y optimización compleja
- Desfase teórico-práctico
## Concepto de base de datos
### Base de Datos
Colección o depósito de datos integrados, almacenados en soporte secundario
(no volátil) y con redundancia controlada. Los datos, que han de ser compartidos
por diferentes usuarios y aplicaciones, deben mantenerse independientes de ellos,
y su definición (estructura de la base de datos) única y almacenada junto con los
datos, se ha de apoyar en un modelo de datos, el cual ha de permitir captar las
interrelaciones y restricciones existentes en el mundo real. Los procedimientos
de actualización y recuperación, comunes y bien determinados, facilitarán la
seguridad del conjunto de los datos
### Sistema de Gestión de Base de Datos
Conjunto de programas que permiten la implantación, acceso y mantenimiento de la BD
### Sistema de Base de Datos
SGBD + DATOS + USUARIOS