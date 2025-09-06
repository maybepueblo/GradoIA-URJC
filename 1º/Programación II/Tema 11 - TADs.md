>[!NOTE] Tipo Abstracto de Datos
>Colección de valores con ciertas operaciones sobre ellos definidos mediante una especificación independiente de cualquier implementación.
>
>Los TADs se usan sin necesidad de conocer como se implementan, se conoce su especificación.

Usarlos tiene las siguientes ventajas:

- **Facilidad de uso** No necesitamos conocer la implementación.
- **Simplifación y mantenimiento** Operaciones como correción de errores o mejoras pues no afectan a quienes usan el TAD.
- **Reusabilidad** Encapsular datos y funcionalidad, no arrastra dependencias.

#### Especificación de TADs

Debe de ser independiente de la implementación. La especificación de TADs de manera informal se hace con lenguaje natural e incluye los siguientes elementos:

- Conjunto de valores a almacenar
- Declaración de encabezamiento de operaciones: parámetros de entrada y salida.
- Descripción de cada operación.
- Posibles excepciones.

Propiedades de la especificación de un TAD:

- **Precisión** se indica únicamente lo imprescindible.
- **Generalidad** la especificación puede ser adaptable a diversos contextos.
- **Legibilidad** ha de ser sencilla de comprender.
- **No ambigüedad** no debe dar lugar a varias interpretaciones.

#### Ejemplo TADs

Veamos un ejemplo para implementarlo en C. En nuestro caso, vamos a crear un TAD llamado `Fecha`. Una vez tengamos creado el fichero que usaremos, hemos de crear en él el fichero *Fecha.h*, donde tendremos la siguiente información:

```
//  
// Created by pablo on 5/9/2024.  
//  
  
#ifndef CLASE11PROG_FECHA_H  
#define CLASE11PROG_FECHA_H  
  
typedef struct {  
    int dia;  
    int mes;  
    int anyo  
} FechaTipo;  
  
FechaTipo *creaFecha(int dia, int mes, int anyo);  
FechaTipo creaFechaEstatico(int dia, int mes, int anyo);  
  
int dameDia(FechaTipo *fecha);  
  
int dameMes(FechaTipo *fecha);  
  
int dameAnyo(FechaTipo *fecha);  
  
void imprimeFecha(FechaTipo *fecha);  
  
/*  
FechaTipo diferenciaEntreFechas(int dia, int mes, int anyo);  
  
FechaTipo sumaDias(int dia, int mes, int anyo);  
  
FechaTipo obtenerDia(int dia, int mes, int anyo);  
  
FechaTipo convierteFechaTexto(int dia, int mes, int anyo);  
*/  
  
#endif //CLASE11PROG_FECHA_H
```

Como se puede ver, en este caso no implementaremos las funciones comentadas abajo, pero lo importante son las declaraciones que se ven en la parte superior del código, que ahora implementaremos en nuestro fichero *Fecha.c*:

```
//  
// Created by pablo on 5/9/2024.  
//  
  
#include "Fecha.h"  
#include <stdlib.h>  
  
FechaTipo *creaFecha(int dia, int mes, int anyo) {  
    if (dia < 1 || dia > 31) {  
        return NULL;  
    } else if (mes < 1 || mes > 12) {  
        return NULL;  
    }  
    FechaTipo *fecha = malloc(sizeof(FechaTipo));  
    fecha->dia = dia;  
    fecha->mes = mes;  
    fecha->anyo = anyo;  
  
    return fecha;  
}  
  
FechaTipo creaFechaEstatico(int dia, int mes, int anyo) {  
    FechaTipo fecha;  
    fecha.dia = dia;  
    fecha.mes = mes;  
    fecha.anyo = anyo;  
    return fecha;  
}  
  
int dameDia(FechaTipo *fecha) {  
    return fecha->dia;  
}  
  
int dameMes(FechaTipo *fecha) {  
    return fecha->mes;  
}  
  
int dameAnyo(FechaTipo *fecha) {  
    return fecha->anyo;  
}  
  
void imprimeFecha(FechaTipo *fecha) {  
    // Versión más rápida  
    printf("%i/%i/%i\n", fecha->dia, fecha->mes, fecha->anyo);  
    // Versión más lenta y menos acoplada  
    printf("%i/%i/%i\n", dameDia(fecha), dameMes(fecha), dameAnyo(fecha));  
}
```

En este caso, ya tenemos todas las posibles funciones implementadas. Véase cómo hay alternativas explicadas como más eficientes o menos además. 

Luego, teniendo todo implementado, sólo nos queda ver como añadir todo a nuestro main.c para tener el programa final:

```
#include <stdio.h>  
#include "Fecha.h"  
  
/*  
 * Tipo abstracto de datos: TAD * - Se pueden crear en todos los lenguajes * - Programación imperativa siempre puede hacer TADs * - Tiene datos con funcionalidades asociadas. En C es typedef */  
  
int mainI() {  
    FechaTipo fecha;  
    fecha.dia = 22;  
    fecha.mes = 5;  
    fecha.anyo = 2000;  
  
    printf("El dia es %i", fecha.dia);  
  
    return 0;  
}  
  
int main() {  
    /* Este código está muy acoplado  
    TipoFecha fecha;    
    fecha.dia = 22;    
    fecha.mes = 12;    
    fecha.anyo = 2000; 

    printf("El dia es %i",fecha.dia);    
    */  
    
    // El código siguiente está poco acoplado (desconoce detalles de implementación)    
    FechaTipo *fechaBuena = creaFecha(22, 5, 2000);  
    printf("El dia es %i\n", dameDia(fechaBuena));  
  
    FechaTipo fechaBuenaEstatico = creaFechaEstatico(22, 12, 2000);  
    printf("El dia es %i (variable estatica)\n", dameDia(&fechaBuenaEstatico));  
  
    FechaTipo *fecha2 = creaFecha(35, 12, 2000);  
    if (fecha2 == NULL) {  
        printf("Fecha incorrecta\n");  
    } else {  
        printf("El dia es %i\n", dameDia(fecha2));  
    }  
    imprimeFecha(fechaBuena);  
}
```

Finalmente, vemos como se vuelve mucho más fácil de comprender el código, dándonos a nosotros el control sobre cómo hace lo que hace, sin dejar ver en nuestro código base la implementación.