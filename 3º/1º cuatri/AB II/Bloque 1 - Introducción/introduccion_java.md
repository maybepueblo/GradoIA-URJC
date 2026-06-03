## Índice
1. [Historia y ecosistema](#1-historia-y-ecosistema)
2. [Compilación y ejecución](#2-compilación-y-ejecución)
3. [Paquetes de Java](#3-paquetes-de-java)
4. [Primer programa: Hola Mundo](#4-primer-programa-hola-mundo)
5. [Comentarios y Javadoc](#5-comentarios-y-javadoc)
6. [Palabras reservadas](#6-palabras-reservadas)
7. [Tipos primitivos y variables](#7-tipos-primitivos-y-variables)
8. [Operadores](#8-operadores)
9. [Control de flujo](#9-control-de-flujo)
10. [Las clases](#10-las-clases)
11. [Detalles de las propiedades](#11-detalles-de-las-propiedades)
12. [Detalles de los métodos](#12-detalles-de-los-métodos)
13. [Arrays](#13-arrays)
14. [Paquetes](#14-paquetes)

---

## 1. Historia y ecosistema

Java fue creado por **James Gosling** en Sun Microsystems. A continuación, los hitos más relevantes de su evolución:

| Año  | Hito |
|------|------|
| 1994 | Lenguaje **Oak** (precursor de Java) |
| 1995 | Lanzamiento de **JDK 1.0** |
| 1996 | Aparece **Xelfi** (origen de NetBeans) |
| 1998 | **J2SE 1.2** |
| 2004 | **J2SE 5.0** y **Eclipse 3** |
| 2007 | **OpenJDK** (versión libre) |
| 2009 | **Oracle compra Sun Microsystems** |
| 2014 | JDK 11 con soporte funcional |
| 2018 | JDK 11 basado en OpenJDK |
| 2020 | **JDK 15** |

---

## 2. Compilación y ejecución

Java sigue un modelo de **compilación en dos fases**:

```
Código fuente (.java)
        │
        ▼
  Compilador (javac)
        │  [compilación correcta]
        ▼
  Bytecode (.class)  ◄──── Máquina Virtual y API de Java
        │
        ▼
  Ejecución en Máquina Virtual (JVM)
        │
        ├── Compilador JIT Hotspot ──► Código objeto nativo
        │
        ▼
     Resultado
```

- El **compilador `javac`** transforma el código fuente `.java` en **bytecode** `.class`, independiente de la plataforma.
- La **JVM** ejecuta ese bytecode. El **compilador JIT (Just-In-Time) Hotspot** optimiza en tiempo de ejecución las partes más usadas, compilándolas a código máquina nativo para mejorar el rendimiento.

**Pasos básicos desde la línea de comandos:**
```bash
javac HolaMundo.java   # compila
java HolaMundo         # ejecuta
```

---

## 3. Paquetes de Java

El JDK se organiza en capas de paquetes:

- **JDK** engloba al **JRE**, que a su vez contiene la JVM.
- Capas principales (de más baja a más alta):
  - **Máquinas virtuales:** Java Hotspot Client/Server Compiler
  - **Paquetes base:** `java.lang`, `java.util` (colecciones, logging, concurrencia, etc.)
  - **Otros paquetes:** Networking, Serialization, Security, New IO, XML/JAXP
  - **Interfaces de integración:** IDL, JDBC, JNDI, RMI, RMI-IIOP
  - **Paquetes de interfaz de usuario:** `java.awt`, `javax` (Swing, Image IO, etc.)
  - **Tecnologías de despliegue:** Java Web Start, Java Plug-in
  - **Herramientas y APIs de desarrollo:** `java`, `javac`, `javadoc`, `jar`, `javap`, etc.
- Todo esto se ejecuta sobre **sistemas operativos** (Linux, Solaris, Windows y otros).

---

## 4. Primer programa: Hola Mundo

```java
/** Programa en Java que muestra un mensaje de bienvenida */
public class HolaMundo {
    // El método en el que comienza la ejecución del programa es main
    public static void main(String[] arg) {
        System.out.println("Hola mundo");
    }
}
```

- El nombre del fichero **debe coincidir** con el nombre de la clase pública: `HolaMundo.java`.
- Todo programa Java arranca en el método **`public static void main(String[] arg)`**.

---

## 5. Comentarios y Javadoc

Java ofrece tres sintaxis de comentario:

```java
/* Comentario
   multilínea */

// Comentario de una sola línea

/** Comentario Javadoc — genera documentación automática.
 *  @author  José Vélez
 *  @version 1.0
 */
```

**Etiquetas Javadoc más habituales en métodos:**

```java
/**
 * Descripción del método.
 * @param  nombre_parámetro  descripción del parámetro
 * @return descripción del valor devuelto
 * @throws NombreClase       descripción de la excepción
 */
```

Para generar la documentación HTML desde la línea de comandos:
```bash
javadoc -author -version HolaMundo.java
```

---

## 6. Palabras reservadas

El conjunto completo de palabras reservadas de Java (no pueden usarse como identificadores):

```
abstract   boolean    break      byte       case
catch      char       class      continue   default
do         double     extend     false      final
finally    float      for        if         implements
instanceof int        interface  long       native
new        null       package    private    public
return     short      static     super      switch
synchronized this     threadsafe transient  true
try        void       volatile   while
```

Clasificadas por uso:

| Categoría | Palabras |
|-----------|----------|
| **Tipos primitivos** | `boolean`, `byte`, `char`, `short`, `int`, `long`, `float`, `double`, `void` |
| **Literales** | `true`, `false`, `null` |
| **Control de flujo** | `if`, `else`, `for`, `while`, `do`, `switch`, `case`, `default`, `break`, `continue`, `return`, `try`, `catch`, `finally` |
| **POO** | `class`, `interface`, `extends`, `implements`, `new`, `this`, `super`, `abstract`, `final`, `static`, `instanceof` |
| **Acceso** | `public`, `private`, `protected` |
| **Otros** | `package`, `import`, `native`, `synchronized`, `volatile`, `transient`, `threadsafe` |

---

## 7. Tipos primitivos y variables

En Java **todos los datos son objetos**, salvo **7 tipos primitivos** añadidos por eficiencia:

### Tipo carácter

| Tipo | Bytes | Descripción | Valor por defecto | Ejemplo |
|------|-------|-------------|-------------------|---------|
| `char` | 2 | Carácter Unicode | `'\u000000'` | `char c = 'ñ';` |

### Tipos numéricos

| Tipo | Bytes | Rango / Descripción | Defecto | Ejemplo |
|------|-------|---------------------|---------|---------|
| `byte`   | 1  | Entero: −128 a 127          | 0      | `byte b = 100;` |
| `short`  | 2  | Entero: −16 384 a 16 383    | 0      | `short s = -8000;` |
| `int`    | 4  | Entero: −2³¹ a 2³¹−1        | 0      | `int i = 1400000;` |
| `long`   | 8  | Entero: −2⁶³ a 2⁶³−1        | 0      | `long l = -53L;` |
| `float`  | 8  | Real (precisión simple)     | +0.0f  | `float x = -1.21f;` |
| `double` | 16 | Real (precisión doble)      | 0.0    | `double pi = 3.14;` |

**Jerarquía de promoción implícita:**
```
byte > short y char > int > long > float > double
```

### Tipo booleano

| Tipo | Bytes | Descripción | Defecto | Ejemplo |
|------|-------|-------------|---------|---------|
| `boolean` | indefinido | `true` / `false` | `false` | `boolean b = true;` |

### Declaración de variables

```java
// Sintaxis general
<tipo> <identificador> [, <identificador>];
<identificador> = <expresión>;
[final] <tipo> <identificador> = <expresión>;

// Ejemplos
int mainCont, auxCont;
mainCont = 2;
int i = 5;
final double PI = 3.1416;   // constante
```

---

## 8. Operadores

### Aritméticos

| Operador | Descripción | Tipo | Ejemplo |
|----------|-------------|------|---------|
| `+` `-`  | Suma / Resta (también unario) | Binario/Unario | `a + b`, `-a` |
| `*` `/`  | Producto / División | Binario | `a * b` |
| `%`      | Resto de división entera | Binario | `a % b` |
| `+=` `-=` `*=` `/=` `%=` | Asignación compuesta | Unario | `a += b` |
| `++` `--` | Pre/post incremento/decremento (solo enteros) | Unario | `a++`, `++a` |

```java
int A = 12;
A *= 2;          // A = 24
int B = A++;     // B = 24, A = 25
```

### Relacionales

| Operador | Descripción | Ejemplo |
|----------|-------------|---------|
| `==` | Igualdad | `a == b` |
| `!=` | Distinto | `a != b` |
| `>` `<` | Mayor / Menor | `a > b` |
| `>=` `<=` | Mayor o igual / Menor o igual | `a >= b` |

### Operaciones a nivel de bit (enteros)

| Operador | Descripción |
|----------|-------------|
| `&` `\|` `^` | AND, OR, XOR bit a bit |
| `~` | Negación binaria (unario) |
| `<<` | Desplazamiento izquierda (rellena con 0) |
| `>>` | Desplazamiento derecha (rellena con bit de signo) |
| `>>>` | Desplazamiento derecha sin signo (rellena con 0) |

```java
int A = 0x5E;     // 94
byte B = -3;
short C = 0b111;  // 7
System.out.println(A | (B & C));  // 95
```

### Booleanos

| Operador | Descripción |
|----------|-------------|
| `&` `\|` | AND / OR (evalúa ambos operandos siempre) |
| `&&` `\|\|` | AND / OR **cortocircuito** (deja de evaluar si el resultado ya es conocido) |
| `^` | XOR |
| `!` | Negación |
| `&=` `\|=` | Asignación con AND / OR |

```java
boolean A = true;
boolean B = false;
boolean C = B && (A || B);  // false — se detiene en &&
boolean D = A | (3 == 2+1); // true
```

---

## 9. Control de flujo

### Ámbitos y sentencias

Un **ámbito** se delimita con `{` y `}`. Las variables declaradas dentro de un ámbito son **locales** a él. Los ámbitos se pueden anidar. Java no permite redeclarar una variable con el mismo nombre en un ámbito hijo.

### `if - else`

```java
if (<expresión booleana>) {
    // rama verdadera
} else if (<expresión booleana>) {
    // rama alternativa
} else {
    // rama por defecto
}
```

### `for`

Preferible cuando el **número de iteraciones se conoce de antemano** y depende de una única condición.

```java
for (int cont = 0; cont < 100; cont++) {
    a = a * B / c;
}
// cont no existe aquí fuera
```

### `while` y `do-while`

Preferibles cuando el número de iteraciones **no está definido a priori** o depende de varias condiciones.

```java
while (a > b) {
    b = D * 25;
    a--;
}

do {
    b = D * 25;
    a--;
} while (a > b);   // se ejecuta al menos una vez
```

### `break` y `continue`

- **`break`**: interrumpe el bucle y sale de él.
- **`continue`**: interrumpe la iteración actual y vuelve a la condición del bucle.
- Ambos pueden combinarse con **etiquetas** para salir de bucles anidados:

```java
externo:
for (...) {
    for (...) {
        if (condición) break externo;
    }
}
```

### `switch`

**Versión clásica** (hasta Java 7, solo enteros; Java 8 añade enums y Strings):

```java
switch (variable) {
    case 5: {
        System.out.println("cinco");
        break;
    }
    case 6: {
        System.out.println("seis");
        break;
    }
    default: {
        System.out.println("Más");
        break;
    }
}
```
> ⚠️ Sin `break`, la ejecución "cae" al siguiente `case`.

**Versión moderna** (Java 12+, con flechas; Java 18+ añade match de tipos y guardas):

```java
// Como sentencia
switch (expresión) {
    case match [when cond], match2 -> sentencia;
    default -> sentencia;
}

// Como expresión (devuelve valor con yield)
return switch (expresión) {
    case match -> valorDevuelto;
    case match2 -> { yield otraExpresión; }
    default -> valorPorDefecto;
};
```

---

## 10. Las clases

### Definición de una clase

```java
[modificadorClase] class <Identificador> [parámetros] [herencia] [excepciones] {
    // propiedades, métodos, clases internas, bloques de inicialización
}
```

- Los nombres de clase se escriben en **UpperCamelCase**: `Coche`, `JuegoCoches`.
- Los nombres de miembros se escriben en **lowerCamelCase**: `velocidad`, `acelerar`.
- Los nombres de paquetes se escriben en **minúsculas**.

### Referencias a objetos

```java
Coche a, b, c;       // se declaran tres referencias (valen null)
a = new Coche();     // se crea un objeto Coche
b = new Coche();     // se crea otro
c = a;               // c apunta al mismo objeto que a
```

| Tipo | Bytes | Descripción | Valor por defecto |
|------|-------|-------------|-------------------|
| referencia a objeto | 4 | Apunta a un objeto que cumple un tipo | `null` |

### Propiedades (campos)

Variables declaradas dentro de la clase que dotan de **estado** al objeto.

```java
class Coche {
    boolean enMarcha;
    int velocidad;
    Rueda r1 = new Rueda();
    Rueda r2 = new Rueda();
}

class Rueda {
    int presion = 2000;
    float radio = 6.28f;
}
```

### Métodos

Funciones definidas dentro de la clase que se invocan sobre objetos o sobre la propia clase.

```java
class Coche {
    void parar() { ... }                      // sin parámetros, sin retorno
    void acelerar(int incremento) { ... }     // con parámetro
    float reparar(float dinero, Taller t) {   // varios parámetros y retorno
        ...
        return dinero - precio;
    }
}
```

### Acceso a miembros

```java
// Miembro de otro objeto (punto como separador)
coche1.acelerar(10);

// Miembro del propio objeto (identificador directamente, o this)
velocidad += incremento;
t.arreglar(this);   // this = referencia al propio objeto
```

### Control de acceso

| Modificador | Clase | Paquete | Todos |
|-------------|-------|---------|-------|
| `public`    | ✅    | ✅      | ✅    |
| *(sin mod — friendly)* | ✅ | ✅ | ❌ |
| `private`   | ✅    | ❌      | ❌    |

- Las **propiedades** suelen ser `private`.
- Los **métodos públicos** son la interfaz de la clase.
- Los **métodos privados** son auxiliares internos.

### Clases públicas

- Una clase `public` es visible desde otros paquetes.
- **Solo puede haber una clase `public` por fichero** y su nombre debe coincidir con el del fichero.

```java
// Fichero: Coche.java
class Rueda { ... }        // visible solo en el paquete

public class Coche { ... } // visible desde cualquier paquete
```

### Clases internas

Una clase puede definirse dentro de otra. Si se declara `private`, solo es visible dentro de la clase contenedora.

```java
public class Stack {
    private class Node {
        Node next;
        int value;
    }
    private Node top = new Node();
}
```

### Ejemplo completo

```java
public class Coche {

    class Rueda {
        private int presion = 2000;
        private float radio = 6.28f;
        public float dameRadio() { return radio; }
        public void subePresion() { presion += 10; }
    }

    private boolean enMarcha;
    private int velocidad;
    private Rueda ruedaRepuesto = new Rueda();

    public void parar() {
        velocidad = 0;
        enMarcha = false;
    }

    public Rueda dameRueda() { return ruedaRepuesto; }

    public void acelerar(int incremento) {
        velocidad += incremento;
        enMarcha = true;
    }

    public float reparar(float dinero, Taller t) {
        float precio = t.precioReparar(this);
        if (precio < dinero) {
            parar();
            t.arreglar(this);
        }
        return dinero - precio;
    }
}

public class Taller {
    public float precioReparar(Coche c) {
        return 100 * c.dameRueda().dameRadio();
    }
    public void arreglar(Coche c) {
        c.dameRueda().subePresion();
    }
}
```

---

## 11. Detalles de las propiedades

### Propiedades privadas y getters/setters

Las propiedades suelen ser `private`. Para exponerlas de forma controlada se usan métodos **getter** y **setter**, que permiten validar los valores y preservar el **invariante** de la clase.

```java
class Coche {
    private int speed;

    public int getSpeed() {
        return speed;
    }

    public void setSpeed(int speed) {
        if (speed > 120)      this.speed = 120;
        else if (speed < 0)   this.speed = 0;
        else                  this.speed = speed;
    }
}
```

### Propiedades `final`

- Una propiedad `final` es una **constante** durante la vida del objeto; su valor no cambia.
- Las referencias `final` no pueden reasignarse, aunque el objeto al que apuntan sí puede cambiar su estado interno.
- Las variables `final` de tipo primitivo pueden declararse `public` sin riesgo.

```java
class Coche {
    public final int numRuedas = 4;         // constante de instancia
    private final Rueda r = new Rueda();    // referencia constante
}
```

En UML se representa con la restricción `{readOnly}`.

### Propiedades estáticas (`static`)

Las propiedades `static` pertenecen a la **clase**, no a cada objeto. Son compartidas por todas las instancias.

```java
class Coche {
    private boolean enMarcha;           // propiedad de instancia
    public final static double PI = 3.14; // propiedad de clase (constante global)
}

// Acceso desde fuera:
System.out.println(Coche.PI);
System.out.println(unCoche.numRuedas);
```

En UML, los miembros estáticos se **subrayan**.

### Otros modificadores de uso

- **`transient`**: la propiedad **no persiste** aunque el objeto tenga capacidad de persistencia (serialización).
- **`volatile`**: la propiedad se mantiene en **memoria principal** (no en caché del procesador), útil en contextos multihilo para evitar inconsistencias.

---

## 12. Detalles de los métodos

### Paso de parámetros

En Java el paso de parámetros es **siempre por valor**: se copia el contenido de la variable.

- **Tipos primitivos**: se pasa una copia del valor → no afecta al original.
- **Referencias a objetos**: se pasa una copia de la referencia → el estado del objeto sí puede modificarse desde el método.

### Métodos de instancia vs. métodos de clase

| Tipo | Cómo se declara | Sobre qué se invoca |
|------|-----------------|---------------------|
| De instancia | (sin `static`) | Sobre un objeto |
| De clase (estático) | `static` | Sobre la clase |

```java
class Coche {
    private int velocidad;
    private static int cochesCreados;

    // Método estático — no puede acceder a 'velocidad'
    public static void sumarCoche() {
        cochesCreados++;
    }

    // Métodos de instancia
    public void acelerar() { velocidad++; }
    public void parar()    { velocidad = 0; }
}

// Invocación externa
Coche.sumarCoche();   // método de clase
```

> Dentro de un método `static` **no se pueden usar propiedades de instancia** (no hay objeto).

### El método `main`

Todo programa Java arranca en un método estático especial:

```java
public static void main(String[] args) { ... }
```

### Sobrecarga de métodos (*overloading*)

Una clase puede tener **varios métodos con el mismo nombre** siempre que difieran en el tipo o número de parámetros.

```java
class Coche {
    public void acelerar(int v)        { velocidad += v; }
    public void acelerar(boolean on)   { velocidad += 60; }
}
```

### El constructor

- Se invoca con `new NombreClase(...)`.
- **No tiene tipo de retorno**.
- Si no se define ninguno, Java añade un **constructor por defecto** vacío.
- Se pueden definir **varios constructores** (sobrecarga), pero no dos con los mismos parámetros.
- Desde un constructor se puede llamar a otro de la misma clase con `this(parámetros)`.
- En el constructor se pueden inicializar incluso propiedades `final`.

```java
class Coche {
    public final int numRuedas;
    private boolean enMarcha;
    private int velocidad;

    public Coche(int velInicial, boolean on) {
        numRuedas = 4;
        velocidad = velInicial;
        this(on);           // llama al constructor Coche(boolean)
    }

    public Coche(boolean on) {
        enMarcha = on;
    }

    public Coche() { }      // constructor por defecto explícito
}
```

### Destrucción de objetos y finalizadores

- Java gestiona la memoria automáticamente mediante el **recolector de basura** (*garbage collector*), que libera los objetos sin referencias activas en segundo plano.
- El método **`void finalize()`** se ejecuta antes de liberar el objeto (cierre de ficheros, avisos a otros objetos...).
- Desde **Java 9 está desaconsejado** (`deprecated`) por la no determinismo en su momento de ejecución.

### Otros modificadores de métodos

| Modificador | Efecto |
|-------------|--------|
| `native` | Implementado en código nativo (C, C++) mediante JNI |
| `synchronized` | Solo un hilo puede ejecutarlo a la vez por objeto |
| `strictfp` | Aritmética flotante independiente del procesador (portabilidad) |

---

## 13. Arrays

### Declaración

```java
int[]   vector;
Coche[] parking;
```

### Inicialización

```java
// Tamaño fijo, valores por defecto (0 o null)
int[]   vector  = new int[25];
Coche[] parking = new Coche[N];

// Implícita con valores
int[]  fib    = {1, 1, 2, 3, 5, 8, 13};
char[] nombre = {'j', 'u', 'a', 'n'};
```

- Si no se inicializa, el valor es `null`.
- Cada posición se rellena con el valor por defecto del tipo (`0`, `false`, `null`...).
- **Una vez creado, el array no puede redimensionarse.**
- Los índices van de `0` hasta `longitud - 1`.

### Acceso a elementos

```java
int[] vector = new int[25];

for (int x = 0; x < 25; x++)
    vector[x] = 3;

int resultado = 0;
for (int x = 0; x < 25; x++)
    resultado += vector[x];
```

### Arrays de arrays (matrices y arrays irregulares)

```java
// Matriz rectangular 25×30
Coche[][] tabla = new Coche[25][30];
for (int x = 0; x < 25; x++)
    for (int y = 0; y < 30; y++)
        tabla[x][y] = new Coche();

// Arrays irregulares (filas de distinto tamaño)
int[][] vectores = new int[2][];
vectores[0] = new int[5];
vectores[1] = new int[8];

for (int x = 0; x < vectores.length; x++)
    for (int y = 0; y < vectores[x].length; y++)
        vectores[x][y] = -1;
```

La propiedad **`length`** devuelve la dimensión del array.

### Clase `java.util.Arrays`

Ofrece métodos estáticos de utilidad sobre arrays:

| Método | Descripción |
|--------|-------------|
| `sort(T[])` | Ordena el array |
| `binarySearch(T[], T)` | Búsqueda binaria (array ordenado) |
| `copyOf(T[], int)` | Copia con nueva longitud |
| `copyOfRange(T[], int, int)` | Copia de un rango |
| `equals(T[], T[])` | Compara dos arrays |
| `fill(T[], T)` | Rellena con un valor |
| `toString(T[])` | Representación en cadena |

---

## 14. Paquetes

### Definición

Los paquetes agrupan clases relacionadas y se corresponden con **directorios** del sistema de ficheros. Se pueden anidar usando el punto (`.`) como separador.

```java
// Primera línea del fichero
package urjc.util.automovilismo;

public class Parking { ... }
```

- Nombre de fichero: `Parking.java`
- Ruta: `urjc/util/automovilismo/Parking.java`

### CLASSPATH

La variable de entorno `CLASSPATH` (o el parámetro `-classpath` de la JVM) indica dónde buscar la raíz de los paquetes.

### Importar clases de otros paquetes

```java
package urjc.util.automovilismo;

import vehiculos.utilitarios.Coche;      // importa una clase concreta
import vehiculos.camiones.*;             // importa todas las clases del paquete

public class Parking {
    Coche c = new Coche();
    Camion c1 = new Camion();
    // nombre completamente calificado (sin import)
    vehiculos.agricolas.Tractor t = new vehiculos.agricolas.Tractor();
}
```

### Visibilidad entre paquetes

- Dentro de un paquete se comparten los miembros **friendly** (sin modificador de acceso).
- **El anidamiento de paquetes no implica visibilidad adicional**: un subpaquete no puede acceder a los elementos friendly de su paquete padre y viceversa.

```
paquete vehiculos.utilitarios
│  Coche  +peso : int       → visible desde cualquier lado (public)
│  Rueda  ~radio : int      → visible solo dentro de vehiculos.utilitarios

paquete automovilismo
│  Taller                   → NO puede ver radio de Rueda (distinto paquete)
```

---

## Convenciones de nomenclatura en Java

| Elemento | Convención | Ejemplo |
|----------|-----------|---------|
| Paquetes | todo minúsculas | `urjc.util.automovilismo` |
| Clases | UpperCamelCase | `HolaMundo`, `JuegoCoches` |
| Miembros (props/métodos) | lowerCamelCase | `velocidad`, `dameVelocidad()` |
| Constantes | MAYÚSCULAS_CON_GUIÓN | `MAX_VELOCIDAD`, `PI` |

---

*Documento elaborado a partir de las diapositivas del Tema 2 — Introducción al lenguaje Java, Programación Orientada a Objetos, URJC.*
