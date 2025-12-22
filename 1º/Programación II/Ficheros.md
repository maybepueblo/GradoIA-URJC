Conocemos a los ficheros por ser una colección de datos almacenados bajo el mismo nombre en la memoria secundaria. Con ellos, se puede almacenar grandes cantidades de información teniendo la plena tranquilidad de que estos perpetuarán en el tiempo y estarán identificados unívocamente.

¿Su principal uso? Ser usados como fuente de otro programa.

Podemos clasificar estos archivos de la siguiente forma:

- **[[Ficheros de texto]]** --> Son datos formados por caracteres de tipo [ASCII]([ASCII - Wikipedia, la enciclopedia libre](https://es.wikipedia.org/wiki/ASCII)). Estos pueden ser leídos y modificados por el usuario. 
- **[[Ficheros binarios]]** --> Datos almacenados a través de [números binarios]([Sistema binario - Wikipedia, la enciclopedia libre](https://es.wikipedia.org/wiki/Sistema_binario)). En contraposición a los datos anteriores, estos no pueden ser leídos ni escritos por el usuario.

**Tipo de acceso a los ficheros**

Tenemos dos diferentes tipos de accesos dentro de la programación en C:

- Acceso secuencial --> Para leer la posición i de un fichero, es necesario haber leído todas las posiciones menores a i ( leer todas las posiciones < i ). En el caso de C, el acceso a los [[Ficheros de texto]] es secuencial.
- Acceso directo --> Es posible posicionarnos en cualquier dato del fichero sin pasar por los datos que lo preceden. En C, los [[Ficheros binarios]] permiten acceso directo.