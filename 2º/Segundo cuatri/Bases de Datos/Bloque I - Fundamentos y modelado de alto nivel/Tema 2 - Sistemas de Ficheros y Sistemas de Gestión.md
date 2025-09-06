## Sistemas de ficheros
### Estructura física y lógica
**Fichero**: Colección con nombre de datos que tienen relación entre sí y están ciertamente organizados. Un fichero viene constituido por una colección de registros.

- **Registro** (lógico)
	- Colección de información. Unidad básica de información procesada, se constituye por campos lógicamente relacionados.
- **Campo**
	- Unidad mínima de información de un registro. Describe atributos de una entidad.

Nos organizamos una jerarquía simple de mayor a menor:
- Ficheros > Registros > Campos > Caracteres

En estos ficheros necesitamos distinguir las estructuras lógicas (organizar datos para usuarios) y las físicas (organizar datos para soportes como discos).

Establecer una correspondencia entre lo lógico y lo físico es vital, lo cual se encarga a bajo nivel el sistema operativo y a alto nivel la aplicación a utilizar.
### Objetivos de diseño y gestión
El diseñar ficheros y gestionarlos es clave para que funcione bien un sistema de info. Deben cumplirse unos requisitos para alcanzar eficacia (lógico) y eficiencia (físico) en el sistema.
- Eficacia
	- Fiel a lo real
	- Aislar al usuario de la complejidad
	- Facilitar la manipulación de datos
	- Evitar redundancias lógicas
- Eficiencia
	- Minimizar espacio
	- Disminuir tiempos
	- Minimizar mantenimiento
	- Optimizar recursos
### Operaciones sobre fichero
**Sobre la totalidad**
- Creación
- Destrucción
- Lectura
**Sobre registros**
- Actualizar
	- Insertar
	- Borrar
	- Modificar
- Lectura selectiva
**Otros**
- Abrir
- Cerrar 
- Organizar
### Organizaciones y métodos de acceso
La organización es la forma en la que estructuramos registros en el fichero, mientras que el método es nuestro modo de localizar registros en un fichero.

Para decidir la organización nos guiamos por si son archivos estáticos o dinámicos, eficiencia al ejecutar operaciones o en caso de más de una organización, comprometerse.

Almacenar entonces se puede hacer tal que:
- Consecutivo -> colocamos registros según orden de llegada (uno tras otro)
	- Sin/con orden (serial/secuencial)
- Direccionado -> dirección física de dónde se sitúa registro
	- Directo/Disperso (valor/hashing)
- *Índice* -> Facilitan el acceso a los registros
	- Basada en estos
- El tipo de organización y el soporte están relacionados.

Como métodos de acceso tenemos:
- **Secuencial**
	- Acceso a fichero según orden de almacenaje de sus registros.
- **Directo**
	- Implica el acceso a un determinado registro, sin implicar el acceso a precedentes.
		- Por su dirección a través de una clave
		- Determinada posición (indexado)
### Estructuras de índices para ficheros
Son auxiliares, para aumentar velocidad de recuperar registros en respuesta a ciertas condiciones de búsqueda. Dando caminos secundarios en base a campos de indexación, los cuales cualquiera se puede usar para un índice, teniendo entonces un fichero múltiples índices sobre varios campos.

Hay tres tipos pero solo hablaremos de uno de ellos
#### Ordenados de un solo nivel
Similar a libros de texto (términos ordenados alfabéticamente y lista de nº de páginas en las que aparece). Se define entonces sobre un solo campo del registro llamado campo de indexación. Tenemos entonces valores de este campo y un puntero a bloques del disco que contienen registros.

Tenemos así los valores ordenados, siendo el fichero de este índice mucho más pequeño que los datos, realizando búsquedas binarias. Los ínidces multinivel lo hacen construyendo índices sobre este fichero índice.

Los más comunes de este tipo son:
- Primario -> Campo de ordenación único para cada registro.
- Agrupación -> Sobre el ampo de ordenación.
- Secundario -> Sobre cualquier campo que no sea de ordenación.
## Sistemas de gestión de bases de datos (SGBD)
### SGBD como interfaz usuario/BD
Actúa como interfaz entre la BD y los niveles de gestión de la organización; integrando subsistemas, atendiendo a necesidades de usuarios en los tres niveles.
- **Nivel estratégico** -> Planes y objetivos generales
- **Nivel táctico** -> Gestión y objetivos específicos
- **Nivel operacional** -> Tareas administrativas
Así, en una BD tenemos usuarios informáticos y finales
### Concepto y funciones
Decimos que un SGBD es un conjunto coordinado de programas, procedimientos, lenguajes y demás. Este suministra a los distintos tipos de usuarios los medios necesarios para describir y manipular los datos almacenados en la base de datos, garantizando seguridad. 
	Se debe poder realizar sobre el conjunto de la bd la creación, la reestructuración y la consulta total.
	Además, sobre ciertos registros se ha de poder insertar, borrar, modificar y consultar de forma selectiva.

Las funciones esenciales son las siguientes:
- **Descripción**
	- Describimos datos con su estructura, sus interrelaciones y sus validaciones. (LDD)
- **Manipulación**
	- Nos permite buscar, añadir, suprimir o modificar datos, lo cual supone definir un criterio de selección, una estructura externa a recuperar, y la posibilidad de acceder a la estructura física. (LMD) 
- **Control**
	- Reúne interfaces de usuarios y suministra procedimientos para el admin. (LCD)

Veamos los tipos de funciones:
- Lenguaje de Definición de Datos
	- Autocontenido y no necesita apoyarse en ningún lenguaje de programación
- Lenguaje de Manipulación de Datos
	- Permisos para referirse a un set de datos
	- Uno mismo actúa como huésped y como autocontenido
	- Mayoría permite diferido y conversacional
	- Programador necesita un LMD: embebido y procedimental
	- Usuario no informático precisa LMD: autocontenido, poco procedimental e interactivo
### Arquitectura ANSI/X3/SPARC
Son organismos de estandarización internacionales para tecnologías de la información
### Arquitectura e independencia físico/lógica
El principal objetivo de las BD es dar esta característica. Esto nos consigue que los mismos datos se presenten de diversas formas según las necesidades del usuario y que el almacenaje de datos, su estructura lógica y los programas sean independientes.