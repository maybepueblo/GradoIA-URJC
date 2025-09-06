A continuación, se adjunta una explicación detallada de la práctica de fractales realizada para el curso de Estructura de Datos en GIA de la URJC.

#### Comienzo

Se nos aporta por parte del profesor unos archivos, que también estarán adjuntados en este repositorio, `Bitmap` y `colourScale`, los cuales son necesarios para finalizar esta práctica.

Asimismo, como toma de contacto, se brinda un pequeño ejercicio a realizar siguiendo este código:

```c
#include <stdio.h>
#include "Bitmap.h"
int main()
{
int i, j;
int ancho = 640;
int alto = 480;
Bitmap gradiente = createBitmap("gradiente.bmp", ancho, alto, 3);
for(i = 0; i < ancho; i++) {
	for(j = 0; j < alto; j++) {
	putPixel(&gradiente, i, j, (i/10)% 64);
	}
}
saveBitmap(&gradiente);
}
```

No profundizaré en detalle en él, pero aporta una base necesaria para resolver el problema que nos atañe, así que permitidme dar una breve introducción.

En estas líneas de código nos importa en principio el doble bucle `for`, cuya función es, en esencia, recorrer cada pixel de la imagen de tamaño 640x480 que estamos creando para poder pintarla.

Luego, en dicho pixel, lo que hacemos es pintar con cierto color, esto se hace a través de la función `putPixel`, una herramienta de suma importancia de cara a nuestro problema posterior, veamos cómo funciona, empezando por su implementación en c:

```c
void putPixel(Bitmap* bmp, int x, int y, char i)  
{  
    if(i<65) {  
       putPixelRGB(bmp, x, y, Rs[i], Gs[i], Bs[i]);  
    }  
    else {  
       putPixelRGB(bmp, x, y, 0, 0, 0);  
    }  
}
```

Como podemos observar, de argumentos recibe el archivo en el que estamos pintando, la posición en la que estamos y el color. Este color se calcula a través de otra función: `putPixelRGB`, pero por no complicar demasiado el entendimiento de estas funciones, vamos a entenderla brevemente. Nuestra i sirve como un punto de referencia a la iteración en la que estamos, es decir, el procesado que le vamos a dar a nuestro código.

Esto luego se traduce en una posición de unas listas definidas en `colourScale`, componiendo finalmente un color en el formato RGB (255, 0, 255). Si no nos encontramos entre las iteraciones deseadas, directamente ponemos el pixel en negro.

Teniendo esto ya explicado, podemos proseguir a lo que nos concierne, el conjunto de Mandelbrot.

#### Conjunto de Mandelbrot

Entendemos el conjunto de Mandelbrot como el resultado a la siguiente sucesión:
$$
\begin{cases}z_0=0 & n = 0 \\ z_{n+1} = z²_n + c & n > 0 \end{cases}
$$
Donde `c` es un complejo, `z` otro complejo definido como 0 + 0i y `n` como el **número de iteración** (importante).

Así sabemos que z viene dado por c. Veamos el ejemplo que nos dan con c = 1 + 0i:
$$\begin{align}	
z_0 = 0 \\
z_1 = z^2_0 + c = 0 + 1 = 1 \\
z_2 = z^2_1 + c = 1^2 + 1 = 2 \\
z_3 = z^2_2 + c = 2² + 1 = 5 \\
z_4 = z^2_3 + c = 5² + 1 = 26 \\
\end{align}$$
Se dice que c pertenece al conjunto de Mandelbrot únicamente cuando al realizar la sucesión se encuentra acotado (oscila entre dos valores). En el caso de ejemplo de arriba podemos ver que esto no es así, así que diríamos que c = 1 + 0i no pertenece al conjunto de Mandelbrot. Podemos poner ahora los otros dos casos para que veamos que estos **sí** que están acotados y por ende, sí que están incluidos dentro del conjunto de Mandelbrot.

![[Pasted image 20241019193748.png]]

Como vemos, estas sucesiones sí están acotadas y por ende, podemos decir que sí pertenecen. 

Vamos a visualizar este conjunto a través de un algoritmo de tiempo de escape, que nos asigna un color a cada complejo en el espacio 2D en función de la iteración en la que se nota si es divergente (es decir, que no pertenece al conjunto). Si pertenece, lo dejaremos en negro, haciendo un dibujo to chulo como resultado (después de haberlo sufrido programando).

Antes que nada, no tenemos manera de usar complejos en este proyecto. Hemos de definir a los complejos sirviéndonos de los TADS.

En este caso, simplemente voy a adjuntar el código con el que he generado dichos complejos pero no entraré en detalle acerca de cómo los he implementado.

##### Complejos

**Complejos.h**
```c
typedef struct {  
    double real;  
    double imag;  
} tComplejo;  
  
// Constructora generadora  
tComplejo CrearComplejo(double real, double imag);  
  
// Constructoras no generadoras  
tComplejo Sumar(tComplejo a, tComplejo b);  
tComplejo Restar(tComplejo a, tComplejo b);  
tComplejo Multiplicar(tComplejo a, tComplejo b);  
tComplejo Dividir(tComplejo a, tComplejo b);  
tComplejo Conjugar(tComplejo a);  
tComplejo I();  
  
// Observadoras selectoras  
double ObtenerReal(tComplejo a);  
double ObtenerImag(tComplejo b);  
  
// Observadora no selectora  
double CalcularModulo(tComplejo a);
```

