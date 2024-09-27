 Veamos cómo hacer acopio de los tipos enumerados y de los registros en pos de facilitar la implementación de varios tipos de datos. Esto nos es útil, para por ejemplo añadir todos los datos que conforman el historial médico de un paciente.

En este tema, usaremos *enum* y *struct* para favorecer al programador y que los use posteriormente para satisfacer ciertas necesidades.

#### Tipos enumerados

Es un tipo de dato definido por el programador, y su rango de valores se consideran una serie de constantes con valores enteros comenzando desde 0.

```
enum NOMBRE { 
	VALOR1, // toma valor 0 
	VALOR2, // toma valor 1 
	VALOR3 // toma valor 2 
};
```

En este caso, como no tenemos puesto ningún valor, el propio IDE asumirá valores a partir de cero hasta tantos valores tengamos.

```
enum NOMBRE { 
	VALOR1 = 1, // toma valor 1 
	VALOR2 = 2, // toma valor 2 
	VALOR3 = 3 // toma valor 3 
};
```

Ahora sí que sí, como vemos, podemos darle un valor que nosotros queramos. 

Si ahora quisiésemos declarar el valor de una variable teniendo en cuenta un enum previamente declarado, la sintaxis es simple, donde referenciamos directamente al valor que buscamos darle (sea en un interruptor por ejemplo el valor ENCENDIDO). En este caso, si ENCENDIDO dentro del enum corresponde al valor 0, entonces tendremos que en la variable donde hemos asignado el estado del interruptor, tendrá el mismo valor que la variable que se halla en el *enum*.

```
enum interruptor { 
	ENCENDIDO, // toma valor 0 
	APAGADO // toma valor 1 
}; 

enum interruptor varInterruptor; 
varInterruptor = ENCENDIDO; // Si ahora imprimimos varInterruptor, veríamos un 0 por consola, ya que toma literalmente el valor de enumerando que toma.
```

Finalmente, ¿qué tal si vemos un par de ejemplillos hechos en C para ilustrar algunos de los usos que tiene esta forma de representar datos? Si quieren más información, cabe destacar que la [[Práctica 2 - Agenda]] amplía en el uso de esto.

```
int showingENUM() {  
    enum tipoEstados {  // Definimos los Estados que vamos a usar aquí
        SOLIDO,  // Valor = 0
        LIQUIDO,  // Valor = 1
        GASEOSO  // Valor = 2
    };  
    enum tipoEstados estado; // Declaramos la variable estado  
    estado = LIQUIDO;  // estado = 1
    printf("El estado es %i", estado); // El estado es 1 
    return 0;  
}  
  
enum tipoResultado {  // Podemos también definirlo fuera de un main o de una función para facilitar que se use en todos lados
    DERROTA = 0,  
    EMPATE = 1,  
    VICTORIA = 3  
};  

void imprimeResultado(enum tipoResultado res) {  
    printf("Resultado %i", res);  
}  
  
int enum2() {  
    enum tipoResultado resultado = VICTORIA;  
    imprimeResultado(resultado);  
}
```


#### Estructuras/Registros

Es lo que llamamos un *struct* que puede parecer un array, pero es mejor, ya que por ejemplo nos brinda la posibilidad de que los datos que contiene sean de tipos diferentes. Es así un tipo de datos definido por el programador. 

Tenemos que declarar una variable struct tenemos primero que definir su tipo. Veamos una sintaxis muy básica:

```
struct nombreStruct { 
	tipo campo1; 
	tipo campo2; 
	tipo campo3; 
};
```

Solo estamos definiendo el tipo de dato, no declaramos ninguna variable ni reservamos memoria. Se define así el nombre del *struct* y cada campo del mismo. 

Ya luego podemos declarar la variable y acceder a los campos del struct con el operador "."

Veamos un par de ejercicios que ilustran su uso:

```
  
#define MAX 50  

// Definimos el struct como vemos aquí y tal y como indicaba el ejemplo
struct tipoPersona {  
    char nombre[MAX]; // Damos un char que tiene un tamaño máximo de 50
    int edad; // La edad de la persona
    float salario;  // Su salario
};  
  
void pruebaPersona(struct tipoPersona persona) {  
    strcpy(persona.nombre, "Griezmann"); // Función de la librería <string.h>  
    printf("DENTRO DE FUNCION: Nombre %s, Edad %i\n", persona.nombre, 
    persona.edad);  // Imprimimos ahora los datos con el operador "." tal y como     comentábamos antes
}  

int main() {
	struct tipoPersona persona;
	pruebaPersona(persona);
	return 0;
}
```
##### typedef

El typedef nos permite renombrar un tipo de datos en C. No define un tipo, más bien da un sinónimo para uno que ya exista. Tiene que aparecer siempre antes de cualquier variable del tipo a redefinir. Se suele meter así fuera del main. Veamos algún que otro ejemplo para mostrarlo de forma más didáctica:

```
// Como vemos, lo usamos antes que nada
typedef struct {  
    char nombre[MAX];  
    int edad;  
    float salario;  
} tipoPersona2;  


void reseteaPersona(tipoPersona2 *persona) {  
    strcpy(persona->nombre, "Griezmann");  
	printf("DENTRO DE FUNCION: Nombre %s, Edad %i\n", persona->nombre,               (*persona).edad);  
}  

// Aquí ya usamos todo tal y como vimos antes, pero con un struct que usa un typedef
int main() {  
    tipoPersona2 persona;  
    strcpy(persona.nombre, "Vinicius");  
    persona.edad = 30;  
    persona.salario = 2000.50;  
    reseteaPersona(&persona);  
    printf("Nombre: %s, Edad %i", persona.nombre, persona.edad);  
    return 0;  
}
```

El typedef nos sirve para mejorar lo legibles que son nuestros códigos, haciendo que al profesor le duela menos la cabeza como consecuencia.

##### Otros detalles de las estructuras

Hay algún que otro detalle que nos puede interesar a la hora de hablar de estructuras, veamos algún que otro. 

- El operador para acceder es el punto pero también tenemos el operador `->` que nos permite acceder a los campos a partir de un puntero a la propia escritura. 
- Es posible copiar el contenido de dos estructuras con un operador de asignación, pero si algún dato de la estructura es un puntero, pues el resultado puede no ser el que queremos que sea.
- Se pueden utilizar como argumento o como tipo de retorno en funciones, si se pasa por valor se copia la estructura, a no ser que usemos punteros. Así, recomendamos no pasar como parámetro la copia de estas estructuras ya que son mu grandes y desperdician memoria del cacharro.
- Por si no fuese poco, podemos también crear arrays de estructuras y así mismo podemos reservar una estructura en memoria dinámica (luego hay que acordarse de liberarla). No obstante si alguno de los campos es un puntero, debemos reservar memoria para él, ya que no basta con la memoria de la estructura. 