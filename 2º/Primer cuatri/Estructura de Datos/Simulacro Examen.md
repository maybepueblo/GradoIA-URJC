Resolver el examen de simulacro hecho el día 17/12/24.

#### 1º Ejercicio

>[!NOTE] Enunciado 
>Dado un árbol binario de búsqueda, explica cuál es la complejidad algorítmica en notación O() de una operación de inserción de árbol.

Si tenemos un árbol balanceado, podemos dar la complejidad de un caso promedio donde la altura del árbol es *h*, siendo la complejidad resultante:
$$O(log \space n)$$
El peor caso sería un árbol completamente desbalanceado (por ejemplo insertar los nodos todos en un lado), la altura es únicamente *n*. La complejidad sería de:
$$O(n)$$
#### 2º Ejercicio

>[!NOTE] Enunciado 
> En la práctica de los Dioses, ¿qué se pedía en sus diferentes apartados? Explica cómo procediste a realizarla y esboza el prototipo de la función que se pedía para conocer si un dios tenía parentesco con otro. A continuación, describe con tus palabras qué hace esa función y cómo lo hace

En Dioses lo que se pedía era copiar el árbol de dioses dado con una implementación dinámica, teniendo funciones también pensadas para realizar el recorrido a lo largo del árbol (preorden, inorden, postorden)

#### 3º Ejercicio

>[!NOTE] Enunciado
>Especifica la función EspejarMisterio para que, dado un árbol binario, devuelva el árbol con todos los subárboles izquierdos y derechos intercambiados entre ellos cuando cada raíz cumpla la condición Misterio. Se dispone de la función genérica de TipoElemento:
>
Misterio: TipoElemento -> Booleano, que no hay que especificar y que devuelve CIERTO si el elemento cumple la condición
Misterio y FALSO en caso contrario.
> 
Nótese que, raíces por debajo de una raíz que no cumpla la condición Misterio, sí pueden cumplirla y deberán proceder de
manera equivalente.

```c
ESPECIFICACIÓN

OPERACIONES

(* CONSTRUCTORA GENERADORA *)
EspejarMisterio : TipoArbolBin -> TipoArbolBin 

ECUACIONES

(* CONSTRUCTORA GENERADORA *)
EspejarMisterio := Si raiz NULO entonces
						NULO 
					Fin Si

	izquierda <- EspejarMisterio(izquierda)
	derecha <- EspejarMisterio(derecha)

	Si Misterio(raiz) entonces
		temp <- izquierda
		izquierda <- derecha 
		derecha <- temp

FIN ESPECIFICACIÓN
```

#### 4º Ejercicio

>[!NOTE] Enunciado
>Dada la siguiente representación estática de un árbol binario, contesta:

![[Pasted image 20241219135655.png]]

1. Devolver la lista de elementos del recorrido:

Laura -> Ana -> Esteban 

2. Elimina la raíz del árbol e indica como queda el árbol tras hacer la operación (dibújalo esquemáticamente o describir los cambios a realizar)

	Ana
  /            \
-           Esteban  
		/           \
		-            -


3. Describe cómo queda el árbol si se inserta, en el árbol original del enunciado, el elemento ‘Carmenʼ como nueva raíz y que el árbol original quede como subárbol derecho de la nueva raíz (puedes "dibujar" esquemáticamente o describir textualmente todos los cambios que hay que realizar en los índices)

```
	Carmen
	/    \
  ---    Laura
		  /   \
		Ana   ---
		/ \    
	  --- Esteban
			/   \
		 ---	---
```

#### 5º Ejercicio

>[!NOTE] Enunciado
>Se desea implementar una red social de universitarios (estudiantes y profesores) de la URJC denominada NM1GO, en la que cada perfil pueda asignar puntuaciones positivas y negativas a otros perfiles para considerar su grado de amistad o enemistad, respectivamente. En esta red se otorgan 100 puntos máximos a cada perfil estudiante para distribuirlos entre amistades y enemistades (por ejemplo, +50 y -50 harían uso de los 100 puntos, pero podrían distribuirse con menos peso entre más perfiles o apenas utilizar el máximo disponible) y de 200 puntos para profesores. Esta red tendrá como máximo 50.000 nodos (número aproximado de estudiantes, 45000, y profesores, 5000, de la URJC).

a. ¿Qué tipo de estructura y representación utilizarás? Define los tipos de datos de la estructura principal para que los perfiles tengan la información tUniversitario definida como:

```c
enum tipo{ESTUDIANTE, PROFESOR}

typedef struct{
	enum tipo rol;
	char nombre[25];
	int numAmigos; //entero que si es positivo tiene más amigos que enemigos y viceversa
	int ptsDisponibles; //número de puntos disponibles para asignar desde 0 hasta 100 para estudiantes o
	200 para profesores
}tUniversitario;
```

```c
typedef struct NodoAdy {
	tUniversitario universitario;
	int puntos;
	struct NodoAdy* siguiente;
}; 

typedef NodoAdy* ListaAdy;

typedef struct NodoLista {
	tUniversitario universitario; 
	struct NodoAdy* adyacente; // Lista de adyacencia
	struct NodoLista* siguiente; // Siguiente en la lista
};

typedef NodoLista* Grafo;
```

b. Suponiendo disponible la operación para la creación aleatoria de enteros:
	int devolverAleatorio(int valorMin, int valorMax);

implementa la función insertarAleatorio que inserta en la estructura un nuevo nodo estudiante y que asigna amistad y enemistad aleatoriamente en el rango [-50, +50] a una colección de profesores (no importa cuáles) hasta agotar sus puntos.

Supóngase accesibles a través de universitario.h (no hay que implementar) también las operaciones del tipo tUniversitario:

```C
void copiarPerfil(tUniversitario* pCopia, tUniversitario origen);
void crearPerfil(tUniversitario *pPerfil, enum tipo rol); /*pedirá los datos o los leerá de un archivo para devolver un perfil tUniversitario inicializado adecuadamente dependiendo el rol que tenga (estudiante o profesor). Inicialmente el número de amigos y enemigos de un perfil recién creado será de 0*/
void setPuntosDisponibles(tUniversitario *pPerfil, int p);
int getPuntosDisponibles(tUniversitario *pPerfil); //min 0, max 100/200
void setNumAmigos(tUniversitario *pPerfil, int n);
int getNumAmigos(tUniversitario perfil);
void setNombre(tUniversitario *pPerfil, char *nombre);
char* getNombre (tUniversitario perfil);
void setRol(tUniversitario *pPerfil, enum tipo rol);
enum tipo getRol (tUniversitario perfil);
```

```
void insertarAleatorio(Grafo* pG, tUniversitario perfil) {
	NodoLista* aux = (struct NodoLista*) malloc (sizeof(struct NodoLista))
	asignar(&(aux->universitario))
} 
```