**Complejos.c**
```c
#include "complejos.h"  
#include <math.h>  
  
// Constructora generadora  
tComplejo CrearComplejo(double re, double im) {  
    tComplejo complejo;  
    complejo.real = re;  
    complejo.imag = im;  
    return complejo;  
}  
  
// Constructoras no generadoras  
tComplejo Sumar(tComplejo a, tComplejo b) {  
    return CrearComplejo(a.real + b.real, a.imag + b.imag);  
}  
  
tComplejo Restar(tComplejo a, tComplejo b) {  
    return CrearComplejo(a.real - b.real, a.imag - b.imag);  
}  
  
tComplejo Multiplicar(tComplejo a, tComplejo b) {  
    double re = a.real * b.real - a.imag * b.imag;  
    double im = a.real * b.imag + a.imag * b.real;  
    return CrearComplejo(re, im);  
}  
  
tComplejo Dividir(tComplejo a, tComplejo b) {  
    double denom = b.real * b.real + b.imag * b.imag;  
    if (denom == 0) {  
        return CrearComplejo(0, 0);  
    }  
    double re = (a.real * b.real + a.imag * b.imag) / denom;  
    double im = (a.real * b.imag - a.imag * b.real) / denom;  
    return CrearComplejo(re, im);  
}  
  
tComplejo Conjugar(tComplejo a) {  
    return CrearComplejo(a.real, -a.imag);  
}  
  
tComplejo I() {  
    return CrearComplejo(0, 1);  
}  
  
// Observadoras selectoras  
double ObtenerReal(tComplejo a) {  
    return a.real;  
}  
  
double ObtenerImag(tComplejo a) {  
    return a.imag;  
}  
  
// Observadoras no selectoras  
double CalcularModulo(tComplejo a) {  
    double square_root = sqrt(a.real * a.real + a.imag * a.imag);  
    return square_root;  
}
```

##### Realización de la práctica

Ahora, adjunto primero el código finalizado de la práctica, para posteriormente ir explicando lo relevante para entender cómo funciona mi implementación:

```c
#include "complejos.h"  
#include <stdio.h>  
#include "Bitmap.h"  
  
int main() {  
    int i, j;  
    int ancho = 640;  
    int alto = 480;  
    Bitmap gradiente = createBitmap("mandelbrot.bmp", ancho, alto, 3);  
    for (i = 0; i < ancho; i++) {  
        for (j = 0; j < alto; j++) {  
            int maxIteraciones = 64;  
            tComplejo z = CrearComplejo(0, 0);  
            tComplejo c = CrearComplejo(((double) i / 160 - 2.5),                     ((double) j / 160 - 1.5));  

            int indice = 0;  
            int comprobador = 0; 
            while (comprobador == 0 && indice < maxIteraciones) {  
                double limiteModulo = 2.0;
                z = Sumar(Multiplicar(z, z), c); 
                if (CalcularModulo(z) > limiteModulo) {  
                    comprobador = 1;  
                }  
                indice++;  
            }  
            putPixel(&gradiente, i, j, (char)indice);  
        }  
    }  
    saveBitmap(&gradiente);  
}
```

Empecemos:

El principio no varía prácticamente, sólo he cambiado que he introducido el TAD de complejos que creé y he cambiado el nombre del archivo que crea el programa.

En cambio, empieza verdaderamente el cambio cuando entramos a nuestro bucle que recorre cada pixel de nuestra imagen 640x480.

Como se puede ver, definimos el máximo de iteraciones que para esta práctica **por definición** será como mucho de 64.

Luego, creo los complejos z y c. Como se puede ver z viene vació y c viene dado según una fórmula un poco peculiar. Esto de hecho viene en relación con los píxeles, es decir, con nuestra imagen, para hallar la equivalencia entre complejo y pixel. 

Esto lo hacemos sabiendo que el origen (0,0) es la esquina superior izquierda, teniendo que a cada pixel de la imagen en posición (x, y) le corresponde el complejo (x/(640/4)-2.5) + (y/(480/3)-1.5) o simplificado: (x/160 - 2.5) + (y/160-1.5).

Ahora, antes que nada, tenemos que preguntarnos, ¿cómo sabemos si una sucesión es divergente o no? Aquí, sabemos (según datos externos) que los puntos del plano complejo cuyo módulo es superior a 2 no pertenecen al conjunto. Por lo tanto, sólo necesitamos encontrar un elemento de la sucesión que verifique:
$$|z_n|>2$$
Por ende, si el valor de módulo de pasa de 2, le asignamos el número de iteración al color del punto en el que estamos.

Esto en el código lo hacemos muy fácil dentro de este segmento de código:

```c
	int indice = 0;  
    int comprobador = 0; 
    while (comprobador == 0 && indice < maxIteraciones) {  
        double limiteModulo = 2.0;
        z = Sumar(Multiplicar(z, z), c); 
        if (CalcularModulo(z) > limiteModulo) {  
	        comprobador = 1;  
        }  
        indice++;  
    }  
putPixel(&gradiente, i, j, (char)indice);  
```

Aquí, definimos el índice, un comprobador y establecemos la condición del while: que nuestro comprobador esté a cero (para decir si se pasa o no de módulo) y que no nos pasemos de las iteraciones máximas de 64.

Dentro del bucle, definimos el límite del módulo para que esté en el conjunto la sucesión, y lo evaluamos en un if tras haber calculado la sucesión de z con esa línea de código que pone `z = Sumar(Multiplicar(z, z), c);` que en realidad, es básicamente hacer esto:
$$z = z*z+c=z²+c$$
Lo que es exactamente igual a la sucesión que comentámos anteriormente.

Volviendo a la comparación, revisamos que el módulo sea menor a 2, si no lo es, salimos y ponemos el pixel con el color basado en el índice de iteración en el que estamos, si lo fuese, seguimos, dejando ese pixel en negro. 

Así tenemos finalmente todo el código y debería crearte en tu cmake una imagen igual a la siguiente:

![[Pasted image 20241019200221.png]]

Y esto es todo... ¡gracias por leerme!