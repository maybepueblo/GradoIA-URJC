A día de hoy, la colaboración en equipo es cada vez más imprescindible. Hay un gran número de metodologías orientadas a proyectos de desarrollo pero en este caso veremos los **sistemas de control de versiones** (SCV).

Estos permiten lo siguiente:

- Crear copias de seguridad y restaurarlas.
- Sincronizar a los desarrolladores respecto de la última versión de desarrollo.
- Deshacer cambios, tanto puntuales como históricos.
- Gestionar la auditoría del código: quien hizo qué y cuando.
- Realizar pruebas aisladas a través de las ramas.

#### Terminología

**Repositorio**
- Almacén que guarda la información del proyecto.
- Suele tener una estructura de árbol. 

**Servidor**
- Máquina donde alojamos el repositorio.

**Working Copy / Working Set**
- Copia local donde el desarrollador trabaja.

**Trunk/Main/Master**
- Rama principal, localización dentro del repositorio.
- Contiene la rama principal de desarrollo.

**SCM**
- *Source Code Management* (Gestión de código fuente). Propiedad aplicable a los SCV.

##### Operaciones básicas

- **Add** -> Añadir un archivo para ser rastreado por el SCV.
- **Revisión** -> Versión de un archivo o directorio dentro del SCV.
- **Head** -> Última versión del repositorio. 
- **Check out** -> Creación de una copia de trabajo que rastrea un repositorio.
- **Check in / commits** -> Envío de cambios locales al repositorio. Como resultado cambia la versión del archivo / repositorio.
- **Mensaje de check in / log** -> Todo check in tiene asociado un mensaje que describe la finalidad del cambio. Puede estar asociado a un sistema de gestión de incidencias (tickets).
- **Log** -> Permite ver o revisar la lista de cambios de un archivo o repositorio.
- **Update / Synchronize / fetch&pull** -> Sincroniza la copia de trabajo con la última versión que existe en el repositorio.
- **Revert / Reset** -> Permite deshacer los cambios realizados en la copia de trabajo y dejar el archivo / recurso en el último estado conocido del repositorio.

##### Operaciones avanzadas

- **Branching** 
	- Permite crear una copia de un archivo o carpeta.
	- Permite desarrollar en paralelo en otra "rama" pero dejando constancia de la relación con la rama original.
- **Diff / Change / Delta** 
	- Permite encontrar las diferencias entre dos versiones del repositorio.
	- Se puede generar un parche que permitiría pasar de una versión a otra.
- **Merge / Patch**
	- Aplica los cambios de un archivo a otro.
	- Utilizado habitualmente para mezclar branches.
- **Conflict**
	- Problema que surge cuando varios desarrolladores modifican el mismo recurso y los cambios se solapan.

#### Tipos de SCV

**Centralizados**

- Existe un servidor centralizado que almacena el repositorio entero.
- La comunicación / colaboración se lleva a cabo forzosamente a través del este repositorio centralizado.
- Son más fáciles de usar.
- Los modelos de trabajo son más restringidos.

**Distribuidos**

- Cada desarrollador tiene una copia completa del repo.
- Los mecanismos de comunicación / colaboración entre desarrolladores son más abiertos.
- Son más difíciles de usar que los sistemas centralizados.
- Los modelos de trabajo son más flexibles.
- Los branches/merges son más simples.

#### Políticas de control de versiones

Para aprovechar los SCV es necesario establecer una política para el control de versiones en los proyectos además de documentar el desarrollo.

Existen herramientas como Trello o Slack que pueden vincularse a repositorios de códigos.

Cabe destacar que es vital adoptar un modelo de trabajo adecuado para el equipo de desarrollo, lo cual condiciona la herramienta SCV a usar. 

#### Metodología básica de trabajo

**Primera vez**
1. Crear el repositorio.
2. Crear una copia de trabajo del repo.
3. Modificar la copia de trabajo.
4. Enviar cambios al repo.

**Siguientes ocasiones**
1. Actualizar el repo.
2. Modificar la copia de trabajo.
3. Enviar los cambios.

#### Ventajas de git

- **Branches locales muy útiles y "baratos"**
	- Fáciles de crear y borrar.
	- No han de ser públicos.
	- Útiles para organizar el trabajo y los experimentos.
- **Las operaciones en git se gestionan en local**
	- Operaciones más rápidas.
	- Se puede trabajar sin red.
	- Todos los repos de los desarrolladores son iguales, así que en caso de emergencia, sirven de backup.
- **El espacio ocupado no es grande pese a guarda una copia de todo el repo**
	- Si dos archivos son iguales se guarda el contenido de uno solamente.
	- El contenido de los archivos se guarda comprimido.
	- Se compactan archivos periódicamente, generando *deltas* entre diferentes versiones de los archivos.
- **Git tiene integridad: todo tiene una firma asociada**
- **La *staging area* o área de ensayo es la zona donde se añaden los cambios a hacer en el commit**
	- No es necesario añadir todos los archivos de la WC a la SA.
	- Es posible añadir modificaciones parciales (hunks). De este modo cada mod parcial puede ir en un commit.
- **Buena práctica: commits frecuentes** 
	- Pequeños y que incluyan las modificaciones concretas que resuelvan un problema o tarea.

#### GitHub

Es un servicio de git gestionado que tiene una versión gratis con repositorios siempre públicos, una versión education y una versión de pago con diversas características.




