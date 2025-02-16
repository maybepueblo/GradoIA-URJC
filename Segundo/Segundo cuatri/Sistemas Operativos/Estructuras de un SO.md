El nacimiento de un SO proviene de parte de una necesidad de manejar múltiples procesos a la vez, lo que incluye a la interfaz de usuario. 
## Servicios del SO
Nos ofrece un entorno para la ejecución de programas, de cara al usuario:
- **Interfaz de usuario**
	- Usamos interfaces por línea de comando cuando necesitamos un sistema que consuma la menor cantidad de recursos (e.j, un ordenador al cuál solo tendrá acceso personal técnico)
	- Procesos por lotes: .bat (win) o .sh (linux)
	- GUI (gráfico)
- **Ejecución de programas**
- **E/S** -> Sistema nos ofrece la abstracción "fichero" a capas superiores
- **Comunicación entre procesos**
	- Memoria compartida
	- Paso de mensajes
- **Gestión de errores**
	- Falta papel, fallo paridad al leer, etc...

De cara al sistema
- **Seguridad**
	- Tienen que permitir autentificación, para verificar los permisos de los distintos usuarios
## Interfaz
¿Por qué no se considera kernel? Un servidor puede seguir ejecutando procesos sin tener que estar a través de una interfaz, lo que significa que puedo abrir una consola, lanzar procesos, salir la interfaz de memoria y así seguir usando memoria para otros procesos más importantes, lo cuál nos deja a esta interfaz como algo ajeno a nuestro sistema.

## Llamadas al sistema
Proporcionan la interfaz con la que invocar a los servicios ofrecidos por el sistema, ya que deben ejecutarse en modo privilegiado

- **API** -> POSIX (linux) y WIN32 (windows) 
	- Application Program Interface
		- Cómo se accede a estos recursos
	- APIREST
		- Se accede por URLs
	
### Posix
Las llamadas se agrupan en categorías, por ejemplo en POSIX:
- POSIX 1: Core Services (implementa llamadas del ANSI C estándar). Incluyendo:
	- Control y creación de procesos
	- Señales
	- Excepciones float
	- Excepciones por violación de segmento
	- Excepciones por instrucción ilegal
	- Errores de bus
	- Temporizadores
	- Operaciones de ficheros y directorios
	- Tuberías
	- Biblio estándar de C
	- Instrucciones de entrada/salida y de control de dispositivo
- POSIX 1b: extensiones en tiempo real
## Monolíticos
Implementan el núcleo los cuatro componentes fundamentales del sistema operativo, que son la planificación de procesos, la administración de la memoria principal, la administración de ficheros y la gestión de entrada/salida.

Algunos ejemplos son UNIX, tales como FreeBSD, NETBSD y OPENBSD, GNU/Linux y por tanto Android también, DOS, tales como MS-DPS y DR-DOS.
## Microkernel
Disponen de un núcleo que implementa solamente:
- Planificación de procesos
- Mecanismo de comunicación
- Gestión de interrupciones

Existen procesos que se encuentran en modo no-privilegiado, los cuales se ejecutan fuero del espacio del núcleo del sistema operativo e implementan los siguientes componentes:
- Administración de memoria principal

lsmod nos ayuda a saber todos los módulos que tiene tu sistema operativo, para hacer más sencillo el entender para qué sirve 

