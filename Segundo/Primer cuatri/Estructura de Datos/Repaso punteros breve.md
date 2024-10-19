```
typedef struct {
	edad;
	nombre;
} tAlumno;

tAlumno uno;
tAlumno *ptrUno;

ptrUno = &uno;
uno.edad = 21 // Acceder al contenido del struct si no es un puntero, pues el puntero sería una dirección a este struct, no el mismo struct

ptrUno -> edad = 22 // Accedemos al contenido del campo

(*ptrUno).edad = 23
// Ve lo que hay en esa dirección de memoria, es decir ya tengo la dirección a nuestro struct
// Si ptrUno = &uno; 
// *ptr es lo mismo a uno
```

![[Drawing 2024-10-17 15.32.32.excalidraw]]