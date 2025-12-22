Ficheros basados en el código ASCII, pueden ser leídos y escritos por el usuario.

Las operaciones que conforman a los ficheros de texto son las siguientes: 

- Abrir --> *fopen*
- Leer --> *fscanf*
- Escribir --> *fprintf*
- Cerrar --> *fclose*

La comunicación de un fichero establece un canal de comunicación entre un programa y el fichero. Esto se hace a través de FILE * pFichero = fopen(ruta, modo);

En esta expresión mostrada, tenemos lo siguiente:

- pFichero --> variable que describe al fichero.
- ruta --> ruta completa donde se escribirá/leerá el fichero.
- modo --> indicador de si el texto es de tipo ASCII o binario, para permitir si podemos escribir o solo leer.

| Modo | Descripción                                                                                                                 |
| ---- | --------------------------------------------------------------------------------------------------------------------------- |
| r    | Abre el fichero para leer de él. El fichero debía de existir y el cursor se sitúa al comienzo del mismo.                    |
| r+   | Permite escribir y leer en el fichero ya existente.                                                                         |
| w    | Abre el fichero para escribir. Si existe, borra su contenido. Si no existiese, lo crea.                                     |
| w+   | Igual que el anterior pero esta vez se permite lectura.                                                                     |
| a    | Abre el fichero para añadir al final. Si no existe, se crea, y si existe, se sitúa el cursor al final del fichero original. |

##### fopen
La función dada anteriormente *fopen* devuelve un FILE * . Es un puntero a una estructura FILE definida en stdio.h que almacena toda la información del archivo. 

#### Fallos al abrir un fichero

Se pueden cometer ciertos fallos como los siguientes:
- Abrir un fichero inexistente en modo lectura 
- No tener permiso de escritura y abrirlo en modo de escritura
- Abrir un fichero inexistente y la carpeta donde se va a crear no posee permisos de escritura

**CONSEJO**
- La función perror ayuda a identificar el error en cualquier operación con ficheros.

```
	FILE *f = fopen("prueba.txt", "r");
	if (f == NULL) {
		perror("Error en apertura: ");
	}
```

